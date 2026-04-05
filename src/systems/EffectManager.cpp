#include "EffectManager.hpp"

#include <algorithm>

namespace Breakout
{

void EffectManager::PushEffect(EffectType type, float duration,
                               std::function<void()> onApply,
                               std::function<void()> onExpire)
{
    auto it = std::find_if(m_ActiveEffects.begin(), m_ActiveEffects.end(),
        [type](const ActiveEffect& e) { return e.type == type; });

    if (it != m_ActiveEffects.end())
    {
        it->remainingTime = duration;
        return;
    }

    onApply();
    m_ActiveEffects.push_back({type, duration, std::move(onExpire)});
}

void EffectManager::Update(float dt)
{
    for (auto it = m_ActiveEffects.begin(); it != m_ActiveEffects.end(); )
    {
        it->remainingTime -= dt;

        if (it->remainingTime <= 0.0f)
        {
            it->onExpire();
            it = m_ActiveEffects.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

bool EffectManager::HasEffect(EffectType type) const
{
    return std::any_of(m_ActiveEffects.begin(), m_ActiveEffects.end(),
        [type](const ActiveEffect& e) { return e.type == type; });
}

} // namespace Breakout
