#pragma once

#include "Scene.hpp"
#include "systems/RenderSystem.hpp"
#include "ui/Label.hpp"
#include "ui/Button.hpp"

#include <vector>

namespace Breakout
{

class MenuScene : public Scene
{
public:
    MenuScene();

    void ProcessInput(sf::RenderWindow& window) override;
    void Update(float dt) override;
    void Render(RenderSystem& renderer, sf::RenderWindow& window) override;

private:
    Label                m_Title;
    std::vector<Button>  m_Buttons;
};

} // namespace Breakout
