#pragma once

#include "entities/Ability.hpp"

namespace Breakout
{

class WidePaddleAbility : public Ability
{
public:
    WidePaddleAbility(const sf::Texture& texture, float widthMultiplier, sf::Vector2f position, float size);

    void Apply(GameplayContext& context) override;

private:
    float m_WidthMultiplier;
};

} // namespace Breakout
