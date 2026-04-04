#include "Paddle.hpp"

namespace Breakout
{

Paddle::Paddle(sf::Vector2f position, sf::Vector2f size)
    : Actor(position, size)
    , m_Direction(0.0f)
    , m_Shape(m_Size)
{
    m_Shape.setPosition(m_Position);
    m_Shape.setFillColor(sf::Color::White);
}

void Paddle::SetDirection(float direction)
{
    m_Direction = direction;
}

float Paddle::GetDirection() const
{
    return m_Direction;
}

sf::FloatRect Paddle::GetBounds() const
{
    return m_Shape.getGlobalBounds();
}

void Paddle::Draw(sf::RenderWindow& window) const
{
    window.draw(m_Shape);
}

void Paddle::SyncShapePosition()
{
    m_Shape.setPosition(m_Position);
}

} // namespace Breakout
