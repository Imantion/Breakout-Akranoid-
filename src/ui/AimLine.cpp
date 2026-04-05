#include "AimLine.hpp"
#include "Constants.hpp"

#include <cmath>

namespace Breakout
{

void AimLine::Update(sf::Vector2f origin, sf::Vector2f target)
{
    m_Visible = true;

    sf::Vector2f dir = target - origin;
    float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);

    if (length < 1.0f)
    {
        m_Visible = false;
        return;
    }

    dir /= length;

    float clampedLength = std::min(length, g_AimLineLength);
    sf::Vector2f endpoint = origin + dir * clampedLength;

    m_Line[0] = sf::Vertex{.position = origin,   .color = sf::Color(255, 255, 255, 120)};
    m_Line[1] = sf::Vertex{.position = endpoint, .color = sf::Color(255, 255, 255, 40)};
}

void AimLine::SetVisibility(bool visible)
{
    m_Visible = visible;
}

bool AimLine::IsVisible() const
{
    return m_Visible;
}

const sf::VertexArray& AimLine::GetLine() const
{
    return m_Line;
}

} // namespace Breakout
