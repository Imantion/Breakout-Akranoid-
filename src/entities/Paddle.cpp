#include "Paddle.hpp"

namespace Breakout
{

Paddle::Paddle(const sf::Texture& texture, sf::Vector2f position, float width, float height)
    : Actor(EntityType::Player, texture, position, width, height)
    , m_Direction(0.0f)
{
}

void Paddle::SetDirection(float direction)
{
    m_Direction = direction;
}

float Paddle::GetDirection() const
{
    return m_Direction;
}

} // namespace Breakout
