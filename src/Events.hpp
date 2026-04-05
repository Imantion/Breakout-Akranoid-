#pragma once

namespace Breakout
{

class Ball;
class Paddle;
class Brick;
class Ability;

struct BallHitWallEvent
{
    Ball& ball;
};

struct BallHitPaddleEvent
{
    Ball& ball;
    const Paddle& paddle;
};

struct BallHitBrickEvent
{
    Ball& ball;
    Brick& brick;
};

struct BallLostEvent
{
    Ball& ball;
};

struct AbilityPickedUpEvent
{
    Ability& ability;
};

struct AbilityFallOutOfBoundsEvent
{
    Ability& ability;
};

} // namespace Breakout
