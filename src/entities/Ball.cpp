#include "Ball.hpp"

namespace Breakout
{

Ball::Ball(const sf::Texture& texture, sf::Vector2f position, float radius)
    : Actor(EntityType::Ball, texture, position, radius * 2.0f, radius * 2.0f)
    , m_Radius(radius)
    , m_Velocity({0.0f, 0.0f})
    , m_State(BallState::Free)
{
    m_Sprite.setOrigin({m_Radius, m_Radius});
    m_Sprite.setPosition(m_Position);
}

void Ball::SetVelocity(sf::Vector2f velocity)
{
    m_Velocity = velocity;
}

void Ball::SetState(BallState state)
{
    m_State = state;
}

float Ball::GetRadius() const
{
    return m_Radius;
}

sf::Vector2f Ball::GetVelocity() const
{
    return m_Velocity;
}

BallState Ball::GetState() const
{
    return m_State;
}

bool Ball::IsAttached() const
{
    return m_State == BallState::Attached;
}

} // namespace Breakout
