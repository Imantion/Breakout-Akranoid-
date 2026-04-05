#pragma once

#include "Scene.hpp"
#include "ui/Label.hpp"
#include "entities/Paddle.hpp"
#include "entities/Ball.hpp"
#include "entities/Brick.hpp"
#include "systems/PaddleController.hpp"
#include "systems/MovementSystem.hpp"
#include "systems/CollisionSystem.hpp"
#include "systems/RenderSystem.hpp"

#include <memory>
#include <vector>

namespace Breakout
{

class GameplayScene : public Scene
{
public:
    GameplayScene();

    void OnEnter() override;
    void OnExit() override;

    void ProcessInput(sf::RenderWindow& window) override;
    void Update(float dt) override;
    void Render(sf::RenderWindow& window) override;

private:
    void _initBricks();
    void _subscribeEvents();
    void _resetBall(Ball& ball);
    void _updateHud();

    std::unique_ptr<Paddle>  m_Paddle;
    std::vector<Ball>        m_Balls;
    std::vector<Brick>       m_Bricks;

    PaddleController   m_PaddleController;
    MovementSystem     m_MovementSystem;
    CollisionSystem    m_CollisionSystem;
    RenderSystem       m_RenderSystem;

    int      m_Score;
    int      m_Lives;
    uint32_t m_DestroyedInRow;
    Label    m_ScoreLabel;
    Label    m_LivesLabel;
};

} // namespace Breakout
