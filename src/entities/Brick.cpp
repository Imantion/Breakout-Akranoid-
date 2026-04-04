#include "Brick.hpp"

#include <array>

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

sf::Color ColorFromHex(uint32_t hex)
{
    return sf::Color(
        static_cast<uint8_t>((hex >> 24) & 0xFF),
        static_cast<uint8_t>((hex >> 16) & 0xFF),
        static_cast<uint8_t>((hex >> 8)  & 0xFF),
        static_cast<uint8_t>( hex        & 0xFF));
}

} // anonymous namespace

Brick::Brick(sf::Vector2f position, sf::Vector2f size, int colorIndex)
    : Actor(position, size)
    , m_IsAlive(true)
    , m_Color(ColorFromHex(g_RowColors[colorIndex % static_cast<int>(g_RowColors.size())]))
    , m_Shape(m_Size)
{
    m_Shape.setPosition(m_Position);
    m_Shape.setFillColor(m_Color);
}

void Brick::OnHit()
{
    m_IsAlive = false;
}

bool Brick::IsAlive() const
{
    return m_IsAlive;
}

sf::Color Brick::GetColor() const
{
    return m_Color;
}

sf::FloatRect Brick::GetBounds() const
{
    return m_Shape.getGlobalBounds();
}

void Brick::Draw(sf::RenderWindow& window) const
{
    window.draw(m_Shape);
}

void Brick::SyncShapePosition()
{
    m_Shape.setPosition(m_Position);
}

} // namespace Breakout
