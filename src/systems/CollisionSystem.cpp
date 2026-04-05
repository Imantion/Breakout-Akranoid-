#include "CollisionSystem.hpp"
#include "Constants.hpp"
#include "Game.hpp"
#include "Events.hpp"

#include <cmath>
#include <algorithm>

namespace Breakout
{

void CollisionSystem::Update(std::span<Ball> balls, Paddle& paddle,
                             std::vector<Brick>& bricks) const
{
    _clampPaddleToWindow(paddle);
    _handleWallCollisions(balls);
    _handlePaddleCollision(balls, paddle);
    _handleBrickCollisions(balls, bricks);
}

void CollisionSystem::_clampPaddleToWindow(Paddle& paddle) const
{
    auto pos = paddle.GetPosition();
    float minX = 0.0f;
    float maxX = g_WindowWidth - paddle.GetSize().x;
    pos.x = std::clamp(pos.x, minX, maxX);
    paddle.SetPosition(pos);
}

void CollisionSystem::_handleWallCollisions(std::span<Ball> balls) const
{
    for (auto& ball : balls)
    {
        auto pos = ball.GetPosition();
        auto vel = ball.GetVelocity();
        float r  = ball.GetRadius();
        bool hit = false;

        if (pos.x - r <= 0.0f)
        {
            pos.x = r;
            vel.x = std::abs(vel.x);
            hit = true;
        }
        else if (pos.x + r >= g_WindowWidth)
        {
            pos.x = g_WindowWidth - r;
            vel.x = -std::abs(vel.x);
            hit = true;
        }

        if (pos.y - r <= 0.0f)
        {
            pos.y = r;
            vel.y = std::abs(vel.y);
            hit = true;
        }
        else if (pos.y + r >= g_WindowHeight)
        {
            ball.SetPosition(pos);
            ball.SetVelocity(vel);
            Game::Get()->GetEventBus().Publish(BallLostEvent{ball});
            return;
        }

        ball.SetPosition(pos);
        ball.SetVelocity(vel);

        if (hit)
            Game::Get()->GetEventBus().Publish(BallHitWallEvent{ball});
    }
}

void CollisionSystem::_handlePaddleCollision(std::span<Ball> balls, const Paddle& paddle) const
{
    auto paddlePos  = paddle.GetPosition();
    auto paddleSize = paddle.GetSize();

    for(auto& ball : balls)
    {
        auto ballPos = ball.GetPosition();
        auto ballVel = ball.GetVelocity();
        float r      = ball.GetRadius();

        if (ballVel.y <= 0.0f)
            continue;

        Collision collision = _AABBCircleCollision(ballPos, r, paddlePos, paddleSize);

        if (!collision.Hit)
            continue;

        float hitNormalized = (ballPos.x - paddlePos.x) / paddleSize.x;
        hitNormalized = std::clamp(hitNormalized, 0.0f, 1.0f);

        float angle = (hitNormalized - 0.5f) * 2.0f * g_MaxBounceAngle;

        float speed = std::sqrt(ballVel.x * ballVel.x + ballVel.y * ballVel.y);
        ballVel.x = speed * std::sin(angle);
        ballVel.y = -speed * std::cos(angle);

        ballPos.y = paddlePos.y - r;
        ball.SetVelocity(ballVel);

        Game::Get()->GetEventBus().Publish(BallHitPaddleEvent{ball, paddle});
    }
}

void CollisionSystem::_handleBrickCollisions(std::span<Ball> balls, std::vector<Brick>& bricks) const
{
    for (auto& ball : balls)
    {
        auto ballPos = ball.GetPosition();
        auto ballVel = ball.GetVelocity();
        float r      = ball.GetRadius();

        for (auto& brick : bricks)
        {
            if (!brick.IsAlive())
                continue;

            auto brickPos  = brick.GetPosition();
            auto brickSize = brick.GetSize();

            Collision collision = _AABBCircleCollision(ballPos, r, brickPos, brickSize);

            if (!collision.Hit)
                continue;

            brick.OnHit();

            float overlapLeft   = (ballPos.x + r) - brickPos.x;
            float overlapRight  = (brickPos.x + brickSize.x) - (ballPos.x - r);
            float overlapTop    = (ballPos.y + r) - brickPos.y;
            float overlapBottom = (brickPos.y + brickSize.y) - (ballPos.y - r);

            float minOverlapX = std::min(overlapLeft, overlapRight);
            float minOverlapY = std::min(overlapTop, overlapBottom);

            if (minOverlapX < minOverlapY)
            {
                ballVel.x = -ballVel.x;
                float offset = std::abs(collision.DiffVector.x - r);
                ballPos.x += (overlapLeft < overlapRight) ? -offset : offset;
            }
            else
            {
                ballVel.y = -ballVel.y;
                float offset = std::abs(collision.DiffVector.y - r);
                ballPos.y += (overlapTop < overlapBottom) ? -offset : offset;
            }

            ball.SetPosition(ballPos);
            ball.SetVelocity(ballVel);

            Game::Get()->GetEventBus().Publish(BallHitBrickEvent{ball, brick});
            break;
        }
    }
}

auto CollisionSystem::_AABBCircleCollision(const sf::Vector2f& circlePos, float radius, const sf::Vector2f& rectPos, 
    const sf::Vector2f& rectSize) const -> Collision
{
    float closestX = std::clamp(circlePos.x, rectPos.x, rectPos.x + rectSize.x);
    float closestY = std::clamp(circlePos.y, rectPos.y, rectPos.y + rectSize.y);

    float distX = circlePos.x - closestX;
    float distY = circlePos.y - closestY;

    return Collision{
        .Hit = distX * distX + distY * distY <= radius * radius, 
        .ClosestPoint = sf::Vector2f(closestX, closestY), 
        .DiffVector = sf::Vector2f(distX, distY)
    };
}

} // namespace Breakout
