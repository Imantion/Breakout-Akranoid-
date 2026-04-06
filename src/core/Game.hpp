#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "core/GameSession.hpp"
#include "events/EventBus.hpp"
#include "managers/TextureManager.hpp"
#include "managers/ScoreManager.hpp"
#include "levels/LevelLoader.hpp"
#include "systems/RenderSystem.hpp"

namespace Breakout
{

class Scene;

class Game
{
public:
    Game();
    ~Game();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    static Game* Get();

    void Run();
    void SetScene(std::unique_ptr<Scene> scene);

    void StartCampaign();
    void OnLevelComplete(int score);
    void OnGameOver(int score);
    void LoadNextLevel();

    EventBus&             GetEventBus();
    TextureManager&       GetTextureManager();
    ScoreManager&         GetScoreManager();
    RenderSystem&         GetRenderSystem();
    const GameSession&    GetSession() const;
    const sf::Font&       GetFont() const;
    sf::RenderWindow&     GetWindow();

private:
    static Game*              s_Instance;

    sf::RenderWindow          m_Window;
    sf::Font                  m_Font;
    EventBus                  m_EventBus;
    TextureManager            m_TextureManager;
    ScoreManager              m_ScoreManager;
    LevelLoader               m_LevelLoader;
    RenderSystem              m_RenderSystem;

    GameSession               m_Session;

    std::unique_ptr<Scene>    m_CurrentScene;
    std::unique_ptr<Scene>    m_PendingScene;
};

} // namespace Breakout
