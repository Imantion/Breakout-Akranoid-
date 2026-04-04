#include "MovementSystem.hpp"
#include "Constants.hpp"

namespace Breakout
{

void MovementSystem::Update(Paddle& paddle, Ball& ball, float dt) const
{
    auto paddlePos = paddle.GetPosition();
    paddlePos.x += paddle.GetDirection() * g_PaddleSpeed * dt;
    paddle.SetPosition(paddlePos);

    auto ballPos = ball.GetPosition();
    auto ballVel = ball.GetVelocity();
    ballPos.x += ballVel.x * dt;
    ballPos.y += ballVel.y * dt;
    ball.SetPosition(ballPos);
}

} // namespace Breakout
