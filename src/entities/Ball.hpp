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

	void         IncrementCombo() { ++m_ComboCount; }
	void         ResetCombo() { m_ComboCount = 0; }
	uint32_t     GetComboCount() const { return m_ComboCount; }

    sf::CircleShape m_circle;
private:
    float        m_Radius;
    sf::Vector2f m_Velocity;
    BallState    m_State;
    uint32_t     m_ComboCount;
};

} // namespace Breakout
