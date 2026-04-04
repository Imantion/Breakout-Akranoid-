#pragma once

#include <vector>
#include <span>

#include "entities/Ball.hpp"
#include "entities/Paddle.hpp"
#include "entities/Brick.hpp"

namespace Breakout
{

class CollisionSystem
{
public:

struct Collision
{
    bool         Hit;
    sf::Vector2f ClosestPoint;
    sf::Vector2f DiffVector;
};

public:
    void Update(std::span<Ball> balls, Paddle& paddle, std::vector<Brick>& bricks) const;

private:
    void _clampPaddleToWindow(Paddle& paddle) const;
    void _handleWallCollisions(std::span<Ball> balls) const;
    void _handlePaddleCollision(std::span<Ball> balls, const Paddle& paddle) const;
    void _handleBrickCollisions(std::span<Ball> balls, std::vector<Brick>& bricks) const;
    auto _AABBCircleCollision(const sf::Vector2f& circlePos, float radius, const sf::Vector2f& rectPos, 
        const sf::Vector2f& rectSize) const -> Collision;
};

} // namespace Breakout
