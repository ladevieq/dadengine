#include "windows-text-file-io.hpp"

#include "../../debug.hpp"
#include "../../defines.hpp"
#include "../../types/string.hpp"

namespace DadEngine
{
    WindowsTextFile::WindowsTextFile(const char *_InFilePath, IOModeFlag _InIOMode)
    {
        switch (_InIOMode)
        {
        case IO_MODE_READ:
            LogAssert(OpenRead(_InFilePath) != false, "File doesn't exist !",
                      __FILE__, __LINE__);
            break;
        case IO_MODE_WRITE:
            LogAssert(OpenWrite(_InFilePath) != false, "File doesn't exist !",
                      __FILE__, __LINE__);
            break;
        case IO_MODE_WRITE | IO_MODE_READ:
            m_fileHandle = fopen(_InFilePath, "r+");
            break;
        case IO_MODE_APPEND:
            m_fileHandle = fopen(_InFilePath, "a");
            break;
        }
    }

    WindowsTextFile::~WindowsTextFile()
    {
        fclose(m_fileHandle);
    }


    uint8_t WindowsTextFile::OpenRead(const char *_InFilePath)
    {
        m_fileHandle = fopen(_InFilePath, "rt");

        return m_fileHandle != nullptr;
    }

    uint8_t WindowsTextFile::Read(uint8_t *_InDst, size_t _InBytesToRead)
    {
        size_t size = fread(_InDst, 1U, _InBytesToRead, m_fileHandle);
        return size == _InBytesToRead;
    }

    uint8_t WindowsTextFile::Read(String &_InDst)
    {
        size_t size = fread(reinterpret_cast<void *>(const_cast<char *>(_InDst.Cstr())),
                            sizeof(uint8_t), _InDst.Size(), m_fileHandle);
        return size == _InDst.Size();
    }


    uint8_t WindowsTextFile::OpenWrite(const char *_InFilePath)
    {
        m_fileHandle = fopen(_InFilePath, "wt");

        return m_fileHandle != nullptr;
    }

    uint8_t WindowsTextFile::Write(uint8_t *_InSrc, size_t _InBytesToWrite)
    {
        size_t size = fwrite(_InSrc, 1U, _InBytesToWrite, m_fileHandle);
        return size == _InBytesToWrite;
    }

    uint8_t WindowsTextFile::Write(String &_InDst)
    {
        size_t size = fread(reinterpret_cast<void *>(const_cast<char *>(_InDst.Cstr())),
                            1U, _InDst.Size(), m_fileHandle);
        return size == _InDst.Size();
    }

    void WindowsTextFile::Close()
    {
        fclose(m_fileHandle);
    }

    size_t WindowsTextFile::Size()
    {
        int64_t pos;
        size_t size = 0U;
        fgetpos(m_fileHandle, &pos);
        fseek(m_fileHandle, 0, SEEK_END);

        size = static_cast<size_t>(ftell(m_fileHandle));

        fseek(m_fileHandle, static_cast<int32_t>(pos), SEEK_SET);

        return size;
    }
} // namespace DadEngine
