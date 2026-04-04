#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <span>

#include "entities/Paddle.hpp"
#include "entities/Ball.hpp"
#include "entities/Brick.hpp"

namespace Breakout
{

class RenderSystem
{
public:
    void Render(sf::RenderWindow& window,
                const Paddle& paddle,
                const std::span<Ball> balls,
                const std::vector<Brick>& bricks) const;
};

} // namespace Breakout
