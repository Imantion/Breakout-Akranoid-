#pragma once

#include "utils/uuid.hpp"

namespace Breakout
{

struct BallHitWallEvent
{
    uuids::uuid ballUUID;
};

struct BallHitPaddleEvent
{
    uuids::uuid ballUUID;
};

struct BallHitBrickEvent
{
    uuids::uuid ballUUID;
    uuids::uuid brickUUID;
};

struct BrickDeathEvent
{
    uuids::uuid brickUUID;
    uuids::uuid killerUUID;
};

struct BallLostEvent
{
    uuids::uuid ballUUID;
};

struct AbilityPickedUpEvent
{
    uuids::uuid abilityUUID;
};

struct AbilityFallOutOfBoundsEvent
{
    uuids::uuid abilityUUID;
};

} // namespace Breakout
