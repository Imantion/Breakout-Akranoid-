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
constexpr float g_BrickGridTopMargin = 40.0f;

constexpr float g_MaxBounceAngle = 60.0f * 3.14159265f / 180.0f;

constexpr char g_DataDirectory[]  = "data";
constexpr char g_FontFile[]       = "data/font.ttf";
constexpr char g_LevelsDirectory[] = "data/levels";
constexpr char g_CampaignFile[]   = "data/levels/campaign.txt";

constexpr int g_StartingLives = 3;
constexpr int g_ScorePerBrick = 10;
constexpr int g_DestroyedInRow = 3;
constexpr int g_DestroyedInRowBonus = 20;

constexpr float g_AbilitySize          = 20.0f;
constexpr float g_AbilityFallSpeed     = 150.0f;
constexpr float g_AbilitySpawnChance   = 0.2f;
constexpr float g_WidePaddleDuration   = 8.0f;
constexpr float g_WidePaddleMultiplier = 1.5f;

constexpr int g_MultiHPBrickHp = 2;

constexpr float g_AimLineLength = 80.0f;

constexpr float g_HudMargin   = 10.0f;
constexpr unsigned int g_HudFontSize  = 20;
constexpr unsigned int g_TitleFontSize = 64;
constexpr unsigned int g_MenuFontSize  = 32;

} // namespace Breakout
