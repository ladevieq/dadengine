#ifndef __WINDOWS_MEMORY_HPP_
#define __WINDOWS_MEMORY_HPP_


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