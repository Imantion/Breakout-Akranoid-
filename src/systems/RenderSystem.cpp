#include "RenderSystem.hpp"
#include "Constants.hpp"

namespace Breakout
{

RenderSystem::RenderSystem()
    : m_BrickTexture(sf::Vector2u{
          static_cast<unsigned>(g_BrickWidth),
          static_cast<unsigned>(g_BrickHeight)})
{
    CreateBrickTexture();
}

void RenderSystem::CreateBrickTexture()
{
    m_BrickTexture.clear(sf::Color::White);

    sf::RectangleShape border({g_BrickWidth - 2.0f, g_BrickHeight - 2.0f});
    border.setPosition({1.0f, 1.0f});
    border.setFillColor(sf::Color::White);
    border.setOutlineThickness(-1.0f);
    border.setOutlineColor(sf::Color(255, 255, 255, 80));

    m_BrickTexture.draw(border);
    m_BrickTexture.display();
}

void RenderSystem::Render(sf::RenderWindow& window,
                          const Paddle& paddle,
                          const Ball& ball,
                          const std::vector<Brick>& bricks)
{
    window.clear(sf::Color(30, 30, 46));

    // Render bricks using Flyweight: one shared texture, reused sprite
    sf::Sprite brickSprite(m_BrickTexture.getTexture());

    for (const auto& brick : bricks)
    {
        if (!brick.IsAlive())
            continue;

        brickSprite.setPosition(brick.GetPosition());
        brickSprite.setColor(brick.GetColor());
        window.draw(brickSprite);
    }

    paddle.Draw(window);
    ball.Draw(window);

    window.display();
}

} // namespace Breakout
