#include "GameOverScene.hpp"
#include "core/Game.hpp"
#include "core/Constants.hpp"
#include "scenes/MenuScene.hpp"

#include <string>

namespace Breakout
{

GameOverScene::GameOverScene(int finalScore)
    : m_Title(Game::Get()->GetFont(), "GAME OVER", g_TitleFontSize,
              {0.0f, g_WindowHeight * g_LayoutEndTitleY}, sf::Color(g_GameOverColorR, g_GameOverColorG, g_GameOverColorB))
    , m_ScoreLabel(Game::Get()->GetFont(),
                   "Score: " + std::to_string(finalScore), g_MenuFontSize,
                   {0.0f, g_WindowHeight * g_LayoutEndScoreY}, sf::Color::White)
    , m_BestScoreLabel(Game::Get()->GetFont(),
                       "Level Best: " + std::to_string(
                           Game::Get()->GetScoreManager().GetBestScore(
                               Game::Get()->GetSession().currentLevelIndex)),
                       g_HudFontSize, {0.0f, g_WindowHeight * g_LayoutEndBestY}, sf::Color(180, 180, 180))
{
    m_Title.CenterHorizontally(g_WindowWidth);
    m_ScoreLabel.CenterHorizontally(g_WindowWidth);
    m_BestScoreLabel.CenterHorizontally(g_WindowWidth);

    m_Buttons.emplace_back(Game::Get()->GetFont(), "Play Again", g_MenuFontSize,
                           sf::Vector2f{0.0f, g_WindowHeight * g_LayoutEndButton1Y},
                           []() { Game::Get()->StartCampaign(); });

    m_Buttons.emplace_back(Game::Get()->GetFont(), "Main Menu", g_MenuFontSize,
                           sf::Vector2f{0.0f, g_WindowHeight * g_LayoutEndButton2Y},
                           []() { Game::Get()->SetScene(std::make_unique<MenuScene>()); });

    for (auto& button : m_Buttons)
        button.CenterHorizontally(g_WindowWidth);
}

void GameOverScene::OnEnter()
{
    Game::Get()->GetAudioSystem().StopMusic();
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
    renderer.DrawLabel(window, m_BestScoreLabel);

    for (auto& button : m_Buttons)
        renderer.DrawButton(window, button);
}

} // namespace Breakout
