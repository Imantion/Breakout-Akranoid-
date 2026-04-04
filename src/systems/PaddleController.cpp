#include "PaddleController.hpp"

namespace Breakout
{

void PaddleController::Update(Paddle& paddle) const
{
    float direction = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        direction -= 1.0f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        direction += 1.0f;
    }

    paddle.SetDirection(direction);
}

} // namespace Breakout
