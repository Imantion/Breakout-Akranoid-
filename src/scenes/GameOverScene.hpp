#pragma once

#include "Scene.hpp"
#include "ui/Label.hpp"
#include "ui/Button.hpp"

#include <vector>

namespace Breakout
{

class GameOverScene : public Scene
{
public:
    explicit GameOverScene(int finalScore);

    void ProcessInput(sf::RenderWindow& window) override;
    void Update(float dt) override;
    void Render(sf::RenderWindow& window) override;

private:
    Label                m_Title;
    Label                m_ScoreLabel;
    std::vector<Button>  m_Buttons;
};

} // namespace Breakout
