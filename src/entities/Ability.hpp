#pragma once

#include "Actor.hpp"
#include "GameplayContext.hpp"

namespace Breakout
{

class Ability : public Actor
{
public:
    Ability(const sf::Texture& texture, sf::Vector2f position, float size);

    virtual void Apply(GameplayContext& context) = 0;

    bool IsAlive() const;
    void Kill();

private:
    bool m_IsAlive;
};

} // namespace Breakout
