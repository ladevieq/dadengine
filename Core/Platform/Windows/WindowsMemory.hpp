#ifndef __WINDOWS_MEMORY_HPP_
#define __WINDOWS_MEMORY_HPP_

#include <Windows.h>
#include <stdio.h>

namespace DadEngine::Core
{
	class WindowsMemory
	{

	public:

		static void GetStatus();
	};
}

using PlatformMemory = DadEngine::Core::WindowsMemory;

#endif //__WINDOWS_MEMORY_HPP_