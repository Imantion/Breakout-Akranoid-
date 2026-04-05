#pragma once

#include <functional>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace Breakout
{

class EventBus
{
public:
    template<typename TEvent>
    void Subscribe(std::function<void(const TEvent&)> callback)
    {
        auto wrapper = [cb = std::move(callback)](const void* eventPtr)
        {
            cb(*static_cast<const TEvent*>(eventPtr));
        };
        m_Subscribers[std::type_index(typeid(TEvent))].push_back(std::move(wrapper));
    }

    template<typename TEvent>
    void Publish(const TEvent& event)
    {
        auto typeIdx = std::type_index(typeid(TEvent));
        if (m_Subscribers.find(typeIdx) == m_Subscribers.end())
            return;

        TEvent copy = event;
        m_PendingEvents.push_back([this, copy, typeIdx]()
        {
            auto it = m_Subscribers.find(typeIdx);
            if (it == m_Subscribers.end())
                return;

            for (auto& cb : it->second)
                cb(&copy);
        });
    }

    void FlushEvents()
    {
        while (!m_PendingEvents.empty())
        {
            auto batch = std::move(m_PendingEvents);
            for (auto& fn : batch)
                fn();
        }
    }

    void Clear()
    {
        m_Subscribers.clear();
        m_PendingEvents.clear();
    }

private:
    std::unordered_map<std::type_index,
                       std::vector<std::function<void(const void*)>>> m_Subscribers;
    std::vector<std::function<void()>> m_PendingEvents;
};

} // namespace Breakout
