#pragma once

namespace Breakout
{

class Ball;
class Paddle;
class Brick;

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

} // namespace Breakout
