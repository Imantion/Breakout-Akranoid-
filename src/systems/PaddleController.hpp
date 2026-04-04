#pragma once

#include <SFML/Window/Keyboard.hpp>
#include "entities/Paddle.hpp"

namespace Breakout
{

class PaddleController
{
public:
    void Update(Paddle& paddle) const;
};

} // namespace Breakout
