#ifndef __WINDOWS_THREADS_HPP_
#define __WINDOWS_THREADS_HPP_

#include <Windows.h>

#include "../ThreadsStates.hpp"
#include "WindowsTypes.hpp"


namespace DadEngine::Core
{
    class WindowsThread
    {
        public:
        using Job = void (*)(void);

        WindowsThread(uint8 _InStart, Job _InJob);

        ~WindowsThread();


        // Change the thread priority for the scheduler
        void ChangePriority(int32 _InThreadPriority);


        // Start or resume the thread
        void Resume();

        void Stop();

        void Kill();


        // Execute the thread task
        static void Work(WindowsThread *_ptrJob);


        private:
        Job m_ptrJobFunction = nullptr;
        HANDLE m_ThreadHandle = nullptr;
        ThreadState m_eThreadState = CREATED;
    };

	namespace Test
    {
        void TestThread();
    } // namespace Test
} // namespace DadEngine::Core

#endif //__WINDOWS_THREADS_HPP_