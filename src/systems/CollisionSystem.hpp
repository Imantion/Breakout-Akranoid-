#pragma once

#include <memory>
#include <vector>
#include <span>

#include "entities/Ball.hpp"
#include "entities/Paddle.hpp"
#include "entities/Brick.hpp"
#include "entities/Ability.hpp"

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
    void Update(std::span<Ball> balls, Paddle& paddle,
                std::span<std::unique_ptr<Brick>> bricks,
                std::span<std::unique_ptr<Ability>> abilities) const;

private:
    void _clampPaddleToWindow(Paddle& paddle) const;
    void _handleWallCollisions(std::span<Ball> balls) const;
    void _handlePaddleCollision(std::span<Ball> balls, const Paddle& paddle) const;
    void _handleBrickCollisions(std::span<Ball> balls, std::span<std::unique_ptr<Brick>> bricks) const;
    void _handleAbilityCollisions(std::span<std::unique_ptr<Ability>> abilities, const Paddle& paddle) const;
    void _handleAbilityBottomCollision(std::span<std::unique_ptr<Ability>> abilities) const;
    auto _AABBCircleCollision(const sf::Vector2f& circlePos, float radius, const sf::Vector2f& rectPos,
        const sf::Vector2f& rectSize) const -> Collision;
    bool _AABBOverlap(const sf::Vector2f& posA, const sf::Vector2f& sizeA,
                      const sf::Vector2f& posB, const sf::Vector2f& sizeB) const;
};

} // namespace Breakout
