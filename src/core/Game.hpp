#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "core/GameSession.hpp"

namespace Breakout
{

class Scene;
class EventBus;
class TextureManager;
class ScoreManager;
class LevelLoader;
class RenderSystem;
class AudioSystem;

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
    AudioSystem&          GetAudioSystem();
    const GameSession&    GetSession() const;
    const sf::Font&       GetFont() const;
    sf::RenderWindow&     GetWindow();

private:
    static Game*              s_Instance;

    sf::RenderWindow          m_Window;
    sf::Font                  m_Font;
    std::unique_ptr<EventBus>                  m_EventBus;
    std::unique_ptr<TextureManager>            m_TextureManager;
    std::unique_ptr<ScoreManager>              m_ScoreManager;
    std::unique_ptr<LevelLoader>               m_LevelLoader;
    std::unique_ptr<RenderSystem>              m_RenderSystem;
    std::unique_ptr<AudioSystem>               m_AudioSystem;

    GameSession               m_Session;

    std::unique_ptr<Scene>    m_CurrentScene;
    std::unique_ptr<Scene>    m_PendingScene;
};

} // namespace Breakout
