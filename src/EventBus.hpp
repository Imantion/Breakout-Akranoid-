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
        auto it = m_Subscribers.find(std::type_index(typeid(TEvent)));
        if (it == m_Subscribers.end())
            return;

        for (auto& callback : it->second)
            callback(&event);
    }

private:
    std::unordered_map<std::type_index,
                       std::vector<std::function<void(const void*)>>> m_Subscribers;
};

} // namespace Breakout
