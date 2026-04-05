#pragma once

#include "entities/Ability.hpp"

namespace Breakout
{

class MultiBallAbility : public Ability
{
public:
    MultiBallAbility(const sf::Texture& texture, sf::Vector2f position, float size);

    void Apply(GameplayContext& context) override;
};

} // namespace Breakout
