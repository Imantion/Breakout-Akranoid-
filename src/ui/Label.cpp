#include "Label.hpp"

namespace Breakout
{

Label::Label(const sf::Font& font, const std::string& text, unsigned int size,
             sf::Vector2f position, sf::Color color)
    : m_Text(font, text, size)
{
    m_Text.setFillColor(color);
    m_Text.setPosition(position);
}

void Label::SetText(const std::string& text)
{
    m_Text.setString(text);
}

void Label::SetPosition(sf::Vector2f position)
{
    m_Text.setPosition(position);
}

void Label::CenterHorizontally(float windowWidth)
{
    auto bounds = m_Text.getLocalBounds();
    float x = (windowWidth - bounds.size.x) / 2.0f - bounds.position.x;
    float y = m_Text.getPosition().y;
    m_Text.setPosition({x, y});
}

sf::FloatRect Label::GetBounds() const
{
    return m_Text.getGlobalBounds();
}

void Label::Draw(sf::RenderWindow& window) const
{
    window.draw(m_Text);
}

} // namespace Breakout
