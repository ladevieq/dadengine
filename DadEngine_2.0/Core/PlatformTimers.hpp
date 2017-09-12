#ifndef __PLATFROM_TIME_HPP_
#define	__PLATFROM_TIME_HPP_

#if defined (WINDOWS)
#include "Platform/Windows/WindowsTimers.hpp"

namespace DadEngine::Core {
	using PlatformTimer = DadEngine::Core::WindowsTimer;
}

#endif

#endif //__PLATFROM_TIME_HPP_