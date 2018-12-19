#ifndef __MEMORY_READER_HPP_
#define __MEMORY_READER_HPP_

namespace DadEngine::Core
{
	class MemoryReader : public Archive
	{

	public:

		MemoryReader(TArray<uint8_t>& _InData) : Archive(_InData, TRUE) {}


	private:

		void Serialize(void* _InValue, int32_t _InSize) override final
		{
			MemoryManager::Copy(&m_Data[m_uiOffset], _InValue, _InSize);

			m_uiOffset += _InSize;
		}
	};
}

#endif //__MEMORY_READER_HPP_