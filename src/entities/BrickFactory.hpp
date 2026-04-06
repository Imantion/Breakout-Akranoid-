#pragma once

#include "Brick.hpp"

#include <memory>

#include <SFML/System/Vector2.hpp>

namespace Breakout
{

class BrickFactory
{
public:
    static std::unique_ptr<Brick> CreateDestructible(sf::Vector2f position,
                                                     float width, float height,
                                                     int colorIndex, int hp);

    static std::unique_ptr<Brick> CreateInvulnerable(sf::Vector2f position,
                                                     float width, float height,
                                                     int colorIndex);
};

} // namespace Breakout
