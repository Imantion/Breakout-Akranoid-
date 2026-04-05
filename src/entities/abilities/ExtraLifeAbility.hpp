#pragma once

#include "entities/Ability.hpp"

namespace Breakout
{

class ExtraLifeAbility : public Ability
{
public:
    ExtraLifeAbility(const sf::Texture& texture, sf::Vector2f position, float size);

    void Apply(GameplayContext& context) override;
};

} // namespace Breakout
