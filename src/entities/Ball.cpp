#include "Ball.hpp"

namespace Breakout
{

Ball::Ball(const sf::Texture& texture, sf::Vector2f position, float radius)
    : Actor(EntityType::Ball, texture, position, radius * 2.0f, radius * 2.0f)
    , m_Radius(radius)
    , m_Velocity({0.0f, 0.0f})
    , m_State(BallState::Free)
{
    sf::Rect bounds = m_Sprite.getLocalBounds();
    m_Sprite.setOrigin(bounds.size * 0.5f);
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
