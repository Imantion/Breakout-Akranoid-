#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

namespace Breakout
{

class Button
{
public:
    Button(const sf::Font& font, const std::string& text, unsigned int size,
           sf::Vector2f position, std::function<void()> onClick);

    void HandleEvent(const sf::Event& event, const sf::RenderWindow& window);
    void Update(const sf::RenderWindow& window);
    void CenterHorizontally(float windowWidth);

    void Draw(sf::RenderWindow& window) const;

private:
    sf::Text               m_Text;
    std::function<void()>  m_OnClick;
    bool                   m_IsHovered;

    sf::Color              m_NormalColor;
    sf::Color              m_HoverColor;
};

} // namespace Breakout
