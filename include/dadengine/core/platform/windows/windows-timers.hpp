#ifndef __WINDOWS_TIMERS_HPP_
#define __WINDOWS_TIMERS_HPP_

#include <cstdint>

#include <Windows.h>


namespace DadEngine
{
    class WindowsTimer
    {
        public:
        WindowsTimer() = default;
        ~WindowsTimer() = default;

        void Start();

        void Stop();

        void Reset();

        uint64_t GetSeconds();

        uint64_t GetMilliseconds();

        uint64_t GetMicroseconds();

        uint64_t GetNanoseconds();


        private:
        LARGE_INTEGER m_StartTime;
        LARGE_INTEGER m_Frequency;
    };

    namespace Test
    {
        void TestTime();
    } // namespace Test
} // namespace DadEngine

using PlatformTimer = DadEngine::WindowsTimer;

#endif //__WINDOWS_TIMERS_HPP_

