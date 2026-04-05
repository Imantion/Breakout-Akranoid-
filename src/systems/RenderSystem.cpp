#include "RenderSystem.hpp"

namespace Breakout
{

void RenderSystem::Render(sf::RenderWindow& window,
                          const Paddle& paddle,
                          std::span<Ball> balls,
                          const std::vector<Brick>& bricks) const
{
    for (const auto& brick : bricks)
    {
        if (brick.IsAlive())
            brick.Draw(window);
    }

    paddle.Draw(window);

    for (const auto& ball : balls)
        ball.Draw(window);
}

} // namespace Breakout
