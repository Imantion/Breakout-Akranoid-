#include "Ability.hpp"
#include "core/Constants.hpp"

namespace Breakout
{

Ability::Ability(const sf::Texture& texture, sf::Vector2f position, float size)
    : Actor(EntityType::Ability, texture, position, size, size)
    , m_IsAlive(true)
{
}

bool Ability::IsAlive() const
{
    return m_IsAlive;
}

void Ability::Kill()
{
    m_IsAlive = false;
}

} // namespace Breakout
