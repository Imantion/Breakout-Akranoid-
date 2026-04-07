#pragma once

#include <SFML/Graphics.hpp>
#include "core/EntityUUID.hpp"

namespace Breakout
{

class Actor
{
public:
    Actor(EntityType type, const sf::Texture& texture, sf::Vector2f position, float width, float height);
    virtual ~Actor() = default;

    Actor(const Actor&) = default;
    Actor& operator=(const Actor&) = default;
    Actor(Actor&&) = default;
    Actor& operator=(Actor&&) = default;

    virtual void OnHit() {}

    const uuids::uuid& GetUUID()     const;
    EntityType          GetType()     const;
    void          SetPosition(sf::Vector2f position);
    void          SetWidth(float width);
    sf::Vector2f  GetPosition() const;
    float         GetWidth()    const;
    float         GetHeight()   const;
    sf::Vector2f  GetSize()     const;
    sf::FloatRect GetBounds()   const;

    const sf::Sprite& GetSprite() const;

    void Draw(sf::RenderWindow& window) const;

protected:
    uuids::uuid  m_UUID;
    EntityType   m_EntityType;
    sf::Sprite   m_Sprite;
    sf::Vector2f m_Position;
    float        m_Width;
    float        m_Height;

    void ScaleToFit();
};

} // namespace Breakout
