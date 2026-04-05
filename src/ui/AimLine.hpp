#pragma once

#include <SFML/Graphics.hpp>

namespace Breakout
{

class AimLine
{
public:
    void Update(sf::Vector2f origin, sf::Vector2f target);
    void SetVisibility(bool visible);

    bool IsVisible() const;
    const sf::VertexArray& GetLine() const;

private:
    sf::VertexArray m_Line{sf::PrimitiveType::Lines, 2};
    bool            m_Visible = false;
};

} // namespace Breakout
