#ifndef __LINEAR_STACK_ALLOCATOR_HPP_
#define __LINEAR_STACK_ALLOCATOR_HPP_


namespace DadEngine::Core//::Memory
{
	template<typename T>
	class LinearStackAllocator : public Allocator<T>
	{
	public:

		using Allocator::Allocator;

		LinearStackAllocator() = default;

		LinearStackAllocator(const LinearStackAllocator<T>& _InMoveInstance)
		{
			if (_InMoveInstance.m_ptrMemLocation != nullptr)
			{
				m_ptrMemLocation = static_cast<T*>(MemoryManager::Allocate(_InMoveInstance.m_uiCapacity, _InMoveInstance.m_ItemSize));

				m_ItemSize = _InMoveInstance.m_ItemSize;
				m_uiCapacity = _InMoveInstance.m_uiCapacity;

				MemoryManager::Copy(_InMoveInstance.m_ptrMemLocation, m_ptrMemLocation, m_ItemSize * m_uiCapacity);
			}
		}

		LinearStackAllocator(LinearStackAllocator<T>&& _InMoveInstance) = default;

		~LinearStackAllocator()
		{
				Deallocate();
		}

		LinearStackAllocator<T>& operator= (const LinearStackAllocator<T>& _InMoveInstance)
		{
			if (_InMoveInstance.m_ptrMemLocation != nullptr)
			{
				m_ptrMemLocation = static_cast<T*>(MemoryManager::Allocate(_InMoveInstance.m_uiCapacity, _InMoveInstance.m_ItemSize));

				m_ItemSize = _InMoveInstance.m_ItemSize;
				m_uiCapacity = _InMoveInstance.m_uiCapacity;

				MemoryManager::Copy(_InMoveInstance.m_ptrMemLocation, m_ptrMemLocation, m_ItemSize * m_uiCapacity);
			}

			return *this;
		}

		LinearStackAllocator<T>& operator= (LinearStackAllocator<T>&& _InMoveInstance) = default;


		FORCE_INLINE void Allocate(size_t _InItemCout)
		{
			m_ptrMemLocation = static_cast<T*>(MemoryManager::Allocate(_InItemCout, m_ItemSize));

			m_uiCapacity = _InItemCout;

			ASSERT(m_ptrMemLocation);
		}

		FORCE_INLINE void Deallocate()
		{
			if (m_ptrMemLocation != nullptr) {
				MemoryManager::Deallocate(m_ptrMemLocation);
							m_ptrMemLocation = nullptr;
			}
			
		}

		FORCE_INLINE void Resize(size_t _InItemCout)
		{
			void* ptrTempMemory = static_cast<T*>(MemoryManager::Allocate(_InItemCout, m_ItemSize));

			m_uiCapacity = _InItemCout;

			if (m_ptrMemLocation != nullptr)
			{
				// Copy content to the new memory location
				MemoryManager::Copy((void*)m_ptrMemLocation, ptrTempMemory, m_ItemSize * _InItemCout);
			}

			m_ptrMemLocation = static_cast<T*>(ptrTempMemory);
		}
	};
}

#endif //__LINEAR_STACK_ALLOCATOR_HPP_