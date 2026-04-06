#include "MenuScene.hpp"
#include "core/Game.hpp"
#include "core/Constants.hpp"

#include <string>

namespace Breakout
{

MenuScene::MenuScene()
    : m_Title(Game::Get()->GetFont(), "BREAKOUT", g_TitleFontSize,
              {0.0f, g_WindowHeight * 0.2f}, sf::Color(255, 200, 60))
    , m_TotalScoreLabel(Game::Get()->GetFont(),
                       "Total Score: " + std::to_string(Game::Get()->GetScoreManager().GetTotalScore()),
                       g_HudFontSize, {0.0f, g_WindowHeight * 0.38f}, sf::Color(180, 180, 180))
{
    m_Title.CenterHorizontally(g_WindowWidth);
    m_TotalScoreLabel.CenterHorizontally(g_WindowWidth);

    m_Buttons.emplace_back(Game::Get()->GetFont(), "Play", g_MenuFontSize,
                           sf::Vector2f{0.0f, g_WindowHeight * 0.5f},
                           []() { Game::Get()->StartCampaign(); });

    m_Buttons.emplace_back(Game::Get()->GetFont(), "Quit", g_MenuFontSize,
                           sf::Vector2f{0.0f, g_WindowHeight * 0.6f},
                           []() { Game::Get()->GetWindow().close(); });

    for (auto& button : m_Buttons)
        button.CenterHorizontally(g_WindowWidth);
}

void MenuScene::ProcessInput(sf::RenderWindow& window)
{
    while (const auto event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                window.close();
        }

        for (auto& button : m_Buttons)
            button.HandleEvent(*event, window);
    }
}

void MenuScene::Update([[maybe_unused]] float dt)
{
    auto& window = Game::Get()->GetWindow();
    for (auto& button : m_Buttons)
        button.Update(window);
}

void MenuScene::Render(RenderSystem& renderer, sf::RenderWindow& window)
{
    renderer.DrawLabel(window, m_Title);
    renderer.DrawLabel(window, m_TotalScoreLabel);

    for (auto& button : m_Buttons)
        renderer.DrawButton(window, button);
}

} // namespace Breakout
