#ifndef __THREADS_STATES_HPP_
#define __THREADS_STATES_HPP_

namespace DadEngine
{
    enum ThreadState
    {
        CREATED,
        WORKING,
        STOPPED,
        DONE,
        TERMINATED,
        MAX_THREAD_STATE
    };
}

#endif //__THREADS_STATES_HPP_

