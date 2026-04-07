#include "Actor.hpp"

namespace Breakout
{

Actor::Actor(EntityType type, const sf::Texture& texture, sf::Vector2f position, float width, float height)
    : m_UUID(GenerateUUID())
    , m_EntityType(type)
    , m_Sprite(texture)
    , m_Position(position)
    , m_Width(width)
    , m_Height(height)
{
    ScaleToFit();
    m_Sprite.setPosition(m_Position);
}

const uuids::uuid& Actor::GetUUID() const
{
    return m_UUID;
}

EntityType Actor::GetType() const
{
    return m_EntityType;
}

void Actor::SetPosition(sf::Vector2f position)
{
    m_Position = position;
    m_Sprite.setPosition(m_Position);
}

void Actor::SetWidth(float width)
{
    m_Width = width;
    ScaleToFit();
}

sf::Vector2f Actor::GetPosition() const
{
    return m_Position;
}

float Actor::GetWidth() const
{
    return m_Width;
}

float Actor::GetHeight() const
{
    return m_Height;
}

sf::Vector2f Actor::GetSize() const
{
    return {m_Width, m_Height};
}

const sf::Sprite& Actor::GetSprite() const
{
    return m_Sprite;
}

sf::FloatRect Actor::GetBounds() const
{
    return m_Sprite.getGlobalBounds();
}

void Actor::Draw(sf::RenderWindow& window) const
{
    window.draw(m_Sprite);
}

void Actor::ScaleToFit()
{
    auto texSize = m_Sprite.getTexture().getSize();
    float scaleX = m_Width  / static_cast<float>(texSize.x);
    float scaleY = m_Height / static_cast<float>(texSize.y);
    m_Sprite.setScale({scaleX, scaleY});
}

} // namespace Breakout
