#pragma once

#include "Actor.hpp"

#include <array>
#include <cstdint>
#include <vector>

namespace Breakout
{

class Brick : public Actor
{
public:
    Brick(const sf::Texture& texture, sf::Vector2f position,
          float width, float height, int colorIndex);

    void OnHit() override = 0;

    bool      IsAlive()        const;
    void      Kill();
    virtual bool IsDestructible() const = 0;
    sf::Color GetColor()       const;

protected:
    bool      m_IsAlive;
    sf::Color m_Color;

    static sf::Color ColorFromIndex(int colorIndex);
};

} // namespace Breakout
