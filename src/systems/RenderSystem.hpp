#pragma once

#include <SFML/Graphics.hpp>
#include <span>
#include <vector>

#include "entities/Actor.hpp"
#include "entities/Brick.hpp"
#include "ui/Label.hpp"
#include "ui/Button.hpp"

namespace Breakout
{

class RenderSystem
{
public:
    void BeginFrame(sf::RenderWindow& window);
    void EndFrame(sf::RenderWindow& window);

    void DrawActor(sf::RenderWindow& window, const Actor& actor);
    void DrawBricks(sf::RenderWindow& window, const std::vector<Brick>& bricks);
    void DrawLabel(sf::RenderWindow& window, const Label& label);
    void DrawButton(sf::RenderWindow& window, const Button& button);
};

} // namespace Breakout
