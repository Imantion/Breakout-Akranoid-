#pragma once

#include <span>

#include "entities/Paddle.hpp"
#include "entities/Ball.hpp"

namespace Breakout
{

class MovementSystem
{
public:
    void Update(Paddle& paddle, std::span<Ball> balls, float dt);
};

} // namespace Breakout
