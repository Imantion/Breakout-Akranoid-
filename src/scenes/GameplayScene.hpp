#pragma once

#include "Scene.hpp"
#include "ui/Label.hpp"
#include "entities/Paddle.hpp"
#include "entities/Ball.hpp"
#include "entities/Brick.hpp"
#include "entities/Ability.hpp"
#include "systems/PaddleController.hpp"
#include "systems/MovementSystem.hpp"
#include "systems/CollisionSystem.hpp"
#include "systems/EffectManager.hpp"

#include <functional>
#include <memory>
#include <random>
#include <vector>

namespace Breakout
{

class GameplayScene : public Scene
{
public:
    GameplayScene();

    void OnEnter() override;
    void OnExit() override;

    void ProcessInput(sf::RenderWindow& window) override;
    void Update(float dt) override;
    void Render(RenderSystem& renderer, sf::RenderWindow& window) override;

    void AddBall(sf::Vector2f position, sf::Vector2f velocity);
    void AddLife();
    void AddEffect(EffectType type, float duration,
                   std::function<void()> onApply,
                   std::function<void()> onExpire);

private:
    void _initBricks();
    void _subscribeEvents();
    void _resetBall(Ball& ball);
    void _updateHud();
    void _spawnAbility(sf::Vector2f position);
    void _cleanupDeadAbilities();

    std::unique_ptr<Paddle>                   m_Paddle;
    std::vector<Ball>                         m_Balls;
    std::vector<Brick>                        m_Bricks;
    std::vector<std::unique_ptr<Ability>>     m_Abilities;

    PaddleController   m_PaddleController;
    MovementSystem     m_MovementSystem;
    CollisionSystem    m_CollisionSystem;
    EffectManager      m_EffectManager;

    int      m_Score;
    int      m_Lives;
    uint32_t m_DestroyedInRow;
    Label    m_ScoreLabel;
    Label    m_LivesLabel;

    std::mt19937 m_Rng;
};

} // namespace Breakout
