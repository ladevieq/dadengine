#include "WindowsFileSystem.hpp"

#include "../../IFile.hpp"
#include "WindowsTextFileIO.hpp"
#include "WindowsBinaryFileIO.hpp"

namespace DadEngine::Core
{
    void WindowsFileSystem::CreatDirectory()
    {
        // CreateDirectoryExA()
    }

    // Ambiguous we can read and write
    IFile *WindowsFileSystem::CreateFileReader(const char *_InFilePath, IOMode _InFileFormat)
    {
        if (_InFileFormat == IO_MODE_TEXT)
        {
            return new PlatformTextFile(_InFilePath, IO_MODE_READ);
        }
        else
        {
            return new PlatformBinaryFile(_InFilePath, IO_MODE_READ);
        }
    }

    // Ambiguous we can read and write
    IFile *WindowsFileSystem::CreateTextFileWriter(const char *_InFilePath, IOMode _InFileFormat)
    {
        if (_InFileFormat == IO_MODE_TEXT)
        {
            return new PlatformTextFile(_InFilePath, IO_MODE_WRITE);
        }
        else
        {
            return new PlatformBinaryFile(_InFilePath, IO_MODE_WRITE);
        }
    }


    void WindowsFileSystem::FileExists(const char *_InFilePath)
    {
    }
}