#include "LinearStackAllocator.hpp"

#include "Allocator.hpp"


namespace DadEngine::Core
{
    template <typename T>
    LinearStackAllocator<T>::LinearStackAllocator (const LinearStackAllocator<T> &_InMoveInstance)
    {
        if (_InMoveInstance.m_ptrMemLocation != nullptr)
        {
            this->m_ptrMemLocation = static_cast<T *> (
            MemoryManager::Allocate (_InMoveInstance.m_uiCapacity, _InMoveInstance.m_ItemSize));

            this->m_ItemSize = _InMoveInstance.m_ItemSize;
            this->m_uiCapacity = _InMoveInstance.m_uiCapacity;

            MemoryManager::Copy (_InMoveInstance.m_ptrMemLocation, this->m_ptrMemLocation,
                                 this->m_ItemSize * this->m_uiCapacity);
        }
    }

    template <typename T>
    LinearStackAllocator<T>::~LinearStackAllocator ()
    {
        Deallocate ();
    }


    template <typename T>
    LinearStackAllocator<T> &LinearStackAllocator<T>::operator= (const LinearStackAllocator<T> &_InMoveInstance)
    {
        if (_InMoveInstance.m_ptrMemLocation != nullptr)
        {
            this->m_ptrMemLocation = static_cast<T *> (
            MemoryManager::Allocate (_InMoveInstance.m_uiCapacity, _InMoveInstance.m_ItemSize));

            this->m_ItemSize = _InMoveInstance.m_ItemSize;
            this->m_uiCapacity = _InMoveInstance.m_uiCapacity;

            MemoryManager::Copy (_InMoveInstance.m_ptrMemLocation, this->m_ptrMemLocation,
                                 this->m_ItemSize * this->m_uiCapacity);
        }

        return *this;
    }

	template <typename T>
	void LinearStackAllocator<T>::Allocate (size_t _InItemCout)
    {
        this->m_ptrMemLocation = static_cast<T *> (MemoryManager::Allocate (_InItemCout, this->m_ItemSize));

        this->m_uiCapacity = _InItemCout;

        ASSERT (this->m_ptrMemLocation);
    }

	template <typename T>
    void LinearStackAllocator<T>::Deallocate ()
    {
        if (this->m_ptrMemLocation != nullptr)
        {
            MemoryManager::Deallocate (this->m_ptrMemLocation);
            this->m_ptrMemLocation = nullptr;
            this->m_uiCapacity = 0U;
        }
    }

	template <typename T>
    void LinearStackAllocator<T>::Resize (size_t _InItemCout)
    {
        void *ptrTempMemory = static_cast<T *> (MemoryManager::Allocate (_InItemCout, this->m_ItemSize));

        this->m_uiCapacity = _InItemCout;

        if (this->m_ptrMemLocation != nullptr)
        {
            // Copy content to the new memory location
            MemoryManager::Copy ((void *)this->m_ptrMemLocation, ptrTempMemory, this->m_ItemSize * _InItemCout);

            MemoryManager::Deallocate (this->m_ptrMemLocation);
        }

        this->m_ptrMemLocation = static_cast<T *> (ptrTempMemory);
    }
} // namespace DadEngine::Core