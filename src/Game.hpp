#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "EventBus.hpp"
#include "TextureManager.hpp"
#include "entities/Paddle.hpp"
#include "entities/Ball.hpp"
#include "entities/Brick.hpp"
#include "systems/PaddleController.hpp"
#include "systems/MovementSystem.hpp"
#include "systems/CollisionSystem.hpp"
#include "systems/RenderSystem.hpp"

namespace Breakout
{

class Game
{
public:
    Game();
    ~Game();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    static Game* Get();

    void Run();

    EventBus&       GetEventBus();
    TextureManager& GetTextureManager();

private:
    void _processInput();
    void _update(float dt);
    void _render(float interpolation);

    void _initBricks();
    void _subscribeEvents();
    void _resetBall(Ball& ball);

    static Game*       s_Instance;

    sf::RenderWindow   m_Window;
    EventBus           m_EventBus;
    TextureManager     m_TextureManager;

    std::unique_ptr<Paddle>  m_Paddle;
    std::vector<Ball>        m_Balls;
    std::vector<Brick>       m_Bricks;

    PaddleController   m_PaddleController;
    MovementSystem     m_MovementSystem;
    CollisionSystem    m_CollisionSystem;
    RenderSystem       m_RenderSystem;
};

} // namespace Breakout
