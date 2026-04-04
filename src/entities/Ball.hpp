#pragma once

#include "Actor.hpp"

namespace Breakout
{

class Ball : public Actor
{
public:
    Ball(sf::Vector2f position, float radius);

    void SetVelocity(sf::Vector2f velocity);

    float         GetRadius()   const;
    sf::Vector2f  GetVelocity() const;
    sf::FloatRect GetBounds()   const;

    void Draw(sf::RenderWindow& window) const;

protected:
    void SyncShapePosition() override;

private:
    float           m_Radius;
    sf::Vector2f    m_Velocity;
    sf::CircleShape m_Shape;
};

} // namespace Breakout
