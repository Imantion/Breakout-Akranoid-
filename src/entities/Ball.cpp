#include "Ball.hpp"

namespace Breakout
{

Ball::Ball(const sf::Texture& texture, sf::Vector2f position, float radius)
    : Actor(texture, position, radius * 2.0f, radius * 2.0f)
    , m_Radius(radius)
    , m_Velocity({0.0f, 0.0f})
{
    m_Sprite.setOrigin({m_Radius, m_Radius});
    m_Sprite.setPosition(m_Position);
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

} // namespace Breakout
