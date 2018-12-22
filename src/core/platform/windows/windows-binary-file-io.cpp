#include "windows-binary-file-io.hpp"

#include "../../defines.hpp"
#include "../../debug.hpp"
#include "../../types/string.hpp"

namespace DadEngine::Core
{
    WindowsBinaryFile::WindowsBinaryFile (const char *_InFilePath, IOModeFlag _InIOMode)
    {
        switch (_InIOMode)
        {
        case IO_MODE_READ:
            LOG_ASSERT (OpenRead (_InFilePath) != FALSE, "File doesn't exist !");
            break;
        case IO_MODE_WRITE:
            LOG_ASSERT (OpenWrite (_InFilePath) != FALSE, "File doesn't exist !");
            break;
        case IO_MODE_WRITE | IO_MODE_READ:
            m_fileHandle = fopen (_InFilePath, "rb+");
            break;
        case IO_MODE_APPEND:
            m_fileHandle = fopen (_InFilePath, "ab");
            break;
        }
    }

    WindowsBinaryFile::~WindowsBinaryFile ()
    {
        fclose (m_fileHandle);
    }


    uint8_t WindowsBinaryFile::OpenRead(const char *_InFilePath)
    {
        m_fileHandle = fopen (_InFilePath, "rb");

        return m_fileHandle != nullptr;
    }

    uint8_t WindowsBinaryFile::Read(uint8_t *_InDst, size_t _InBytesToRead)
    {
        size_t size = fread (_InDst, 1U, _InBytesToRead, m_fileHandle);
        return size == _InBytesToRead;
    }

    uint8_t WindowsBinaryFile::Read(String &_InDst)
    {
        size_t size = fread((void *)_InDst.Cstr(), sizeof(uint8_t), _InDst.Size(), m_fileHandle);
        return size == _InDst.Size ();
    }


    uint8_t WindowsBinaryFile::OpenWrite(const char *_InFilePath)
    {
        m_fileHandle = fopen (_InFilePath, "wb");

        return m_fileHandle != nullptr;
    }

    uint8_t WindowsBinaryFile::Write(uint8_t *_InSrc, size_t _InBytesToWrite)
    {
        size_t size = fwrite (_InSrc, 1U, _InBytesToWrite, m_fileHandle);
        return size == _InBytesToWrite;
    }

    uint8_t WindowsBinaryFile::Write(String &_InDst)
    {
        size_t size = fread ((void *)_InDst.Cstr (), 1U, _InDst.Size (), m_fileHandle);
        return size == _InDst.Size ();
    }

    void WindowsBinaryFile::Close ()
    {
        fclose (m_fileHandle);
    }

    size_t WindowsBinaryFile::Size ()
    {
        int64_t pos;
        size_t size = 0U;
        fgetpos (m_fileHandle, &pos);
        fseek (m_fileHandle, 0, SEEK_END);

        size = (size_t)ftell (m_fileHandle);

        fseek (m_fileHandle, (int32_t)pos, SEEK_SET);

        return size;
    }
} // namespace DadEngine::Core