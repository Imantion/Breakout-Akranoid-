#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <array>

#include "entities/Paddle.hpp"
#include "entities/Ball.hpp"
#include "entities/Brick.hpp"

namespace Breakout
{

/// Flyweight renderer: owns a single shared brick texture that all bricks
/// reference through a lightweight sf::Sprite repositioned per brick.
class RenderSystem
{
public:
    RenderSystem();

    void Render(sf::RenderWindow& window,
                const Paddle& paddle,
                const Ball& ball,
                const std::vector<Brick>& bricks);

private:
    void _createBrickTexture();

    sf::RenderTexture m_BrickTexture;
};

} // namespace Breakout
