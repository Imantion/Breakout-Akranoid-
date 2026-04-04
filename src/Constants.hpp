#pragma once

#include <cstdint>

namespace Breakout
{

constexpr uint32_t g_WindowWidth  = 800;
constexpr uint32_t g_WindowHeight = 600;
constexpr char     g_WindowTitle[] = "Breakout";

constexpr float g_FixedTimeStep = 1.0f / 60.0f;

constexpr float g_PaddleWidth  = 100.0f;
constexpr float g_PaddleHeight = 16.0f;
constexpr float g_PaddleSpeed  = 500.0f;
constexpr float g_PaddleBottomMargin = 40.0f;

constexpr float g_BallRadius = 8.0f;
constexpr float g_BallSpeed  = 400.0f;

constexpr float g_BrickWidth  = 60.0f;
constexpr float g_BrickHeight = 20.0f;
constexpr float g_BrickPadding = 4.0f;
constexpr int   g_BrickColumns = 10;
constexpr int   g_BrickRows    = 5;
constexpr float g_BrickGridTopMargin  = 40.0f;
constexpr float g_BrickGridLeftMargin =
    (g_WindowWidth - (g_BrickColumns * (g_BrickWidth + g_BrickPadding) - g_BrickPadding)) / 2.0f;

constexpr float g_MaxBounceAngle = 60.0f * 3.14159265f / 180.0f;

} // namespace Breakout
