#include "Actor.hpp"

namespace Breakout
{

Actor::Actor(sf::Vector2f position, sf::Vector2f size)
    : m_Position(position)
    , m_Size(size)
{
}

void Actor::SetPosition(sf::Vector2f position)
{
    m_Position = position;
    SyncShapePosition();
}

sf::Vector2f Actor::GetPosition() const
{
    return m_Position;
}

sf::Vector2f Actor::GetSize() const
{
    return m_Size;
}

} // namespace Breakout
