#include "WidePaddleAbility.hpp"
#include "core/Constants.hpp"
#include "entities/Paddle.hpp"
#include "scenes/GameplayScene.hpp"

namespace Breakout
{

WidePaddleAbility::WidePaddleAbility(const sf::Texture& texture, float widthMultiplier, sf::Vector2f position, float size)
    : Ability(texture, position, size)
{
	m_WidthMultiplier = widthMultiplier;
}

void WidePaddleAbility::Apply(GameplayContext& context)
{
    float originalWidth = g_PaddleWidth;
    float modifiedWidth     = g_PaddleWidth * m_WidthMultiplier;
    Paddle& paddle      = context.paddle;

    context.scene.AddEffect(
        EffectType::WidePaddle,
        g_WidePaddleDuration,
        [&paddle, modifiedWidth]()     { paddle.SetWidth(modifiedWidth); },
        [&paddle, originalWidth]() { paddle.SetWidth(originalWidth); });
}

} // namespace Breakout
