#include "Brick.hpp"

#include "core/Game.hpp"
#include "events/Events.hpp"
#include "events/EventBus.hpp"

namespace Breakout
{

namespace
{

constexpr std::array<sf::Color, 5> g_RowColors = {
    sf::Color(255, 92, 92),   // red
    sf::Color(255, 172, 92),  // orange
    sf::Color(92, 255, 92),   // green
    sf::Color(92, 172, 255),  // blue
    sf::Color(172, 92, 255),  // purple
};
} // anonymous namespace

Brick::Brick(EntityType type, const sf::Texture& texture, sf::Vector2f position,
             float width, float height, int colorIndex)
    : Actor(type, texture, position, width, height)
    , m_IsAlive(true)
    , m_Color(g_RowColors[colorIndex % static_cast<int>(g_RowColors.size())])
{
    m_Sprite.setColor(m_Color);
}

bool Brick::IsAlive() const
{
    return m_IsAlive;
}

sf::Color Brick::GetColor() const
{
    return m_Color;
}

void Brick::Kill(uuids::uuid killedBy)
{
    m_IsAlive = false;
    Game::Get()->GetEventBus().Publish(BrickDeathEvent{.brickUUID = m_UUID, .killerUUID = killedBy});
}

} // namespace Breakout
