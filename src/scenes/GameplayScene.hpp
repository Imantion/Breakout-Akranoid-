#pragma once

#include "Scene.hpp"
#include "ui/Label.hpp"
#include "ui/AimLine.hpp"
#include "entities/Paddle.hpp"
#include "entities/Ball.hpp"
#include "entities/Brick.hpp"
#include "entities/Ability.hpp"
#include "systems/PaddleController.hpp"
#include "systems/MovementSystem.hpp"
#include "systems/CollisionSystem.hpp"
#include "systems/EffectManager.hpp"
#include "utils/robin_hood.hpp"
#include "utils/uuid.hpp"

#include <functional>
#include <memory>
#include <random>
#include <vector>

namespace Breakout
{

class GameplayScene : public Scene
{
public:
    explicit GameplayScene(std::vector<std::unique_ptr<Brick>> bricks);

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

    Actor* FindActor(const uuids::uuid& uuid);

private:
    template<typename T>
    T* _registerActor(std::unique_ptr<T> actor);

    void _subscribeEvents();
    void _resetBall(Ball& ball);
    void _updateHud();
    void _handleAim();
    void _spawnAbility(sf::Vector2f position);
    void _cleanupDead();
    void _launchAttachedBall(const sf::RenderWindow& window, sf::Vector2i mousePixel);
    Ball* _findAttachedBall();

    robin_hood::unordered_map<uuids::uuid, std::unique_ptr<Actor>> m_Registry;

    Paddle*                m_Paddle = nullptr;
    std::vector<Ball*>     m_Balls;
    std::vector<Brick*>    m_Bricks;
    std::vector<Ability*>  m_Abilities;

    PaddleController   m_PaddleController;
    MovementSystem     m_MovementSystem;
    CollisionSystem    m_CollisionSystem;
    EffectManager      m_EffectManager;

    int      m_Score;
    int      m_Lives;
    int      m_BricksAlive;
    Label    m_ScoreLabel;
    Label    m_LivesLabel;

    AimLine      m_AimLine;
    std::mt19937 m_Rng;
};

} // namespace Breakout
