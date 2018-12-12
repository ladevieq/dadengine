#ifndef __MEMORY_WRITER_HPP_
#define __MEMORY_WRITER_HPP_


namespace DadEngine::Core
{
	class MemoryWriter : public Archive
	{

	public:

		MemoryWriter() : Archive() { m_bIsReading = FALSE; };


	private:

		void Serialize(void* _InValue, int32_t _InSize) override final
		{
			m_Data.AddCapacity(_InSize);

			MemoryManager::Copy(_InValue, &m_Data[m_uiOffset], _InSize);

			m_uiOffset += _InSize;
		}
	};
}

#endif //__MEMORY_WRITER_HPP_