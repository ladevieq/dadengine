#ifndef __WINDOWS_FILE_SYSTEM_HPP_
#define __WINDOWS_FILE_SYSTEM_HPP_

#include "WindowsTypes.hpp"


namespace DadEngine::Core
{
    struct IFile;
    enum IOMode: uint8;

    struct WindowsFileSystem
    {
        static void CreatDirectory ();

        // Ambiguous we can read and write
        static IFile *CreateFileReader(const char *_InFilePath, IOMode _InFileFormat);

        // Ambiguous we can read and write
        static IFile *CreateTextFileWriter(const char *_InFilePath, IOMode _InFileFormat);


        static void FileExists(const char *_InFilePath);
    };

    using PlatformFileSystem = WindowsFileSystem;
} // namespace DadEngine::Core

#endif // !__WINDOWS_FILE_SYSTEM_HPP_