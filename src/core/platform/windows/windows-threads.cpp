#include "windows-threads.hpp"

#include <cstdio>

#include "debug.hpp"

namespace DadEngine
{

    WindowsThread::WindowsThread(uint8_t _InStart, Job _InJob)
    {
        m_ptrJobFunction = _InJob;

        m_ThreadHandle =
            CreateThread(nullptr, 0U, reinterpret_cast<LPTHREAD_START_ROUTINE>(Work),
                         this, _InStart ? NULL : CREATE_SUSPENDED, nullptr);

        Assert(m_ThreadHandle);

        m_eThreadState = _InStart ? WORKING : CREATED;
    }

    WindowsThread::~WindowsThread()
    {
        if (m_eThreadState == WORKING || m_eThreadState == STOPPED || m_eThreadState == CREATED)
            Kill();
    }


    // Change the thread priority for the scheduler
    void WindowsThread::ChangePriority(int32_t _InThreadPriority)
    {
        SetThreadPriority(this->m_ThreadHandle, _InThreadPriority);
    }


    // Start or resume the thread
    void WindowsThread::Resume()
    {
        ResumeThread(m_ThreadHandle);

        m_eThreadState = WORKING;
    }

    void WindowsThread::Stop()
    {
        SuspendThread(m_ThreadHandle);

        m_eThreadState = STOPPED;
    }

    void WindowsThread::Kill()
    {
        TerminateThread(m_ThreadHandle, 0U);

        CloseHandle(m_ThreadHandle);

        m_eThreadState = TERMINATED;
    }


    // Execute the thread task
    void WindowsThread::Work(WindowsThread *_ptrJob)
    {
        _ptrJob->m_ptrJobFunction();

        _ptrJob->m_eThreadState = DONE;
    }

} // namespace DadEngine
