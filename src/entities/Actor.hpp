#pragma once

#include <SFML/Graphics.hpp>

namespace Breakout
{

class Actor
{
public:
    Actor(sf::Vector2f position, sf::Vector2f size);
    virtual ~Actor() = default;

    Actor(const Actor&) = default;
    Actor& operator=(const Actor&) = default;
    Actor(Actor&&) = default;
    Actor& operator=(Actor&&) = default;

    virtual void OnHit() {}

    void         SetPosition(sf::Vector2f position);
    sf::Vector2f GetPosition() const;
    sf::Vector2f GetSize()     const;

protected:
    sf::Vector2f m_Position;
    sf::Vector2f m_Size;

    virtual void SyncShapePosition() = 0;
};

} // namespace Breakout
