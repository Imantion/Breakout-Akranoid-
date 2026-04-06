#include "RenderSystem.hpp"

namespace Breakout
{

void RenderSystem::BeginFrame(sf::RenderWindow& window)
{
    window.clear(sf::Color(30, 30, 46));
}

void RenderSystem::EndFrame(sf::RenderWindow& window)
{
    window.display();
}

void RenderSystem::DrawActor(sf::RenderWindow& window, const Actor& actor)
{
    window.draw(actor.GetSprite());
}

void RenderSystem::DrawBricks(sf::RenderWindow& window, std::span<std::unique_ptr<Brick>> bricks)
{
    for (const auto& brick : bricks)
    {
        if (brick && brick->IsAlive())
            brick->Draw(window);
    }
}

void RenderSystem::DrawLabel(sf::RenderWindow& window, const Label& label)
{
    label.Draw(window);
}

void RenderSystem::DrawButton(sf::RenderWindow& window, const Button& button)
{
    button.Draw(window);
}

void RenderSystem::DrawAimLine(sf::RenderWindow& window, const AimLine& aimLine)
{
    if (aimLine.IsVisible())
        window.draw(aimLine.GetLine());
}

} // namespace Breakout
