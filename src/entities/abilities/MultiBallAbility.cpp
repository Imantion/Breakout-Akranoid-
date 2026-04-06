#include "MultiBallAbility.hpp"
#include "core/Constants.hpp"
#include "scenes/GameplayScene.hpp"

namespace Breakout
{

MultiBallAbility::MultiBallAbility(const sf::Texture& texture, sf::Vector2f position, float size)
    : Ability(texture, position, size)
{
}

void MultiBallAbility::Apply(GameplayContext& context)
{
    context.scene.AddBall(
        context.paddle.GetPosition(),
        sf::Vector2f{g_BallSpeed * 0.7f, -g_BallSpeed * 0.7f});
}

} // namespace Breakout
