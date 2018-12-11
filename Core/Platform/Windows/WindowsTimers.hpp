#ifndef __WINDOWS_TIMERS_HPP_
#define __WINDOWS_TIMERS_HPP_

#include <Windows.h>

#include "WindowsTypes.hpp"

namespace DadEngine::Core
{
    class WindowsTimer
    {
        public:
        WindowsTimer() = default;
        ~WindowsTimer() = default;

        void Start();

        void Stop();

        void Reset();

        uint64 GetSeconds();

        uint64 GetMilliseconds();

        uint64 GetMicroseconds();

        uint64 GetNanoseconds();


        private:
        LARGE_INTEGER m_StartTime;
        LARGE_INTEGER m_Frequency;
    };

	namespace Test
    {
        void TestTime();
    } // namespace Test
} // namespace DadEngine::Core

using PlatformTimer = DadEngine::Core::WindowsTimer;

#endif //__WINDOWS_TIMERS_HPP_