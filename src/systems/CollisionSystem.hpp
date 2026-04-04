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
    void ClampPaddleToWindow(Paddle& paddle) const;
    void HandleWallCollisions(Ball& ball) const;
    void HandlePaddleCollision(Ball& ball, const Paddle& paddle) const;
    void HandleBrickCollisions(Ball& ball, std::vector<Brick>& bricks) const;
    auto AABBCircleCollision(const sf::Vector2f& circlePos, float radius, const sf::Vector2f& rectPos, 
        const sf::Vector2f& rectSize) const -> Collision;
};

} // namespace Breakout
