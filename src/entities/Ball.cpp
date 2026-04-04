#include "Ball.hpp"

namespace Breakout
{

Ball::Ball(sf::Vector2f position, float radius)
    : Actor(position, {radius * 2.0f, radius * 2.0f})
    , m_Radius(radius)
    , m_Velocity({0.0f, 0.0f})
    , m_Shape(m_Radius)
{
    m_Shape.setOrigin({m_Radius, m_Radius});
    m_Shape.setPosition(m_Position);
    m_Shape.setFillColor(sf::Color(255, 200, 60));
}

void Ball::SetVelocity(sf::Vector2f velocity)
{
    m_Velocity = velocity;
}

float Ball::GetRadius() const
{
    return m_Radius;
}

sf::Vector2f Ball::GetVelocity() const
{
    return m_Velocity;
}

sf::FloatRect Ball::GetBounds() const
{
    return m_Shape.getGlobalBounds();
}

void Ball::Draw(sf::RenderWindow& window) const
{
    window.draw(m_Shape);
}

void Ball::SyncShapePosition()
{
    m_Shape.setPosition(m_Position);
}

} // namespace Breakout
