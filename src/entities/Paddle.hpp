#pragma once

#include "Actor.hpp"

namespace Breakout
{

class Paddle : public Actor
{
public:
    Paddle(sf::Vector2f position, sf::Vector2f size);

    void SetDirection(float direction);

    float         GetDirection() const;
    sf::FloatRect GetBounds()    const;

    void Draw(sf::RenderWindow& window) const;

protected:
    void SyncShapePosition() override;

private:
    float              m_Direction;
    sf::RectangleShape m_Shape;
};

} // namespace Breakout
