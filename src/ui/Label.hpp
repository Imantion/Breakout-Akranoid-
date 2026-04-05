#pragma once

#include <SFML/Graphics.hpp>
#include <string>

namespace Breakout
{

class Label
{
public:
    Label(const sf::Font& font, const std::string& text, unsigned int size,
          sf::Vector2f position, sf::Color color = sf::Color::White);

    void SetText(const std::string& text);
    void SetPosition(sf::Vector2f position);
    void CenterHorizontally(float windowWidth);

    sf::FloatRect GetBounds() const;

    void Draw(sf::RenderWindow& window) const;

private:
    sf::Text m_Text;
};

} // namespace Breakout
