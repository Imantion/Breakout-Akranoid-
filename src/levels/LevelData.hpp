#pragma once

#include <vector>

namespace Breakout
{

struct BrickCell
{
    bool isEmpty;
    bool isInvulnerable;
    int  hp;
};

struct LevelData
{
    int rows;
    int columns;
    std::vector<std::vector<BrickCell>> grid;
};

} // namespace Breakout
