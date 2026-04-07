#pragma once

#include "utils/uuid.hpp"
#include <cstdint>
#include <random>

namespace Breakout
{

// TODO: Embeded this into UUID as bit set
enum class EntityType : uint8_t
{
    None          = 0,
    Player        = 1,
    Ball          = 2,
    Destructible  = 3,
    Invulnerable  = 4,
    Ability       = 5,
};

inline uuids::uuid GenerateUUID()
{
    static std::mt19937 rng(std::random_device{}());
    static uuids::uuid_random_generator gen(rng);
    return gen();
}

} // namespace Breakout
