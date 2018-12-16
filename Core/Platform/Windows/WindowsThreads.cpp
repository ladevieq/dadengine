#include "WindowsThreads.hpp"

#include <stdio.h>

#include "../../Defines.hpp"

namespace DadEngine::Core
{

    WindowsThread::WindowsThread (uint8_t _InStart, Job _InJob)
    {
        m_ptrJobFunction = _InJob;

        m_ThreadHandle = CreateThread (NULL, 0U, (LPTHREAD_START_ROUTINE)Work, this,
                                       _InStart ? NULL : CREATE_SUSPENDED, NULL);

        ASSERT (m_ThreadHandle);

        m_eThreadState = _InStart ? WORKING : CREATED;
    }

    WindowsThread::~WindowsThread ()
    {
        if (m_eThreadState == WORKING || m_eThreadState == STOPPED || m_eThreadState == CREATED)
            Kill ();
    }


    // Change the thread priority for the scheduler
    void WindowsThread::ChangePriority (int32_t _InThreadPriority)
    {
        SetThreadPriority (this->m_ThreadHandle, _InThreadPriority);
    }


    // Start or resume the thread
    void WindowsThread::Resume ()
    {
        ResumeThread (m_ThreadHandle);

        m_eThreadState = WORKING;
    }

    void WindowsThread::Stop ()
    {
        SuspendThread (m_ThreadHandle);

        m_eThreadState = STOPPED;
    }

    void WindowsThread::Kill ()
    {
        TerminateThread (m_ThreadHandle, 0U);

        CloseHandle (m_ThreadHandle);

        m_eThreadState = TERMINATED;
    }


    // Execute the thread task
    void WindowsThread::Work (WindowsThread *_ptrJob)
    {
        _ptrJob->m_ptrJobFunction ();

        _ptrJob->m_eThreadState = DONE;
    }

	namespace Test
    {
        void TestThread ()
        {
            auto func = []() {
                while (1)
                {
                    printf ("Hello World!");
                }
            };

            WindowsThread thread (FALSE, func);

            Sleep (1000);

            thread.Resume ();

            Sleep (1000);

            thread.Stop ();

            Sleep (1000);

            thread.Resume ();

            Sleep (3000);

            thread.Kill ();
        }
    } // namespace Test
}