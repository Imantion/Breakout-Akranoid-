#pragma once

#include <span>

#include "entities/Paddle.hpp"
#include "entities/Ball.hpp"
#include "entities/Ability.hpp"

namespace Breakout
{

class MovementSystem
{
public:
    void Update(Paddle& paddle, std::span<Ball*> balls,
                std::span<Ability*> abilities, float dt);
};

} // namespace Breakout
