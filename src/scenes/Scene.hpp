#pragma once

#include <SFML/Graphics.hpp>

namespace Breakout
{

class Scene
{
public:
    virtual ~Scene() = default;

    virtual void OnEnter() {}
    virtual void OnExit() {}

    virtual void ProcessInput(sf::RenderWindow& window) = 0;
    virtual void Update(float dt) = 0;
    virtual void Render(sf::RenderWindow& window) = 0;
};

} // namespace Breakout
