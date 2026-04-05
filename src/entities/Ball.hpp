#pragma once

#include "Actor.hpp"

#include <cstdint>

namespace Breakout
{

enum class BallState : uint8_t
{
    Attached,
    Free
};

class Ball : public Actor
{
public:
    Ball(const sf::Texture& texture, sf::Vector2f position, float radius);

    void SetVelocity(sf::Vector2f velocity);
    void SetState(BallState state);

    float        GetRadius()   const;
    sf::Vector2f GetVelocity() const;
    BallState    GetState()    const;
    bool         IsAttached()  const;

private:
    float        m_Radius;
    sf::Vector2f m_Velocity;
    BallState    m_State;
};

} // namespace Breakout
