#include "WinScene.hpp"
#include "core/Game.hpp"
#include "core/Constants.hpp"
#include "scenes/MenuScene.hpp"

#include <string>

namespace Breakout
{

WinScene::WinScene(int finalScore)
    : m_Title(Game::Get()->GetFont(), "YOU WIN!", g_TitleFontSize,
              {0.0f, g_WindowHeight * 0.12f}, sf::Color(100, 230, 100))
    , m_ScoreLabel(Game::Get()->GetFont(),
                   "Final Score: " + std::to_string(finalScore), g_MenuFontSize,
                   {0.0f, g_WindowHeight * 0.35f}, sf::Color::White)
    , m_TotalScoreLabel(Game::Get()->GetFont(),
                       "Total Score: " + std::to_string(Game::Get()->GetScoreManager().GetTotalScore()),
                       g_HudFontSize, {0.0f, g_WindowHeight * 0.43f}, sf::Color(180, 180, 180))
{
    m_Title.CenterHorizontally(g_WindowWidth);
    m_ScoreLabel.CenterHorizontally(g_WindowWidth);
    m_TotalScoreLabel.CenterHorizontally(g_WindowWidth);

    m_Buttons.emplace_back(Game::Get()->GetFont(), "Play Again", g_MenuFontSize,
                           sf::Vector2f{0.0f, g_WindowHeight * 0.55f},
                           []() { Game::Get()->StartCampaign(); });

    m_Buttons.emplace_back(Game::Get()->GetFont(), "Main Menu", g_MenuFontSize,
                           sf::Vector2f{0.0f, g_WindowHeight * 0.65f},
                           []() { Game::Get()->SetScene(std::make_unique<MenuScene>()); });

    for (auto& button : m_Buttons)
        button.CenterHorizontally(g_WindowWidth);
}

void WinScene::ProcessInput(sf::RenderWindow& window)
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

void WinScene::Update([[maybe_unused]] float dt)
{
    auto& window = Game::Get()->GetWindow();
    for (auto& button : m_Buttons)
        button.Update(window);
}

void WinScene::Render(RenderSystem& renderer, sf::RenderWindow& window)
{
    renderer.DrawLabel(window, m_Title);
    renderer.DrawLabel(window, m_ScoreLabel);
    renderer.DrawLabel(window, m_TotalScoreLabel);

    for (auto& button : m_Buttons)
        renderer.DrawButton(window, button);
}

} // namespace Breakout
