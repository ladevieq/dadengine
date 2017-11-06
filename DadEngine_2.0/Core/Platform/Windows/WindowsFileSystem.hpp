#ifndef __WINDOWS_FILE_SYSTEM_HPP_
#define __WINDOWS_FILE_SYSTEM_HPP_

#include <Windows.h>

namespace DadEngine::Core
{
	struct WindowsFileSystem
	{
		static void CreatDirectory()
		{
			//CreateDirectoryExA()
		}


		static IFile* CreateTextFileReader(const char* _InFilePath)
		{
			return new PlatformFile(_InFilePath, IO_MODE_READ /*| IO_MODE_TEXT*/);
		}

		static IFile* CreateTextFileWriter(const char* _InFilePath)
		{
			return new PlatformFile(_InFilePath, IO_MODE_WRITE /*| IO_MODE_TEXT*/);
		}


		static void FileExists(const char* _InFilePath)
		{

		}
	};

	using PlatformFileSystem = WindowsFileSystem;
}

#endif // !__WINDOWS_FILE_SYSTEM_HPP_