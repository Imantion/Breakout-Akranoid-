#include "AbilityFactory.hpp"
#include "abilities/MultiBallAbility.hpp"
#include "abilities/ExtraLifeAbility.hpp"
#include "abilities/WidePaddleAbility.hpp"
#include "Constants.hpp"
#include "Game.hpp"

#include <random>

namespace Breakout
{

std::unique_ptr<Ability> AbilityFactory::CreateMultiBall(sf::Vector2f position)
{
    return std::make_unique<MultiBallAbility>(
        Game::Get()->GetTextureManager().GetTexture("multi_ball"),
        position, g_AbilitySize);
}

std::unique_ptr<Ability> AbilityFactory::CreateExtraLife(sf::Vector2f position)
{
    return std::make_unique<ExtraLifeAbility>(
        Game::Get()->GetTextureManager().GetTexture("hp"),
        position, g_AbilitySize);
}

std::unique_ptr<Ability> AbilityFactory::CreateWidePaddle(sf::Vector2f position)
{
    return std::make_unique<WidePaddleAbility>(
        Game::Get()->GetTextureManager().GetTexture("wide_paddle"),
        position, g_AbilitySize);
}

std::unique_ptr<Ability> AbilityFactory::CreateRandom(sf::Vector2f position)
{
    static std::mt19937 rng(std::random_device{}());

    using CreateFn = std::unique_ptr<Ability>(*)(sf::Vector2f);
    static constexpr CreateFn factories[] = {
        &CreateMultiBall,
        &CreateExtraLife,
        &CreateWidePaddle
    };

    std::uniform_int_distribution<int> dist(0, std::size(factories) - 1);
    return factories[dist(rng)](position);
}

} // namespace Breakout
