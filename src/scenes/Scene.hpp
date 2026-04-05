#pragma once

#include <SFML/Graphics.hpp>

namespace Breakout
{

class RenderSystem;

class Scene
{
public:
    virtual ~Scene() = default;

    virtual void OnEnter() {}
    virtual void OnExit() {}

    virtual void ProcessInput(sf::RenderWindow& window) = 0;
    virtual void Update(float dt) = 0;
    virtual void Render(RenderSystem& renderer, sf::RenderWindow& window) = 0;
};

} // namespace Breakout
