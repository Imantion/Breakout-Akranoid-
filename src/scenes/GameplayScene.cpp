#include "GameplayScene.hpp"
#include "core/Game.hpp"
#include "core/Constants.hpp"
#include "events/Events.hpp"
#include "core/GameplayContext.hpp"
#include "scenes/MenuScene.hpp"
#include "entities/AbilityFactory.hpp"
#include "managers/ScoreManager.hpp"
#include "systems/AudioSystem.hpp"
#include "events/EventBus.hpp"
#include "managers/TextureManager.hpp"


#include <algorithm>
#include <cmath>
#include <string>

namespace Breakout
{

GameplayScene::GameplayScene(std::vector<std::unique_ptr<Brick>> bricks)
    : m_Score(0)
    , m_Lives(g_StartingLives)
    , m_DestroyedInRow(0)
    , m_ScoreLabel(Game::Get()->GetFont(), "Score: 0",
                   g_HudFontSize, {g_HudMargin, g_HudMargin})
    , m_LivesLabel(Game::Get()->GetFont(),
                   "Lives: " + std::to_string(g_StartingLives), g_HudFontSize,
                   {0.0f, g_HudMargin})
    , m_Rng(std::random_device{}())
{
    auto& texMgr = Game::Get()->GetTextureManager();
    m_Registry.reserve(bricks.size() + 2); // +2 for paddle and ball

    m_Paddle = _registerActor(std::make_unique<Paddle>(
        texMgr.GetTexture(g_TexPaddle),
        sf::Vector2f{g_WindowWidth / 2.0f - g_PaddleWidth / 2.0f,
                     g_WindowHeight - g_PaddleHeight - g_PaddleBottomMargin},
        g_PaddleWidth, g_PaddleHeight));

    auto* ball = _registerActor(std::make_unique<Ball>(
        texMgr.GetTexture(g_TexBall),
        sf::Vector2f{g_WindowWidth / 2.0f, g_WindowHeight / 2.0f},
        g_BallRadius));
    m_Balls.push_back(ball);
    _resetBall(*ball);

    m_Bricks.reserve(bricks.size());
    for (auto& brick : bricks)
    {
            auto* rawBrick = _registerActor(std::move(brick));
            m_Bricks.push_back(rawBrick);
    }

    float livesX = g_WindowWidth - g_HudMargin - g_LivesLabelRightOffset;
    m_LivesLabel.SetPosition({livesX, g_HudMargin});
}

void GameplayScene::OnEnter()
{
    _subscribeEvents();
    Game::Get()->GetAudioSystem().PlayMusic(g_GameplayMusicFile);
}

void GameplayScene::OnExit()
{
}

void GameplayScene::ProcessInput(sf::RenderWindow& window)
{
    while (const auto event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                Game::Get()->SetScene(std::make_unique<MenuScene>());
        }

        if (const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mouseClick->button == sf::Mouse::Button::Left)
                _launchAttachedBall(window, mouseClick->position);
        }
    }

    m_PaddleController.Update(*m_Paddle);
}

void GameplayScene::Update(float dt)
{
    m_EffectManager.Update(dt);

    m_MovementSystem.Update(*m_Paddle, m_Balls, m_Abilities, dt);
    m_CollisionSystem.Update(m_Balls, *m_Paddle, m_Bricks, m_Abilities);

    _handleAim();
    _updateHud();
    _cleanupDead();
}

void GameplayScene::Render(RenderSystem& renderer, sf::RenderWindow& window)
{
    renderer.DrawBricks(window, m_Bricks);
    renderer.DrawActor(window, *m_Paddle);

    for (auto* ball : m_Balls)
    {
        if (ball)
            renderer.DrawActor(window, *ball);
    }

    for (auto* ability : m_Abilities)
    {
        if (ability && ability->IsAlive())
            renderer.DrawActor(window, *ability);
    }

    renderer.DrawAimLine(window, m_AimLine);

    renderer.DrawLabel(window, m_ScoreLabel);
    renderer.DrawLabel(window, m_LivesLabel);
}

void GameplayScene::AddBall(sf::Vector2f position, sf::Vector2f velocity)
{
    auto& texMgr = Game::Get()->GetTextureManager();
    auto* ball = _registerActor(std::make_unique<Ball>(
        texMgr.GetTexture(g_TexBall), position, g_BallRadius));
    ball->SetVelocity(velocity);
    m_Balls.push_back(ball);
}

void GameplayScene::AddLife()
{
    m_Lives++;
    _updateHud();
}

void GameplayScene::AddEffect(EffectType type, float duration,
                              std::function<void()> onApply,
                              std::function<void()> onExpire)
{
    m_EffectManager.PushEffect(type, duration, std::move(onApply), std::move(onExpire));
}

Actor* GameplayScene::FindActor(const uuids::uuid& uuid)
{
    auto it = m_Registry.find(uuid);
    if (it == m_Registry.end())
        return nullptr;
    return it->second.get();
}

template<typename T>
T* GameplayScene::_registerActor(std::unique_ptr<T> actor)
{
    T* raw = actor.get();
    m_Registry[raw->GetUUID()] = std::move(actor);
    return raw;
}

void GameplayScene::_subscribeEvents()
{
    Game::Get()->GetEventBus().Subscribe<BrickDeathEvent>(
        [this](const BrickDeathEvent& event)
        {
            auto* actor = FindActor(event.brickUUID);
            if (!actor || actor->GetType() != EntityType::Destructible) 
                return;
            auto* brick = static_cast<Brick*>(actor);

            ++m_DestroyedInRow;
            m_Score += m_DestroyedInRow >= g_DestroyedInRow
                ? g_ScorePerBrick + g_DestroyedInRowBonus
                : g_ScorePerBrick;

            _spawnAbility(brick->GetPosition());

            bool allDestroyed = std::none_of(m_Bricks.begin(), m_Bricks.end(),
                [](Brick* b) { return b && b->IsDestructible() && b->IsAlive(); });

            if (allDestroyed)
                Game::Get()->OnLevelComplete(m_Score);
        });

    Game::Get()->GetEventBus().Subscribe<BallLostEvent>(
        [this](const BallLostEvent& event)
        {
            auto* actor = FindActor(event.ballUUID);
            if (!actor || actor->GetType() != EntityType::Ball) 
                return;
            auto* ball = static_cast<Ball*>(actor);

            if (m_Balls.size() > 1)
            {
                m_Balls.erase(std::remove(m_Balls.begin(), m_Balls.end(), ball), m_Balls.end());
                m_Registry.erase(event.ballUUID);
                return;
            }

            m_Lives--;

            if (m_Lives <= 0)
            {
                Game::Get()->OnGameOver(m_Score);
                return;
            }

            _resetBall(*ball);
            m_DestroyedInRow = 0;
        });

    Game::Get()->GetEventBus().Subscribe<BallHitPaddleEvent>(
        [this](const BallHitPaddleEvent&)
        {
            m_DestroyedInRow = 0;
        });

    Game::Get()->GetEventBus().Subscribe<AbilityPickedUpEvent>(
        [this](const AbilityPickedUpEvent& event)
        {
            auto* actor = FindActor(event.abilityUUID);
            if (!actor || actor->GetType() != EntityType::Ability) 
                return;

            auto* ability = static_cast<Ability*>(actor);

            GameplayContext context{
                .paddle = *m_Paddle,
                .scene  = *this
            };

            ability->Apply(context);
            ability->Kill();
        });

    Game::Get()->GetEventBus().Subscribe<AbilityFallOutOfBoundsEvent>(
        [this](const AbilityFallOutOfBoundsEvent& event)
        {
            auto* actor = FindActor(event.abilityUUID);
            if (!actor || actor->GetType() != EntityType::Ability) 
                return;

            static_cast<Ability*>(actor)->Kill();
        });
}

void GameplayScene::_resetBall(Ball& ball)
{
    m_AimLine.SetVisibility(true);
    ball.SetVelocity({0.0f, 0.0f});
    ball.SetState(BallState::Attached);
}

void GameplayScene::_updateHud()
{
    m_ScoreLabel.SetText("Score: " + std::to_string(m_Score));
    m_LivesLabel.SetText("Lives: " + std::to_string(m_Lives));
}

void GameplayScene::_handleAim()
{
    if (!m_AimLine.IsVisible())
        return;

    auto* attachedBall = _findAttachedBall();
    if (!attachedBall)
        return;

    auto& window = Game::Get()->GetWindow();
    auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    sf::Vector2f ballCenter = attachedBall->GetPosition();
    ballCenter.x += attachedBall->GetWidth() * 0.5f;
    m_AimLine.Update(ballCenter, mousePos);
}

void GameplayScene::_spawnAbility(sf::Vector2f position)
{
    std::uniform_real_distribution<float> chanceDist(0.0f, 1.0f);
    if (chanceDist(m_Rng) > g_AbilitySpawnChance)
        return;

    auto* ability = _registerActor(AbilityFactory::CreateRandom(position));
    m_Abilities.push_back(ability);
}

void GameplayScene::_cleanupDead()
{
    for (auto it = m_Abilities.begin(); it != m_Abilities.end(); )
    {
        if (!*it || !(*it)->IsAlive())
        {
            if (*it)
                m_Registry.erase((*it)->GetUUID());
            it = m_Abilities.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void GameplayScene::_launchAttachedBall(const sf::RenderWindow& window, sf::Vector2i mousePixel)
{
    Ball* ball = _findAttachedBall();
    if (!ball)
        return;

    auto mousePos = window.mapPixelToCoords(mousePixel);
    auto ballPos  = ball->GetPosition();
    sf::Vector2f dir = mousePos - ballPos;
    float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);

    if (length < 1.0f)
        return;

    dir /= length;
    ball->SetVelocity(dir * g_BallSpeed);
    ball->SetState(BallState::Free);
    m_AimLine.SetVisibility(false);
}

Ball* GameplayScene::_findAttachedBall()
{
    for (auto* ball : m_Balls)
    {
        if (ball && ball->IsAttached())
            return ball;
    }
    return nullptr;
}

} // namespace Breakout
