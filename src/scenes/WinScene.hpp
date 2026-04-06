#pragma once

#include "Scene.hpp"
#include "systems/RenderSystem.hpp"
#include "ui/Label.hpp"
#include "ui/Button.hpp"

#include <vector>

namespace Breakout
{

class WinScene : public Scene
{
public:
    explicit WinScene(int finalScore);

    void ProcessInput(sf::RenderWindow& window) override;
    void Update(float dt) override;
    void Render(RenderSystem& renderer, sf::RenderWindow& window) override;

private:
    Label                m_Title;
    Label                m_ScoreLabel;
    Label                m_TotalScoreLabel;
    std::vector<Button>  m_Buttons;
};

} // namespace Breakout
