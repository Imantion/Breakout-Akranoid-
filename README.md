# Breakout

A classic Breakout (Arkanoid) game built from scratch with **C++23** and **SFML 3.0**.

## About

This project is a full-featured Breakout clone with clean architecture, designed as an exercise in game programming patterns and C++ best practices. The game features multiple levels, power-up abilities, score tracking, and a complete scene management system.

### Features

- **Campaign mode** with file-based level definitions
- **Multiple brick types** -- standard (1 HP), multi-HP with crack textures, and invulnerable
- **Power-up abilities** -- MultiBall, ExtraLife, WidePaddle (with timed effects)
- **Ball attach & aim** -- ball sticks to paddle on reset, aim with mouse, launch on click
- **Score persistence** -- per-level leaderboard saved to disk
- **Audio system** -- background music per scene and sound effects on game events
- **Scene management** -- Menu, Gameplay, Level Complete, Game Over, Win screens

### Architecture

The project follows an OOP + System pattern:

- **Entities** (Actor base class with UUID) -- Paddle, Ball, Brick hierarchy, Ability hierarchy
- **Systems** -- MovementSystem, CollisionSystem, RenderSystem, AudioSystem, EffectManager, PaddleController
- **Scenes** -- each scene owns its lifecycle, Game orchestrates transitions
- **EventBus** -- type-erased pub/sub with deferred dispatch for safe mutation during iteration
- **Factory pattern** -- BrickFactory and AbilityFactory for entity creation
- **Flyweight** -- bricks share textures, tinted per row via sprite color

```
src/
  main.cpp
  core/           -- Game, Constants, GameSession, GameplayContext, EntityUUID
  events/         -- EventBus, Events
  managers/       -- TextureManager, ScoreManager
  levels/         -- LevelLoader, LevelData
  entities/       -- Actor, Paddle, Ball, Brick (Destructible/Invulnerable), Ability
  entities/abilities/  -- MultiBall, ExtraLife, WidePaddle
  scenes/         -- Scene, MenuScene, GameplayScene, LevelCompleteScene, GameOverScene, WinScene
  systems/        -- CollisionSystem, MovementSystem, RenderSystem, AudioSystem, EffectManager, PaddleController
  ui/             -- Label, Button, AimLine
  utils/          -- robin_hood.hpp, uuid.hpp (third-party)
```

### Technologies

- **C++23** (standard features: `std::optional`, `std::span`, designated initializers, `std::filesystem`)
- **SFML 3.0.2** (Graphics, Audio, Window, System, Network)
- **CMake 3.20+** with FetchContent for automatic SFML download
- **robin_hood** hash map for entity UUID registry
- **stduuid** for 128-bit RFC 4122 UUIDs

## Prerequisites

### Linux (Debian/Ubuntu)

```bash
sudo apt install build-essential cmake git \
    libx11-dev libxrandr-dev libxcursor-dev libxi-dev \
    libudev-dev libfreetype-dev libflac-dev libvorbis-dev \
    libopenal-dev libgl-dev
```

### Linux (Fedora/RHEL)

```bash
sudo dnf install gcc-c++ cmake git \
    libXrandr-devel libXcursor-devel libXi-devel \
    libudev-devel freetype-devel flac-devel libvorbis-devel \
    openal-soft-devel mesa-libGL-devel
```

### Windows

No system dependencies needed. CMake + a C++23 compiler (MSVC 2022 or MinGW-w64) and Git are sufficient. SFML is fetched and built automatically.

## Building

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)
```

The executable is output to `build/bin/Breakout`. The `data/` folder is automatically copied to `build/bin/data/` after each build.

### Windows (Visual Studio)

```bash
cmake -B build
```

Open `build/Breakout.sln`. The startup project is already set to `Breakout`.

## Running

```bash
cd build/bin
./Breakout
```

### Controls

| Action | Key/Mouse |
|--------|-----------|
| Move paddle | Arrow keys or A/D |
| Aim ball | Move mouse |
| Launch ball | Left click |
| Pause / Menu | Escape |

## Assets

Place the following files in `data/`:

### Textures (required)

| File | Description |
|------|-------------|
| `paddle.png` | Paddle sprite |
| `ball.png` | Ball sprite |
| `brick.png` | Standard brick |
| `brick_cracked.png` | Damaged brick (multi-HP) |
| `brick_invulnerable.png` | Invulnerable brick |
| `multi_ball.png` | MultiBall ability icon |
| `hp.png` | ExtraLife ability icon |
| `wide_paddle.png` | WidePaddle ability icon |
| `font.ttf` | Any TTF font for UI text |

### Audio (optional, in `data/audio/`)

| File | Description |
|------|-------------|
| `menu_music.ogg` | Menu background music |
| `gameplay_music.ogg` | Gameplay background music |
| `brick_hit.wav` | Ball hits a brick |
| `brick_destroy.wav` | Brick destroyed |
| `wall_hit.wav` | Ball hits a wall |
| `paddle_hit.wav` | Ball hits the paddle |
| `ability_pickup.wav` | Player picks up an ability |
| `ball_lost.wav` | Ball falls off screen |

## Creating Levels

Levels are defined as text files in `data/levels/`.

### Level format

Space-separated values, one row per line:

| Symbol | Meaning |
|--------|---------|
| `1`, `2`, `3`, ... | Destructible brick with that many HP |
| `i` | Invulnerable brick |
| `x` | Empty space (no brick) |

Example (`data/levels/level1.txt`):

```
1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1
2 2 2 2 2 2 2 2 2 2
x x i i i i i i x x
x x x x x x x x x x
```

Grid dimensions are inferred from the file -- columns from the first row, rows from the line count. The brick grid is automatically centered horizontally.

### Campaign file

`data/levels/campaign.txt` lists the levels in play order, one filename per line:

```
level1.txt
level2.txt
level3.txt
```

To add a new level, create the `.txt` file and add its name to `campaign.txt`.

## Project Structure

| Module | Responsibility |
|--------|---------------|
| `Game` | Singleton, owns window/font/managers/audio, orchestrates scene transitions and campaign flow |
| `Scene` | Abstract base with `OnEnter`/`OnExit`/`ProcessInput`/`Update`/`Render` lifecycle |
| `GameplayScene` | Owns all gameplay entities via UUID registry, delegates to systems |
| `CollisionSystem` | Detects collisions, publishes events (no game logic) |
| `EventBus` | Deferred pub/sub -- events queue during systems, flush after all systems complete |
| `LevelLoader` | Parses campaign and level files, creates bricks via BrickFactory |
| `ScoreManager` | Per-level leaderboard with file persistence |
| `AudioSystem` | Loads sound effects, manages playback pool, streams background music |
| `EffectManager` | Timed effects with apply/expire callbacks (e.g. WidePaddle duration) |
| `TextureManager` | Loads all images from `data/` at startup, keyed by filename stem |

## License

This project uses the following third-party libraries:

- [SFML 3.0](https://www.sfml-dev.org/) -- zlib/png license
- [robin-hood-hashing](https://github.com/martinus/robin-hood-hashing) -- MIT license
- [stduuid](https://github.com/mariusbancila/stduuid) -- MIT license
