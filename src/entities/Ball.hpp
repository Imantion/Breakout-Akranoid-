#pragma once

#include "Actor.hpp"

namespace Breakout
{

class Ball : public Actor
{
public:
    Ball(const sf::Texture& texture, sf::Vector2f position, float radius);

    void SetVelocity(sf::Vector2f velocity);

    float        GetRadius()   const;
    sf::Vector2f GetVelocity() const;

private:
    float        m_Radius;
    sf::Vector2f m_Velocity;
};

} // namespace Breakout
