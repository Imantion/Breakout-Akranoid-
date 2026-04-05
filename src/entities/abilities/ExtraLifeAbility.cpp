#include "ExtraLifeAbility.hpp"
#include "scenes/GameplayScene.hpp"

namespace Breakout
{

ExtraLifeAbility::ExtraLifeAbility(const sf::Texture& texture, sf::Vector2f position, float size)
    : Ability(texture, position, size)
{
}

void ExtraLifeAbility::Apply(GameplayContext& context)
{
    context.scene.AddLife();
}

} // namespace Breakout
