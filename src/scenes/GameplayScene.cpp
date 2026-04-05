#include "GameplayScene.hpp"
#include "Game.hpp"
#include "Constants.hpp"
#include "Events.hpp"
#include "scenes/MenuScene.hpp"
#include "scenes/GameOverScene.hpp"
#include "scenes/WinScene.hpp"

#include <algorithm>
#include <string>

namespace Breakout
{

GameplayScene::GameplayScene()
    : m_Score(0)
    , m_Lives(g_StartingLives)
    , m_DestroyedInRow(0)
    , m_ScoreLabel(Game::Get()->GetFont(), "Score: 0", g_HudFontSize,
                   {g_HudMargin, g_HudMargin})
    , m_LivesLabel(Game::Get()->GetFont(),
                   "Lives: " + std::to_string(g_StartingLives), g_HudFontSize,
                   {0.0f, g_HudMargin})
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
    _initBricks();

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
    }

    m_PaddleController.Update(*m_Paddle);
}

void GameplayScene::Update(float dt)
{
    m_MovementSystem.Update(*m_Paddle, m_Balls, dt);
    m_CollisionSystem.Update(m_Balls, *m_Paddle, m_Bricks);
}

void GameplayScene::Render(RenderSystem& renderer, sf::RenderWindow& window)
{
    renderer.DrawBricks(window, m_Bricks);
    renderer.DrawActor(window, *m_Paddle);

    for (const auto& ball : m_Balls)
        renderer.DrawActor(window, ball);

    renderer.DrawLabel(window, m_ScoreLabel);
    renderer.DrawLabel(window, m_LivesLabel);
}

void GameplayScene::_initBricks()
{
    const auto& brickTex = Game::Get()->GetTextureManager().GetTexture("brick");

    m_Bricks.reserve(g_BrickColumns * g_BrickRows);

    for (int row = 0; row < g_BrickRows; ++row)
    {
        for (int col = 0; col < g_BrickColumns; ++col)
        {
            float x = g_BrickGridLeftMargin + col * (g_BrickWidth + g_BrickPadding);
            float y = g_BrickGridTopMargin + row * (g_BrickHeight + g_BrickPadding);

            m_Bricks.emplace_back(brickTex,
                                  sf::Vector2f{x, y},
                                  g_BrickWidth, g_BrickHeight,
                                  row);
        }
    }
}

void GameplayScene::_subscribeEvents()
{
    Game::Get()->GetEventBus().Subscribe<BallHitBrickEvent>(
        [this](const BallHitBrickEvent&)
        {
            ++m_DestroyedInRow;
            m_Score += m_DestroyedInRow >= g_DestroyedInRow ? g_ScorePerBrick + g_DestroyedInRowBonus : g_ScorePerBrick;
            _updateHud();

            bool allDestroyed = std::none_of(m_Bricks.begin(), m_Bricks.end(),
                [](const Brick& b) { return b.IsAlive(); });

            if (allDestroyed)
                Game::Get()->SetScene(std::make_unique<WinScene>(m_Score));
        });

    Game::Get()->GetEventBus().Subscribe<BallLostEvent>(
        [this](const BallLostEvent& event)
        {
            m_Lives--;
            _updateHud();

            if (m_Lives <= 0)
            {
                Game::Get()->SetScene(std::make_unique<GameOverScene>(m_Score));
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
}

void GameplayScene::_resetBall(Ball& ball)
{
    ball.SetPosition({g_WindowWidth / 2.0f, g_WindowHeight / 2.0f});
    ball.SetVelocity({g_BallSpeed * 0.7f, -g_BallSpeed * 0.7f});
}

void GameplayScene::_updateHud()
{
    m_ScoreLabel.SetText("Score: " + std::to_string(m_Score));
    m_LivesLabel.SetText("Lives: " + std::to_string(m_Lives));
}

} // namespace Breakout
