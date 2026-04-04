#pragma once

#include "Actor.hpp"

namespace Breakout
{

class Paddle : public Actor
{
public:
    Paddle(const sf::Texture& texture, sf::Vector2f position, float width, float height);

    void SetDirection(float direction);

    float GetDirection() const;

private:
    float m_Direction;
};

} // namespace Breakout
