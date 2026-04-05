#pragma once

#include <cstdint>
#include <functional>
#include <vector>

namespace Breakout
{

enum class EffectType : uint8_t
{
    WidePaddle
};

struct ActiveEffect
{
    EffectType                type;
    float                     remainingTime;
    std::function<void()>     onExpire;
};

class EffectManager
{
public:
    void PushEffect(EffectType type, float duration,
                    std::function<void()> onApply,
                    std::function<void()> onExpire);

    void Update(float dt);

    bool HasEffect(EffectType type) const;

private:
    std::vector<ActiveEffect> m_ActiveEffects;
};

} // namespace Breakout
