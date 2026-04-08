#include "MovementSystem.hpp"
#include "core/Constants.hpp"

namespace Breakout
{

void MovementSystem::Update(Paddle& paddle, std::span<Ball*> balls,
                            std::span<Ability*> abilities, float dt)
{
    auto paddlePos = paddle.GetPosition();
    paddlePos.x += paddle.GetDirection() * g_PaddleSpeed * dt;
    paddle.SetPosition(paddlePos);

    for (auto* ball : balls)
    {
        if (!ball) continue;

        if (ball->IsAttached())
        {
            sf::Vector2f newPosition = paddle.GetPosition();
			newPosition.x += paddle.GetWidth() / 2.0f;
            ball->SetPosition(newPosition);
            continue;
        }

        sf::Vector2f ballPos = ball->GetPosition();
        sf::Vector2f ballVel = ball->GetVelocity();
        ballPos.x += ballVel.x * dt;
        ballPos.y += ballVel.y * dt;
        ball->SetPosition(ballPos);
    }

    for (auto* ability : abilities)
    {
        if (!ability || !ability->IsAlive())
            continue;

        sf::Vector2f pos = ability->GetPosition();
        pos.y += g_AbilityFallSpeed * dt;
        ability->SetPosition(pos);
    }
}

} // namespace Breakout
