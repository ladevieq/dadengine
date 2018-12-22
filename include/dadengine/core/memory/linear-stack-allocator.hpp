#ifndef __LINEAR_STACK_ALLOCATOR_HPP_
#define __LINEAR_STACK_ALLOCATOR_HPP_

#include "allocator.hpp"

#include "memory-manager.hpp"


namespace DadEngine::Core//::Memory
{
    template<typename T>
	class LinearStackAllocator : public Allocator<T>
	{
	public:

		using Allocator<T>::Allocator;

		LinearStackAllocator() = default;

        LinearStackAllocator(const LinearStackAllocator<T> &_InMoveInstance)
        {
            if (_InMoveInstance.m_ptrMemLocation != nullptr)
            {
                this->m_ptrMemLocation = static_cast<T *>(
                MemoryManager::Allocate(_InMoveInstance.m_uiCapacity, _InMoveInstance.m_ItemSize));

                this->m_ItemSize = _InMoveInstance.m_ItemSize;
                this->m_uiCapacity = _InMoveInstance.m_uiCapacity;

                MemoryManager::Copy(_InMoveInstance.m_ptrMemLocation, this->m_ptrMemLocation,
                                    this->m_ItemSize * this->m_uiCapacity);
            }
        }

		LinearStackAllocator(LinearStackAllocator<T>&& _InMoveInstance) = default;


		~LinearStackAllocator()
        {
            this->Deallocate();
        }


        LinearStackAllocator<T>& operator=(const LinearStackAllocator<T> &_InMoveInstance)
        {
            if (_InMoveInstance.m_ptrMemLocation != nullptr)
            {
                this->m_ptrMemLocation = static_cast<T *>(
                MemoryManager::Allocate(_InMoveInstance.m_uiCapacity, _InMoveInstance.m_ItemSize));

                this->m_ItemSize = _InMoveInstance.m_ItemSize;
                this->m_uiCapacity = _InMoveInstance.m_uiCapacity;

                MemoryManager::Copy(_InMoveInstance.m_ptrMemLocation, this->m_ptrMemLocation,
                                    this->m_ItemSize * this->m_uiCapacity);
            }

            return *this;
        }

		LinearStackAllocator<T>& operator= (LinearStackAllocator<T>&& _InMoveInstance) = default;


        void Allocate(size_t _InItemCout)
        {
            this->m_ptrMemLocation = static_cast<T *>(MemoryManager::Allocate(_InItemCout, this->m_ItemSize));

            this->m_uiCapacity = _InItemCout;

            ASSERT(this->m_ptrMemLocation);
        }

        void Deallocate()
        {
            if (this->m_ptrMemLocation != nullptr)
            {
                MemoryManager::Deallocate(this->m_ptrMemLocation);
                this->m_ptrMemLocation = nullptr;
                this->m_uiCapacity = 0U;
            }
        }

		void Resize(size_t _InItemCout)
        {
            void *ptrTempMemory = static_cast<T *>(MemoryManager::Allocate(_InItemCout, this->m_ItemSize));

            this->m_uiCapacity = _InItemCout;

            if (this->m_ptrMemLocation != nullptr)
            {
                // Copy content to the new memory location
                MemoryManager::Copy((void *)this->m_ptrMemLocation, ptrTempMemory, this->m_ItemSize * _InItemCout);

                MemoryManager::Deallocate(this->m_ptrMemLocation);
            }

            this->m_ptrMemLocation = static_cast<T *>(ptrTempMemory);
        }
	};
}

#endif //__LINEAR_STACK_ALLOCATOR_HPP_