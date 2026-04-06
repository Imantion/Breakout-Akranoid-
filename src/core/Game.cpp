#include "core/Game.hpp"
#include "core/Constants.hpp"
#include "scenes/Scene.hpp"
#include "scenes/MenuScene.hpp"

namespace Breakout
{

Game* Game::s_Instance = nullptr;

Game::Game()
    : m_Window(sf::VideoMode({g_WindowWidth, g_WindowHeight}), g_WindowTitle)
    , m_Font(g_FontFile)
{
    s_Instance = this;
    m_Window.setFramerateLimit(0);
    m_TextureManager.LoadAll(g_DataDirectory);

    SetScene(std::make_unique<MenuScene>());
}

Game::~Game()
{
    if (m_CurrentScene)
        m_CurrentScene->OnExit();

    if (s_Instance == this)
        s_Instance = nullptr;
}

Game* Game::Get()
{
    return s_Instance;
}

void Game::SetScene(std::unique_ptr<Scene> scene)
{
    m_PendingScene = std::move(scene);
}

EventBus& Game::GetEventBus()
{
    return m_EventBus;
}

TextureManager& Game::GetTextureManager()
{
    return m_TextureManager;
}

RenderSystem& Game::GetRenderSystem()
{
    return m_RenderSystem;
}

const sf::Font& Game::GetFont() const
{
    return m_Font;
}

sf::RenderWindow& Game::GetWindow()
{
    return m_Window;
}

void Game::Run()
{
    sf::Clock clock;
    float accumulator = 0.0f;

    while (m_Window.isOpen())
    {
        if (m_PendingScene)
        {
            if (m_CurrentScene)
                m_CurrentScene->OnExit();

            m_EventBus.Clear();
            m_CurrentScene = std::move(m_PendingScene);
            m_CurrentScene->OnEnter();
        }

        float frameTime = clock.restart().asSeconds();
        accumulator += frameTime;

        if (m_CurrentScene)
        {
            m_CurrentScene->ProcessInput(m_Window);

            while (accumulator >= g_FixedTimeStep)
            {
                m_CurrentScene->Update(g_FixedTimeStep);
                m_EventBus.FlushEvents();
                accumulator -= g_FixedTimeStep;
            }

            m_RenderSystem.BeginFrame(m_Window);
            m_CurrentScene->Render(m_RenderSystem, m_Window);
            m_RenderSystem.EndFrame(m_Window);
        }
    }
}

} // namespace Breakout
