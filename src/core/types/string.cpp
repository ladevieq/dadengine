#include "string.hpp"

#include <cstring>

#include "../memory/memory-manager.hpp"


namespace DadEngine
{
    String::String(const char *_InContent) : m_string(strlen(_InContent))
    {
        MemoryManager::Copy(reinterpret_cast<void *>(const_cast<char *>(_InContent)),
                            m_string.GetData(), m_string.Size());
    }

    String::String(size_t _InSize) : m_string(_InSize, '\0')
    {
    }

    void String::operator=(char *&_InSrc)
    {
        size_t size = strlen(_InSrc);
        m_string.Reserve(size);

        MemoryManager::Copy(reinterpret_cast<void *>(_InSrc), m_string.GetData(), size);
    }

    /*void String::operator= (char*&& _InSrc)
    {
        if (m_allocator.m_ptrMemLocation)
        {
            m_allocator.Deallocate();
        }

        m_allocator. strlen(_InSrc);
        m_allocator.m_ptrMemLocation = _InSrc;
    }*/


    void String::Append(String &_InNewString)
    {
        size_t currentSize = m_string.Size();
        size_t appendSize = _InNewString.Size();

        m_string.Resize(currentSize + appendSize);

        MemoryManager::Copy(reinterpret_cast<void *>(
                                const_cast<char *>(_InNewString.Cstr())),
                            &m_string[static_cast<uint32_t>(currentSize - 1U)], appendSize);
    }

    void String::Append(const char *_InNewCString)
    {
        size_t currentSize = m_string.Size();
        size_t appendSize = strlen(_InNewCString);

        m_string.Resize(currentSize + appendSize);

        MemoryManager::Copy(reinterpret_cast<void *>(const_cast<char *>(_InNewCString)),
                            &m_string[static_cast<uint32_t>(currentSize - 1U)], appendSize);
    }

    const char *String::Cstr() const
    {
        return m_string.GetData();
    }

    size_t String::Size()
    {
        return m_string.Size();
    }
} // namespace DadEngine

