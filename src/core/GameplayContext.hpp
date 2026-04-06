#pragma once

namespace Breakout
{

class Paddle;
class GameplayScene;

struct GameplayContext
{
    Paddle&        paddle;
    GameplayScene& scene;
};

} // namespace Breakout
