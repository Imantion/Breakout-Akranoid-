#pragma once

#include "Actor.hpp"

namespace Breakout
{

class Brick : public Actor
{
public:
    Brick(const sf::Texture& texture, sf::Vector2f position, float width, float height, int colorIndex);

    void OnHit() override;

    bool      IsAlive()  const;
    sf::Color GetColor() const;

private:
    bool      m_IsAlive;
    sf::Color m_Color;
};

} // namespace Breakout
