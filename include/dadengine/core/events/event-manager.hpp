#ifndef __EVENT_MANAGER_HPP_
#define __EVENT_MANAGER_HPP_

#include <cstdint>
#include <functional>
#include <map>
#include <vector>

// #include "../types/string.hpp"
// #include "../types/collection/tdictionary.hpp"

namespace DadEngine
{
    class Event;

    using Channel = std::map<uint32_t, auto>;

    class EventManager
    {
        public:
        // EventManager() = default;

        // Send an event
        // void emitEvent(String &_InEventName, Event &_InEvent);

        // Subscribe to an event
        // void onEvent(String &_InEventName, CallbackFunction &_InCallbackFunc);
        
        // Channel level
        RegisterChannel(uint32_t _channelIdentifier);

        UnregisterChannel(uint32_t _channelIdentifier);


        // Event level
        AddListener(uint32_t _eventIdentifier, auto _callbackFunction);

        RemoveListener(uint32_t _eventIdentifier, auto _callbackFunction);


        static EventManager getInstance()
        {
            static EventManager instance = EventManager{};
            return instance;
        }

        // using CallbackFunction = std::function<void(Event &)>;

        // TDictionnary<String, CallbackFunction> m_eventTable;

        std::vector<uint32_t, Channel> m_channels;
    };
} // namespace DadEngine

#endif // !__EVENT_MANAGER_HPP_
