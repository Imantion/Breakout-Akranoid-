#include "MovementSystem.hpp"
#include "Constants.hpp"

namespace Breakout
{

void MovementSystem::Update(Paddle& paddle, std::span<Ball> balls, float dt)
{
    auto paddlePos = paddle.GetPosition();
    paddlePos.x += paddle.GetDirection() * g_PaddleSpeed * dt;
    paddle.SetPosition(paddlePos);

    for(Ball& ball : balls)
    {
        sf::Vector2f ballPos = ball.GetPosition();
        sf::Vector2f ballVel = ball.GetVelocity();
        ballPos.x += ballVel.x * dt;
        ballPos.y += ballVel.y * dt;
        ball.SetPosition(ballPos);
    }
    
}

} // namespace Breakout
