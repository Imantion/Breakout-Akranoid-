#include "InvulnerableBrick.hpp"

namespace Breakout
{

InvulnerableBrick::InvulnerableBrick(const sf::Texture& texture, sf::Vector2f position,
                                     float width, float height, int colorIndex)
    : Brick(EntityType::Invulnerable, texture, position, width, height, colorIndex)
{
}

void InvulnerableBrick::OnHit(uuids::uuid hitWith)
{
}

bool InvulnerableBrick::IsDestructible() const
{
    return false;
}

} // namespace Breakout
