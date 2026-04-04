#pragma once

#include "entities/Paddle.hpp"
#include "entities/Ball.hpp"

namespace Breakout
{

class MovementSystem
{
public:
    void Update(Paddle& paddle, Ball& ball, float dt) const;
};

} // namespace Breakout
