#include "core/Game.hpp"
#include "core/Constants.hpp"
#include "scenes/Scene.hpp"
#include "scenes/MenuScene.hpp"
#include "scenes/GameplayScene.hpp"
#include "scenes/LevelCompleteScene.hpp"
#include "scenes/GameOverScene.hpp"
#include "scenes/WinScene.hpp"

#include "events/EventBus.hpp"
#include "managers/TextureManager.hpp"
#include "managers/ScoreManager.hpp"
#include "levels/LevelLoader.hpp"
#include "systems/RenderSystem.hpp"
#include "systems/AudioSystem.hpp"

namespace Breakout
{

Game* Game::s_Instance = nullptr;

Game::Game()
    : m_Window(sf::VideoMode({g_WindowWidth, g_WindowHeight}), g_WindowTitle)
	, m_Font(g_FontFile), m_TextureManager(std::make_unique<TextureManager>())
    , m_EventBus(std::make_unique<EventBus>())
    , m_ScoreManager(std::make_unique<ScoreManager>())
    , m_LevelLoader(std::make_unique<LevelLoader>())
    , m_RenderSystem(std::make_unique<RenderSystem>())
    , m_AudioSystem(std::make_unique<AudioSystem>())
{
    s_Instance = this;
    m_Window.setFramerateLimit(0);
    m_TextureManager->LoadAll(g_DataDirectory);
    m_AudioSystem->LoadAll(g_AudioDirectory);
    m_LevelLoader->LoadCampaign(g_CampaignFile);
    m_ScoreManager->Load(g_ScoresFile);

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

void Game::StartCampaign()
{
    m_Session = GameSession{};
    auto bricks = m_LevelLoader->LoadLevel(0);
    SetScene(std::make_unique<GameplayScene>(std::move(bricks)));
}

void Game::OnLevelComplete(int score)
{
    m_Session.score = score;

    m_ScoreManager->AddScore(m_Session.currentLevelIndex, g_DefaultPlayerName, score);
    m_ScoreManager->Save(g_ScoresFile);

    if (m_LevelLoader->HasNextLevel(m_Session.currentLevelIndex))
    {
        SetScene(std::make_unique<LevelCompleteScene>(score));
    }
    else
    {
        SetScene(std::make_unique<WinScene>(score));
    }
}

void Game::OnGameOver(int score)
{
    m_Session.score = score;
    m_ScoreManager->AddScore(m_Session.currentLevelIndex, g_DefaultPlayerName, score);
    m_ScoreManager->Save(g_ScoresFile);
    SetScene(std::make_unique<GameOverScene>(score));
}

void Game::LoadNextLevel()
{
    m_Session.currentLevelIndex++;
    auto bricks = m_LevelLoader->LoadLevel(m_Session.currentLevelIndex);
    SetScene(std::make_unique<GameplayScene>(std::move(bricks)));
}

EventBus& Game::GetEventBus()
{
    return *m_EventBus;
}

TextureManager& Game::GetTextureManager()
{
    return *m_TextureManager;
}

ScoreManager& Game::GetScoreManager()
{
    return *m_ScoreManager;
}

RenderSystem& Game::GetRenderSystem()
{
    return *m_RenderSystem;
}

AudioSystem& Game::GetAudioSystem()
{
    return *m_AudioSystem;
}

const GameSession& Game::GetSession() const
{
    return m_Session;
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

            m_EventBus->Clear();
            m_AudioSystem->SubscribeToEvents();
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
                m_EventBus->FlushEvents();
                accumulator -= g_FixedTimeStep;
            }

            m_RenderSystem->BeginFrame(m_Window);
            m_CurrentScene->Render(*m_RenderSystem, m_Window);
            m_RenderSystem->EndFrame(m_Window);
        }
    }
}

} // namespace Breakout
