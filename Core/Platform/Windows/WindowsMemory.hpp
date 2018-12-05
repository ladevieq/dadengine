#ifndef __WINDOWS_MEMORY_HPP_
#define __WINDOWS_MEMORY_HPP_

#include <Windows.h>
#include <stdio.h>

namespace DadEngine::Core
{
	class WindowsMemory
	{

	public:

		static void GetStatus()
		{
			MEMORYSTATUSEX status = {};
			status.dwLength = sizeof(status);

			GlobalMemoryStatusEx(&status);

			printf("%s%llu\n", "Available physical memory : ", status.ullAvailPhys);
			printf("%s%llu\n", "Available virtual memory : ", status.ullAvailVirtual);
			printf("%s%llu\n", "Total physical memory : ", status.ullTotalPhys);
			printf("%s%llu\n", "Toral virtual memory : ", status.ullTotalVirtual);
		}
	};
}

using PlatformMemory = DadEngine::Core::WindowsMemory;

#endif //__WINDOWS_MEMORY_HPP_