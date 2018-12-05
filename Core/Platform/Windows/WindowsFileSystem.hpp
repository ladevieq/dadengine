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

		// Ambiguous we can read and write
		static IFile* CreateFileReader(const char* _InFilePath, IOMode _InFileFormat)
		{
			if (_InFileFormat == IO_MODE_TEXT)
				return new PlatformTextFile(_InFilePath, IO_MODE_READ);
			else
				return new PlatformBinaryFile(_InFilePath, IO_MODE_READ);
		}

		// Ambiguous we can read and write
		static IFile* CreateTextFileWriter(const char* _InFilePath, IOMode _InFileFormat)
		{
			if(_InFileFormat == IO_MODE_TEXT)
				return new PlatformTextFile(_InFilePath, IO_MODE_WRITE);
			else
				return new PlatformBinaryFile(_InFilePath, IO_MODE_WRITE);
		}


		static void FileExists(const char* _InFilePath)
		{

		}
	};

	using PlatformFileSystem = WindowsFileSystem;
}

#endif // !__WINDOWS_FILE_SYSTEM_HPP_