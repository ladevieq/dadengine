#ifndef __EVENT_MANAGER_HPP_
#define __EVENT_MANAGER_HPP_

#include <cstdint>
#include <functional>
#include <map>

namespace DadEngine
{
    using EventIdentifier = uint32_t;

    // enum EVENT_IDENTIFIERS : uint32_t
    // {
    //     CLOSE_WINDOW_EVENT,
    // };
    //
    // struct Event
    // {
    //     const EventIdentifier m_eventIdentifier = 0U;
    // };
    //
    // struct CloseWindowEvent : public Event
    // {
    //     const EventIdentifier m_eventIdentifier = EVENT_IDENTIFIERS::CLOSE_WINDOW_EVENT;
    // };
    //
    // class EventManager
    // {
    //     public:
    //     void EmitEvent(Event &_event)
    //     {
    //         const auto listerners m_eventsTable[_event.m_eventIdentifier];
    //
    //         for (auto &listener in listeners)
    //         {
    //             listener();
    //         }
    //     }
    //
    //
    //     void AddEventListener(EventIdentifier _eventIdentifier, auto _callbackFunction)
    //     {
    //         m_eventsTable.insert(std::make_pair(_eventIdentifier, _callbackFunction));
    //     }
    //
    //     void RemoveEventListener(EventIdentifier _eventIdentifier, auto _callbackFunction);
    //
    //
    //     static EventManager GetInstance()
    //     {
    //         static EventManager instance = EventManager{};
    //         return instance;
    //     }
    //
    //     private:
    //     EventManager() = default;
    //     EventManager(EventManager &) = default;
    //
    //     ~EventManager() = default;
    //
    //     std::<EventIdentifier, auto>m_eventsTable;
    // };
} // namespace DadEngine

#endif // !__EVENT_MANAGER_HPP_
