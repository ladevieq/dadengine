#ifndef __WINDOWS_BINARY_FILE_IO_HPP_
#define __WINDOWS_BINARY_FILE_IO_HPP_

#include <stdio.h>

#include "../../IFile.hpp"


namespace DadEngine::Core
{
    class String;
    // Use windows IO stuff ?

    struct WindowsBinaryFile : public IFile
    {
        WindowsBinaryFile(const char *_InFilePath, IOModeFlag _InIOMode);

        ~WindowsBinaryFile();


        b8 OpenRead(const char *_InFilePath) override final;

        b8 Read(uint8 *_InDst, size_t _InBytesToRead) override final;

        b8 Read(String &_InDst) override final;


        b8 OpenWrite(const char *_InFilePath) override final;

        b8 Write(uint8 *_InSrc, size_t _InBytesToWrite) override final;

        b8 Write(String &_InDst) override final;

        void Close() override final;

        size_t Size() override final;

        FILE *m_fileHandle = nullptr;
    };

    using PlatformBinaryFile = WindowsBinaryFile;
} // namespace DadEngine::Core

#endif //!__WINDOWS_BINARY_FILE_IO_HPP_