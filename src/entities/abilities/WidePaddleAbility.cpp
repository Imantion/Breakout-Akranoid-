#include "WidePaddleAbility.hpp"
#include "Constants.hpp"
#include "entities/Paddle.hpp"
#include "scenes/GameplayScene.hpp"

namespace Breakout
{

WidePaddleAbility::WidePaddleAbility(const sf::Texture& texture, sf::Vector2f position, float size)
    : Ability(texture, position, size)
{
}

void WidePaddleAbility::Apply(GameplayContext& context)
{
    float originalWidth = g_PaddleWidth;
    float wideWidth     = g_PaddleWidth * g_WidePaddleMultiplier;
    Paddle& paddle      = context.paddle;

    context.scene.AddEffect(
        EffectType::WidePaddle,
        g_WidePaddleDuration,
        [&paddle, wideWidth]()     { paddle.SetWidth(wideWidth); },
        [&paddle, originalWidth]() { paddle.SetWidth(originalWidth); });
}

} // namespace Breakout
