#include "GameplayScene.hpp"
#include "core/Game.hpp"
#include "core/Constants.hpp"
#include "events/Events.hpp"
#include "core/GameplayContext.hpp"
#include "scenes/MenuScene.hpp"
#include "entities/AbilityFactory.hpp"

#include <algorithm>
#include <cmath>
#include <string>

namespace Breakout
{

GameplayScene::GameplayScene(std::vector<std::unique_ptr<Brick>> bricks)
    : m_Bricks(std::move(bricks))
    , m_Score(0)
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

    m_Paddle = std::make_unique<Paddle>(
        texMgr.GetTexture("paddle"),
        sf::Vector2f{g_WindowWidth / 2.0f - g_PaddleWidth / 2.0f,
                     g_WindowHeight - g_PaddleHeight - g_PaddleBottomMargin},
        g_PaddleWidth, g_PaddleHeight);

    m_Balls.emplace_back(
        texMgr.GetTexture("ball"),
        sf::Vector2f{g_WindowWidth / 2.0f, g_WindowHeight / 2.0f},
        g_BallRadius);

    _resetBall(m_Balls.back());

    float livesX = g_WindowWidth - g_HudMargin - 120.0f;
    m_LivesLabel.SetPosition({livesX, g_HudMargin});
}

void GameplayScene::OnEnter()
{
    _subscribeEvents();
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
    _cleanupDeadAbilities();
}

void GameplayScene::Render(RenderSystem& renderer, sf::RenderWindow& window)
{
    renderer.DrawBricks(window, m_Bricks);
    renderer.DrawActor(window, *m_Paddle);

    for (const auto& ball : m_Balls)
        renderer.DrawActor(window, ball);

    for (const auto& ability : m_Abilities)
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
    m_Balls.emplace_back(texMgr.GetTexture("ball"), position, g_BallRadius);
    m_Balls.back().SetVelocity(velocity);
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

void GameplayScene::_subscribeEvents()
{
    Game::Get()->GetEventBus().Subscribe<BrickDeathEvent>(
        [this](const BrickDeathEvent& event)
        {
            ++m_DestroyedInRow;
            m_Score += m_DestroyedInRow >= g_DestroyedInRow
                ? g_ScorePerBrick + g_DestroyedInRowBonus
                : g_ScorePerBrick;

            _spawnAbility(event.brick.GetPosition());

            bool allDestroyed = std::none_of(m_Bricks.begin(), m_Bricks.end(),
                [](const std::unique_ptr<Brick>& b) { return b && b->IsDestructible() && b->IsAlive(); });

            if (allDestroyed)
                Game::Get()->OnLevelComplete(m_Score);
        });

    Game::Get()->GetEventBus().Subscribe<BallLostEvent>(
        [this](const BallLostEvent& event)
        {
            if (m_Balls.size() > 1)
            {
                m_Balls.erase(std::remove_if(m_Balls.begin(), m_Balls.end(),
                    [&event](const Ball& ball) { return &ball == &event.ball; }),
                m_Balls.end());
                return;
            }

            m_Lives--;

            if (m_Lives <= 0)
            {
                Game::Get()->OnGameOver(m_Score);
                return;
            }

            _resetBall(event.ball);
            m_DestroyedInRow = 0;
        });

    Game::Get()->GetEventBus().Subscribe<BallHitWallEvent>(
        [this](const BallHitWallEvent&)
        {
            m_DestroyedInRow = 0;
        });

    Game::Get()->GetEventBus().Subscribe<AbilityPickedUpEvent>(
        [this](const AbilityPickedUpEvent& event)
        {
            GameplayContext context{
                .paddle = *m_Paddle,
                .scene  = *this
            };

            event.ability.Apply(context);
            event.ability.Kill();
        });

    Game::Get()->GetEventBus().Subscribe<AbilityFallOutOfBoundsEvent>(
        [this](const AbilityFallOutOfBoundsEvent& event)
        {
            event.ability.Kill();
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

    m_Abilities.push_back(AbilityFactory::CreateRandom(position));
}

void GameplayScene::_cleanupDeadAbilities()
{
    m_Abilities.erase(
        std::remove_if(m_Abilities.begin(), m_Abilities.end(),
            [](const std::unique_ptr<Ability>& a) { return !a || !a->IsAlive(); }),
        m_Abilities.end());
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
    for (auto& ball : m_Balls)
    {
        if (ball.IsAttached())
            return &ball;
    }
    return nullptr;
}

} // namespace Breakout
