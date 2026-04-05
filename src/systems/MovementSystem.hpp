#pragma once

#include <memory>
#include <span>
#include <vector>

#include "entities/Paddle.hpp"
#include "entities/Ball.hpp"
#include "entities/Ability.hpp"

namespace Breakout
{

class MovementSystem
{
public:
    void Update(Paddle& paddle, std::span<Ball> balls,
                std::span<std::unique_ptr<Ability>> abilities, float dt);
};

} // namespace Breakout
