#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "EventBus.hpp"
#include "TextureManager.hpp"

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

    EventBus&          GetEventBus();
    TextureManager&    GetTextureManager();
    const sf::Font&    GetFont() const;
    sf::RenderWindow&  GetWindow();

private:
    static Game*              s_Instance;

    sf::RenderWindow          m_Window;
    sf::Font                  m_Font;
    EventBus                  m_EventBus;
    TextureManager            m_TextureManager;

    std::unique_ptr<Scene>    m_CurrentScene;
    std::unique_ptr<Scene>    m_PendingScene;
};

} // namespace Breakout
