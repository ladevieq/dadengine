#ifndef __EVENT_HPP_
#define __EVENT_HPP_

#include <cstdint>

namespace DadEngine
{
    enum class EventsTypes : uint8_t
    {
        WINDOW_CLOSE,
        WINDOW_RESIZED,
        KEY_PRESSED,
        MAX_EVENT_TYPE = 0xff,
    };

    class Event
    {
        public:
        EventsTypes m_eventType = EventsTypes::MAX_EVENT_TYPE;
    };


    class EventWindowClose : public Event
    {
        public:
        EventWindowClose() : m_eventType(EventsTypes::WINDOW_CLOSE)
        {
        }
    };
} // namespace DadEngine

#endif // !__EVENT_HPP_

