#pragma once

#include <cstdint>

namespace Breakout
{

// Window
constexpr uint32_t g_WindowWidth  = 800;
constexpr uint32_t g_WindowHeight = 600;
constexpr char     g_WindowTitle[] = "Breakout";

constexpr float g_FixedTimeStep = 1.0f / 60.0f;

// Paddle
constexpr float g_PaddleWidth  = 100.0f;
constexpr float g_PaddleHeight = 16.0f;
constexpr float g_PaddleSpeed  = 500.0f;
constexpr float g_PaddleBottomMargin = 40.0f;

// Ball
constexpr float g_BallRadius = 8.0f;
constexpr float g_BallSpeed  = 400.0f;
constexpr float g_BallSpeedDiagonalFactor = 0.7f;
constexpr float g_MinLaunchDirectionLength = 1.0f;

// Bricks
constexpr float g_BrickWidth  = 60.0f;
constexpr float g_BrickHeight = 20.0f;
constexpr float g_BrickPadding = 4.0f;
constexpr float g_BrickGridTopMargin = 40.0f;
constexpr int   g_MultiHPBrickHp = 2;
constexpr int   g_CrackTextureMinHp = 2;

// Physics
constexpr float g_MaxBounceAngle = 60.0f * 3.14159265f / 180.0f;

// File paths
constexpr char g_DataDirectory[]   = "data";
constexpr char g_FontFile[]        = "data/font.ttf";
constexpr char g_LevelsDirectory[] = "data/levels";
constexpr char g_CampaignFile[]    = "data/levels/campaign.txt";
constexpr char g_ScoresFile[]      = "data/scores.txt";

// Scoring
constexpr int g_StartingLives = 3;
constexpr int g_ScorePerBrick = 10;
constexpr int g_DestroyedInRow = 3;
constexpr int g_DestroyedInRowBonus = 20;
constexpr int g_MaxScoreEntries = 10;
constexpr char g_DefaultPlayerName[] = "Player";

// Abilities
constexpr float g_AbilitySize          = 20.0f;
constexpr float g_AbilityFallSpeed     = 150.0f;
constexpr float g_AbilitySpawnChance   = 0.2f;
constexpr float g_WidePaddleDuration   = 8.0f;
constexpr float g_WidePaddleMultiplier = 1.5f;
constexpr float g_ShortPaddleMultiplier = 0.5f;

// Aim line
constexpr float g_AimLineLength = 80.0f;

// Audio
constexpr char  g_AudioDirectory[]    = "data/audio";
constexpr float g_DefaultMusicVolume = 50.0f;
constexpr float g_DefaultSoundVolume = 100.0f;

constexpr char g_MenuMusicFile[]     = "data/audio/menu_music.ogg";
constexpr char g_GameplayMusicFile[] = "data/audio/gameplay_music.ogg";

constexpr char g_SfxBrickHit[]       = "ball_hit";
constexpr char g_SfxWallHit[]        = "ball_hit";
constexpr char g_SfxPaddleHit[]      = "ball_hit";
constexpr char g_SfxBrickDestroy[]   = "ball_hit";
constexpr char g_SfxAbilityPickup[]  = "ability_pickup";
constexpr char g_SfxBallLost[]       = "ball_lose";

// Texture keys
constexpr char g_TexPaddle[]           = "paddle";
constexpr char g_TexBall[]             = "ball";
constexpr char g_TexBrick[]            = "brick";
constexpr char g_TexBrickCracked[]     = "brick_cracked";
constexpr char g_TexBrickInvulnerable[] = "brick_invulnerable";
constexpr char g_TexMultiBall[]        = "multi_ball";
constexpr char g_TexExtraLife[]        = "hp";
constexpr char g_TexWidePaddle[]       = "wide_paddle";
constexpr char g_TexShortPaddle[]       = "short_paddle";

// UI colors
constexpr uint8_t g_BgColorR = 30, g_BgColorG = 30, g_BgColorB = 46;

constexpr uint8_t g_TitleColorR = 255, g_TitleColorG = 200, g_TitleColorB = 60;
constexpr uint8_t g_WinColorR = 100, g_WinColorG = 230, g_WinColorB = 100;
constexpr uint8_t g_GameOverColorR = 230, g_GameOverColorG = 70, g_GameOverColorB = 70;
constexpr uint8_t g_LevelCompleteColorR = 100, g_LevelCompleteColorG = 200, g_LevelCompleteColorB = 255;
constexpr uint8_t g_SubtitleGray = 180;

constexpr uint8_t g_BtnNormalGray = 200;
constexpr uint8_t g_AimLineAlphaStart = 120;
constexpr uint8_t g_AimLineAlphaEnd   = 40;

// UI layout (fractions of window height)
constexpr float g_LayoutTitleY         = 0.2f;
constexpr float g_LayoutSubtitleY      = 0.38f;
constexpr float g_LayoutEndTitleY      = 0.12f;
constexpr float g_LayoutEndScoreY      = 0.35f;
constexpr float g_LayoutEndBestY       = 0.43f;
constexpr float g_LayoutButton1Y       = 0.5f;
constexpr float g_LayoutButton2Y       = 0.6f;
constexpr float g_LayoutEndButton1Y    = 0.55f;
constexpr float g_LayoutEndButton2Y    = 0.65f;

constexpr float g_LivesLabelRightOffset = 120.0f;

// HUD
constexpr float g_HudMargin   = 10.0f;
constexpr unsigned int g_HudFontSize  = 20;
constexpr unsigned int g_TitleFontSize = 64;
constexpr unsigned int g_MenuFontSize  = 32;

} // namespace Breakout
