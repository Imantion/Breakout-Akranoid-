#include "CollisionSystem.hpp"
#include "core/Constants.hpp"
#include "core/Game.hpp"
#include "events/Events.hpp"
#include "events/EventBus.hpp"

#include <cmath>
#include <algorithm>

namespace Breakout
{

void CollisionSystem::Update(std::span<Ball*> balls, Paddle& paddle,
                             std::span<Brick*> bricks,
                             std::span<Ability*> abilities) const
{
    _clampPaddleToWindow(paddle);
    _handleWallCollisions(balls);
    _handlePaddleCollision(balls, paddle);
    _handleBrickCollisions(balls, bricks);
    _handleAbilityCollisions(abilities, paddle);
}

void CollisionSystem::_clampPaddleToWindow(Paddle& paddle) const
{
    sf::Vector2f pos = paddle.GetPosition();
    float minX = 0.0f;
    float maxX = g_WindowWidth - paddle.GetSize().x;
    pos.x = std::clamp(pos.x, minX, maxX);
    paddle.SetPosition(pos);
}

void CollisionSystem::_handleWallCollisions(std::span<Ball*> balls) const
{
    for (auto* ball : balls)
    {
        if (!ball || ball->IsAttached())
            continue;

        sf::Vector2f pos = ball->GetPosition();
        sf::Vector2f vel = ball->GetVelocity();
        float r  = ball->GetRadius();
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
            ball->SetPosition(pos);
            ball->SetVelocity(vel);
            Game::Get()->GetEventBus().Publish(BallLostEvent{ball->GetUUID()});
            continue;
        }

        ball->SetPosition(pos);
        ball->SetVelocity(vel);

        if (hit)
            Game::Get()->GetEventBus().Publish(BallHitWallEvent{ball->GetUUID()});
    }
}

void CollisionSystem::_handlePaddleCollision(std::span<Ball*> balls, const Paddle& paddle) const
{
    sf::Vector2f paddlePos  = paddle.GetPosition();
    sf::Vector2f paddleSize = paddle.GetSize();

    for (auto* ball : balls)
    {
        if (!ball || ball->IsAttached())
            continue;

        sf::Vector2f ballPos = ball->GetPosition();
        sf::Vector2f ballVel = ball->GetVelocity();
        float r      = ball->GetRadius();

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
        ball->SetVelocity(ballVel);

        Game::Get()->GetEventBus().Publish(BallHitPaddleEvent{ball->GetUUID()});
    }
}

void CollisionSystem::_handleBrickCollisions(std::span<Ball*> balls, std::span<Brick*> bricks) const
{
    for (auto* ball : balls)
    {
        if (!ball || ball->IsAttached())
            continue;

        sf::Vector2f ballPos = ball->GetPosition();
        sf::Vector2f ballVel = ball->GetVelocity();
        const float r = ball->GetRadius();

        Brick* bestBrick = nullptr;
        Collision bestCollision{};
        float     maxPenetrationSq = -std::numeric_limits<float>::max();

        for (auto* brick : bricks)
        {
            if (!brick || !brick->IsAlive())
                continue;

            Collision collision = _AABBCircleCollision(ballPos, r, brick->GetPosition(), brick->GetSize());
            if (!collision.Hit)
                continue;

            float distSq = collision.DiffVector.x * collision.DiffVector.x
                + collision.DiffVector.y * collision.DiffVector.y;
            float penetrationSq = r * r - distSq;

            if (penetrationSq > maxPenetrationSq)
            {
                maxPenetrationSq = penetrationSq;
                bestBrick = brick;
                bestCollision = collision;
            }
        }

        if (!bestBrick)
            continue;

        bestBrick->OnHit(ball->GetUUID());

        const sf::Vector2f  brickPos = bestBrick->GetPosition();
        const sf::Vector2f  brickSize = bestBrick->GetSize();

        const float overlapLeft = (ballPos.x + r) - brickPos.x;
        const float overlapRight = (brickPos.x + brickSize.x) - (ballPos.x - r);
        const float overlapTop = (ballPos.y + r) - brickPos.y;
        const float overlapBottom = (brickPos.y + brickSize.y) - (ballPos.y - r);

        const float minOverlapX = std::min(overlapLeft, overlapRight);
        const float minOverlapY = std::min(overlapTop, overlapBottom);

        bool resolveX;
        if (minOverlapX < minOverlapY * 0.95f)
            resolveX = true;
        else if (minOverlapY < minOverlapX * 0.95f)
            resolveX = false;
        else
            resolveX = std::abs(ballVel.x) > std::abs(ballVel.y);

        if (resolveX)
        {
            ballVel.x = -ballVel.x;
            ballPos.x += (overlapLeft < overlapRight) ? -overlapLeft : overlapRight;
        }
        else
        {
            ballVel.y = -ballVel.y;
            ballPos.y += (overlapTop < overlapBottom) ? -overlapTop : overlapBottom;
        }

        ball->SetPosition(ballPos);
        ball->SetVelocity(ballVel);

        Game::Get()->GetEventBus().Publish(BallHitBrickEvent{ ball->GetUUID(), bestBrick->GetUUID() });
    }
}

void CollisionSystem::_handleAbilityCollisions(std::span<Ability*> abilities,
                                               const Paddle& paddle) const
{
    sf::Vector2f paddlePos  = paddle.GetPosition();
    sf::Vector2f paddleSize = paddle.GetSize();

    for (auto* ability : abilities)
    {
        if (!ability || !ability->IsAlive())
            continue;

        auto abilityPos  = ability->GetPosition();
        auto abilitySize = ability->GetSize();

        if (_AABBOverlap(paddlePos, paddleSize, abilityPos, abilitySize))
        {
            Game::Get()->GetEventBus().Publish(AbilityPickedUpEvent{ability->GetUUID()});
        }
    }
}

void CollisionSystem::_handleAbilityBottomCollision(std::span<Ability*> abilities) const
{
    for (auto* ability : abilities)
    {
        if (!ability || !ability->IsAlive())
            continue;

        sf::Vector2f pos = ability->GetPosition();

        if (pos.y > g_WindowHeight)
            Game::Get()->GetEventBus().Publish(AbilityFallOutOfBoundsEvent{ability->GetUUID()});
    }
}

auto CollisionSystem::_AABBCircleCollision(const sf::Vector2f& circlePos, float radius,
    const sf::Vector2f& rectPos, const sf::Vector2f& rectSize) const -> Collision
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

bool CollisionSystem::_AABBOverlap(const sf::Vector2f& posA, const sf::Vector2f& sizeA,
                                   const sf::Vector2f& posB, const sf::Vector2f& sizeB) const
{
    return posA.x < posB.x + sizeB.x &&
           posA.x + sizeA.x > posB.x &&
           posA.y < posB.y + sizeB.y &&
           posA.y + sizeA.y > posB.y;
}

} // namespace Breakout
