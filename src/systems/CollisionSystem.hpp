#pragma once

#include <vector>
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
    void Update(Ball& ball, Paddle& paddle, std::vector<Brick>& bricks) const;

private:
    void _clampPaddleToWindow(Paddle& paddle) const;
    void _handleWallCollisions(Ball& ball) const;
    void _handlePaddleCollision(Ball& ball, const Paddle& paddle) const;
    void _handleBrickCollisions(Ball& ball, std::vector<Brick>& bricks) const;
    auto _AABBCircleCollision(const sf::Vector2f& circlePos, float radius, const sf::Vector2f& rectPos, 
        const sf::Vector2f& rectSize) const -> Collision;
};

} // namespace Breakout
