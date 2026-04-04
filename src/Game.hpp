#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "EventBus.hpp"
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

    EventBus& GetEventBus();

private:
    void ProcessInput();
    void Update(float dt);
    void Render(float interpolation);

    void InitBricks();
    void SubscribeEvents();
    void ResetBall();

    static Game*       s_Instance;

    sf::RenderWindow   m_Window;
    EventBus           m_EventBus;

    Paddle             m_Paddle;
    Ball               m_Ball;
    std::vector<Brick> m_Bricks;

    PaddleController   m_PaddleController;
    MovementSystem     m_MovementSystem;
    CollisionSystem    m_CollisionSystem;
    RenderSystem       m_RenderSystem;
};

} // namespace Breakout
