#include "Brick.hpp"

#include "core/Game.hpp"
#include "events/Events.hpp"

namespace Breakout
{

namespace
{

constexpr std::array<uint32_t, 5> g_RowColors = {
    0xE06C75FF, // red
    0xE5C07BFF, // yellow
    0x98C379FF, // green
    0x61AFEFFF, // blue
    0xC678DDFF, // purple
};

} // anonymous namespace

Brick::Brick(EntityType type, const sf::Texture& texture, sf::Vector2f position,
             float width, float height, int colorIndex)
    : Actor(type, texture, position, width, height)
    , m_IsAlive(true)
    , m_Color(ColorFromIndex(colorIndex))
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

sf::Color Brick::ColorFromIndex(int colorIndex)
{
    uint32_t hex = g_RowColors[colorIndex % static_cast<int>(g_RowColors.size())];
    return sf::Color(
        static_cast<uint8_t>((hex >> 24) & 0xFF),
        static_cast<uint8_t>((hex >> 16) & 0xFF),
        static_cast<uint8_t>((hex >> 8)  & 0xFF),
        static_cast<uint8_t>( hex        & 0xFF));
}

void Brick::Kill()
{
    m_IsAlive = false;
    Game::Get()->GetEventBus().Publish(BrickDeathEvent{m_UUID});
}

} // namespace Breakout
