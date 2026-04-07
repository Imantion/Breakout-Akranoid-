#include "LevelCompleteScene.hpp"
#include "core/Game.hpp"
#include "core/Constants.hpp"
#include "scenes/MenuScene.hpp"
#include "managers/ScoreManager.hpp"
#include "systems/AudioSystem.hpp"


#include <string>

namespace Breakout
{

LevelCompleteScene::LevelCompleteScene(int currentScore)
    : m_Title(Game::Get()->GetFont(), "LEVEL COMPLETE", g_TitleFontSize,
              {0.0f, g_WindowHeight * g_LayoutEndTitleY}, sf::Color(g_LevelCompleteColorR, g_LevelCompleteColorG, g_LevelCompleteColorB))
    , m_ScoreLabel(Game::Get()->GetFont(),
                   "Score: " + std::to_string(currentScore), g_MenuFontSize,
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

    m_Buttons.emplace_back(Game::Get()->GetFont(), "Next Level", g_MenuFontSize,
                           sf::Vector2f{0.0f, g_WindowHeight * g_LayoutEndButton1Y},
                           []() { Game::Get()->LoadNextLevel(); });

    m_Buttons.emplace_back(Game::Get()->GetFont(), "Main Menu", g_MenuFontSize,
                           sf::Vector2f{0.0f, g_WindowHeight * g_LayoutEndButton2Y},
                           []() { Game::Get()->SetScene(std::make_unique<MenuScene>()); });

    for (auto& button : m_Buttons)
        button.CenterHorizontally(g_WindowWidth);
}

void LevelCompleteScene::ProcessInput(sf::RenderWindow& window)
{
    while (const auto event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();

        for (auto& button : m_Buttons)
            button.HandleEvent(*event, window);
    }
}

void LevelCompleteScene::Update([[maybe_unused]] float dt)
{
    auto& window = Game::Get()->GetWindow();
    for (auto& button : m_Buttons)
        button.Update(window);
}

void LevelCompleteScene::Render(RenderSystem& renderer, sf::RenderWindow& window)
{
    renderer.DrawLabel(window, m_Title);
    renderer.DrawLabel(window, m_ScoreLabel);
    renderer.DrawLabel(window, m_BestScoreLabel);

    for (auto& button : m_Buttons)
        renderer.DrawButton(window, button);
}

} // namespace Breakout
