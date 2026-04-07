#pragma once

#include "Ability.hpp"

#include <memory>

#include <SFML/System/Vector2.hpp>

namespace Breakout
{

class AbilityFactory
{
public:
    static std::unique_ptr<Ability> CreateMultiBall(sf::Vector2f position);
    static std::unique_ptr<Ability> CreateExtraLife(sf::Vector2f position);
    static std::unique_ptr<Ability> CreateWidePaddle(sf::Vector2f position);
    static std::unique_ptr<Ability> CreateShortPaddle(sf::Vector2f position);

    static std::unique_ptr<Ability> CreateRandom(sf::Vector2f position);
};

} // namespace Breakout
