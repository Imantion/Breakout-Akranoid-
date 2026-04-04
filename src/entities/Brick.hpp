#pragma once

#include "Actor.hpp"

namespace Breakout
{

class Brick : public Actor
{
public:
    Brick(sf::Vector2f position, sf::Vector2f size, int colorIndex);

    void OnHit() override;

    bool          IsAlive()   const;
    sf::Color     GetColor()  const;
    sf::FloatRect GetBounds() const;

    void Draw(sf::RenderWindow& window) const;

protected:
    void SyncShapePosition() override;

private:
    bool               m_IsAlive;
    sf::Color          m_Color;
    sf::RectangleShape m_Shape;
};

} // namespace Breakout
