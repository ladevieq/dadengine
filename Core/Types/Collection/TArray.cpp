#include "TArray.hpp"
#include <stdio.h>

#include "../../Platform/Types.hpp";
#include "../../Memory/Allocator.hpp"
#include "../../Memory/LinearStackAllocator.hpp"
#include "../../Iterators/LinearStackIterator.hpp"


namespace DadEngine::Core //::Containers
{
    template <typename T, typename Alloc>
    TArray<T, Alloc>::TArray(size_t _InItemCount)
    {
        m_allocator.Allocate(_InItemCount);
    }

    template <typename T, typename Alloc>
    TArray<T, Alloc>::TArray(size_t _InItemCount, T _InInitValue)
    {
        m_allocator.Allocate(_InItemCount);

        MemoryManager::Set(m_allocator.m_ptrMemLocation, *(int32 *)&_InInitValue, _InItemCount);
    }

    template <typename T, typename Alloc>
    TArray<T, Alloc>::TArray(T *_InValues, size_t _InItemCount)
    {
        m_allocator.Allocate(_InItemCount);

        MemoryManager::Copy(_InValues, m_allocator.m_ptrMemLocation, _InItemCount * sizeof(T));
    }


    template <typename T, typename Alloc>
    TArray<T, Alloc> &TArray<T, Alloc>::operator=(const TArray &_InCpy)
    {
        m_allocator = _InCpy.m_allocator;
        m_uiLastItemIndex = _InCpy.m_uiLastItemIndex;

        return *this;
    }


    template <typename T, typename Alloc>
    void TArray<T, Alloc>::Reserve(size_t _InSize)
    {
        m_allocator.Allocate(_InSize);
    }

    template <typename T, typename Alloc>
    void TArray<T, Alloc>::AddCapacity(size_t _InSize)
    {
        Resize(m_allocator.m_uiCapacity + _InSize);
    }

    template <typename T, typename Alloc>
    void TArray<T, Alloc>::Add(T _InNewItem)
    {
        if (m_uiLastItemIndex >= m_allocator.m_uiCapacity)
            Resize(m_allocator.m_uiCapacity + 1U);

        m_allocator.m_ptrMemLocation[m_uiLastItemIndex] = _InNewItem;
        m_uiLastItemIndex++;
    }

    template <typename T, typename Alloc>
    void TArray<T, Alloc>::Add(T *_InValues, size_t _InItemCount)
    {
        if (m_uiLastItemIndex + _InItemCount >= m_allocator.m_uiCapacity)
            Resize(m_allocator.m_uiCapacity + _InItemCount);

        MemoryManager::Copy(_InValues, m_allocator.m_ptrMemLocation + m_uiLastItemIndex,
                            _InItemCount * sizeof(T));
        m_uiLastItemIndex += (uint32)_InItemCount;
    }

    template <typename T, typename Alloc>
    void TArray<T, Alloc>::Resize(size_t _InItemCount)
    {
        m_allocator.Resize(_InItemCount);
    }

    template <typename T, typename Alloc>
    void TArray<T, Alloc>::Clear()
    {
        m_allocator.Deallocate();

        m_uiLastItemIndex = 0U;
    }


    template <typename T, typename Alloc>
    T &TArray<T, Alloc>::operator[](uint32 _InIndex)
    {
        return m_allocator.m_ptrMemLocation[_InIndex];
    }

    template <typename T, typename Alloc>
    uint8 TArray<T, Alloc>::IsEmpty() const
    {
        return m_uiLastItemIndex == 0 ? TRUE : FALSE;
    }

    template <typename T, typename Alloc>
    T *TArray<T, Alloc>::GetData() const
    {
        return m_allocator.m_ptrMemLocation;
    }

    template <typename T, typename Alloc>
    size_t TArray<T, Alloc>::Size() const
    {
        return m_allocator.m_uiCapacity;
    }

    template <typename T, typename Alloc>
    T &TArray<T, Alloc>::Last() const
    {
        return m_allocator.m_ptrMemLocation[m_allocator.m_uiCapacity - 1U];
    }


    // Iterator
    template <typename T, typename Alloc>
    LinearStackIterator<T> TArray<T, Alloc>::begin() const
    {
        return LinearStackIterator<T>(m_allocator.m_ptrMemLocation, m_allocator.m_uiCapacity);
    }

    template <typename T, typename Alloc>
    LinearStackIterator<T> TArray<T, Alloc>::end() const
    {
        return LinearStackIterator<T>(m_allocator.m_ptrMemLocation + m_allocator.m_uiCapacity, 0U);
    }

    namespace Test
    {
        static void TestTArray()
        {
            TArray<int32> eray;
            TArray<int32> bray;

            eray.Add(10);
            eray.Add(20);
            eray.Add(30);

            printf("%d\n", eray[0]);
            printf("%d\n", eray[1]);
            printf("%d\n", eray[2]);

            eray.Clear();

            bray = eray;

            for (int32 i : eray)
            {
                printf("%d\n", i);
            }

            eray.Add(10);
            eray.Add(20);

            eray[0U] = 10;

            /*printf("%d\n", bray[0]);
            printf("%d\n", bray[1]);
            printf("%d\n", bray[2]);*/

            // ASSERT(eray.IsEmpty() == TRUE);

            eray.Resize(100U);

            ASSERT(eray.Size() == 100U);

            eray.Resize(10U);

            ASSERT(eray.Size() == 10U);

            eray.Add(10);

            ASSERT(eray.IsEmpty() == FALSE);
        }
    } // namespace Test
} // namespace DadEngine::Core