#ifndef __PLATFORM_WINDOW_HPP_
#define __PLATFORM_WINDOW_HPP_


#if defined (WINDOWS)

#include "Platform/Windows/WindowsWindow.hpp"

namespace DadEngine::Core {
	using PlatformWindow = WindowsWindow;
}

#endif

#endif //__PLATFORM_WINDOW_HPP_