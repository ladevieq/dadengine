#ifndef __PLATFROM_THREADS_HPP_
#define	__PLATFROM_THREADS_HPP_


enum ThreadState
{
	CREATED,
	WORKING,
	STOPPED,
	DONE,
	TERMINATED,
	MAX_THREAD_STATE,
};

#if defined (WINDOWS)
#include "Platform/Windows/WindowsThreads.hpp"
#endif


#endif //__PLATFROM_THREADS_HPP_