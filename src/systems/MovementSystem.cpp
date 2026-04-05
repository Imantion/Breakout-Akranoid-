#include "MovementSystem.hpp"
#include "Constants.hpp"

namespace Breakout
{

void MovementSystem::Update(Paddle& paddle, std::span<Ball> balls,
                            std::span<std::unique_ptr<Ability>> abilities, float dt)
{
    auto paddlePos = paddle.GetPosition();
    paddlePos.x += paddle.GetDirection() * g_PaddleSpeed * dt;
    paddle.SetPosition(paddlePos);

    for (Ball& ball : balls)
    {
        if (ball.IsAttached())
        {
            float ballX = paddle.GetPosition().x + paddle.GetWidth() / 2.0f;
            float ballY = paddle.GetPosition().y - ball.GetRadius();
            ball.SetPosition({ballX, ballY});
            continue;
        }

        sf::Vector2f ballPos = ball.GetPosition();
        sf::Vector2f ballVel = ball.GetVelocity();
        ballPos.x += ballVel.x * dt;
        ballPos.y += ballVel.y * dt;
        ball.SetPosition(ballPos);
    }

    for (auto& ability : abilities)
    {
        if (!ability || !ability->IsAlive())
            continue;

        sf::Vector2f pos = ability->GetPosition();
        pos.y += g_AbilityFallSpeed * dt;
        ability->SetPosition(pos);
    }
}

} // namespace Breakout
