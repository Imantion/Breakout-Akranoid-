#include "GameOverScene.hpp"
#include "Game.hpp"
#include "Constants.hpp"
#include "scenes/GameplayScene.hpp"

#include <string>

namespace Breakout
{

GameOverScene::GameOverScene(int finalScore)
    : m_Title(Game::Get()->GetFont(), "GAME OVER", g_TitleFontSize,
              {0.0f, g_WindowHeight * 0.15f}, sf::Color(230, 70, 70))
    , m_ScoreLabel(Game::Get()->GetFont(),
                   "Final Score: " + std::to_string(finalScore), g_MenuFontSize,
                   {0.0f, g_WindowHeight * 0.38f}, sf::Color::White)
{
    m_Title.CenterHorizontally(g_WindowWidth);
    m_ScoreLabel.CenterHorizontally(g_WindowWidth);

    m_Buttons.emplace_back(Game::Get()->GetFont(), "Play Again", g_MenuFontSize,
                           sf::Vector2f{0.0f, g_WindowHeight * 0.55f},
                           []() { Game::Get()->SetScene(std::make_unique<GameplayScene>()); });

    m_Buttons.emplace_back(Game::Get()->GetFont(), "Exit", g_MenuFontSize,
                           sf::Vector2f{0.0f, g_WindowHeight * 0.65f},
                           []() { Game::Get()->GetWindow().close(); });

    for (auto& button : m_Buttons)
        button.CenterHorizontally(g_WindowWidth);
}

void GameOverScene::ProcessInput(sf::RenderWindow& window)
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

void GameOverScene::Update([[maybe_unused]] float dt)
{
    auto& window = Game::Get()->GetWindow();
    for (auto& button : m_Buttons)
        button.Update(window);
}

void GameOverScene::Render(RenderSystem& renderer, sf::RenderWindow& window)
{
    renderer.DrawLabel(window, m_Title);
    renderer.DrawLabel(window, m_ScoreLabel);

    for (auto& button : m_Buttons)
        renderer.DrawButton(window, button);
}

} // namespace Breakout
