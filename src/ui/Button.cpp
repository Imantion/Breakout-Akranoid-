#include "Button.hpp"
#include "core/Constants.hpp"

namespace Breakout
{

Button::Button(const sf::Font& font, const std::string& text, unsigned int size,
               sf::Vector2f position, std::function<void()> onClick)
    : m_Text(font, text, size)
    , m_OnClick(std::move(onClick))
    , m_IsHovered(false)
    , m_NormalColor(sf::Color(g_BtnNormalGray, g_BtnNormalGray, g_BtnNormalGray))
    , m_HoverColor(sf::Color::White)
{
    m_Text.setFillColor(m_NormalColor);
    m_Text.setPosition(position);
}

void Button::HandleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
    if (const auto* mouseClick = event.getIf<sf::Event::MouseButtonPressed>())
    {
        if (mouseClick->button != sf::Mouse::Button::Left)
            return;

        auto mousePos = window.mapPixelToCoords(mouseClick->position);
        if (m_Text.getGlobalBounds().contains(mousePos))
            m_OnClick();
    }
}

void Button::Update(const sf::RenderWindow& window)
{
    auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    m_IsHovered = m_Text.getGlobalBounds().contains(mousePos);
    m_Text.setFillColor(m_IsHovered ? m_HoverColor : m_NormalColor);
}

void Button::CenterHorizontally(float windowWidth)
{
    auto bounds = m_Text.getLocalBounds();
    float x = (windowWidth - bounds.size.x) / 2.0f - bounds.position.x;
    float y = m_Text.getPosition().y;
    m_Text.setPosition({x, y});
}

void Button::Draw(sf::RenderWindow& window) const
{
    window.draw(m_Text);
}

} // namespace Breakout
