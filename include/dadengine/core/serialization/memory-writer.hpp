#ifndef __MEMORY_WRITER_HPP_
#define __MEMORY_WRITER_HPP_

namespace DadEngine
{
    class MemoryWriter : public Archive
    {

        public:
        MemoryWriter() : Archive()
        {
            m_bIsReading = FALSE;
        }


        private:
        void Serialize(void *_InValue, size_t _InSize) override final
        {
            m_Data.AddCapacity(_InSize);

            MemoryManager::Copy(_InValue, &m_Data[static_cast<uint32_t>( m_uiOffset )], _InSize);

            this->m_uiOffset += _InSize;
        }
    };
} // namespace DadEngine

#endif //__MEMORY_WRITER_HPP_

