#include "Archive.hpp"

namespace DadEngine::Core
{
    Archive::Archive(TArray<uint8> &_InData, b8 _InReading)
		: m_Data(_InData)
    {
    }

    TArray<uint8> &Archive::GetData()
    {
        return m_Data;
    }
}