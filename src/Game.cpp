#include "Game.hpp"
#include "Constants.hpp"
#include "Events.hpp"

namespace Breakout
{

Game* Game::s_Instance = nullptr;

Game::Game()
    : m_Window(sf::VideoMode({g_WindowWidth, g_WindowHeight}), g_WindowTitle)
    , m_Paddle({g_WindowWidth / 2.0f - g_PaddleWidth / 2.0f,
                g_WindowHeight - g_PaddleHeight - g_PaddleBottomMargin},
               {g_PaddleWidth, g_PaddleHeight})
    , m_Ball({g_WindowWidth / 2.0f, g_WindowHeight / 2.0f}, g_BallRadius)
{
    s_Instance = this;
    m_Window.setFramerateLimit(0);
    _resetBall();
    _initBricks();
    _subscribeEvents();
}

Game::~Game()
{
    if (s_Instance == this)
        s_Instance = nullptr;
}

Game* Game::Get()
{
    return s_Instance;
}

EventBus& Game::GetEventBus()
{
    return m_EventBus;
}

void Game::Run()
{
    sf::Clock clock;
    float accumulator = 0.0f;

    while (m_Window.isOpen())
    {
        float frameTime = clock.restart().asSeconds();
        accumulator += frameTime;

        _processInput();

        while (accumulator >= g_FixedTimeStep)
        {
            _update(g_FixedTimeStep);
            accumulator -= g_FixedTimeStep;
        }

        float interpolation = accumulator / g_FixedTimeStep;
        _render(interpolation);
    }
}

void Game::_processInput()
{
    while (const auto event = m_Window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            m_Window.close();

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                m_Window.close();
        }
    }

    m_PaddleController.Update(m_Paddle);
}

void Game::_update(float dt)
{
    m_MovementSystem.Update(m_Paddle, m_Ball, dt);
    m_CollisionSystem.Update(m_Ball, m_Paddle, m_Bricks);
}

void Game::_render([[maybe_unused]] float interpolation)
{
    m_RenderSystem.Render(m_Window, m_Paddle, m_Ball, m_Bricks);
}

void Game::_initBricks()
{
    m_Bricks.reserve(g_BrickColumns * g_BrickRows);

    for (int row = 0; row < g_BrickRows; ++row)
    {
        for (int col = 0; col < g_BrickColumns; ++col)
        {
            float x = g_BrickGridLeftMargin + col * (g_BrickWidth + g_BrickPadding);
            float y = g_BrickGridTopMargin + row * (g_BrickHeight + g_BrickPadding);

            m_Bricks.emplace_back(sf::Vector2f{x, y},
                                  sf::Vector2f{g_BrickWidth, g_BrickHeight},
                                  row);
        }
    }
}

void Game::_subscribeEvents()
{
    m_EventBus.Subscribe<BallLostEvent>([this](const BallLostEvent&)
    {
        _resetBall();
    });
}

void Game::_resetBall()
{
    m_Ball.SetPosition({g_WindowWidth / 2.0f, g_WindowHeight / 2.0f});
    m_Ball.SetVelocity({g_BallSpeed * 0.7f, -g_BallSpeed * 0.7f});
}

} // namespace Breakout
