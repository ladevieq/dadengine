#ifndef __TARRAY_HPP_
#define __TARRAY_HPP_

#include <cstdint>

#include "../../defines.hpp"
#include "../../iterators/linear-stack-iterator.hpp"
#include "../../memory/linear-stack-allocator.hpp"

namespace DadEngine
{
    template <typename T, typename Alloc = LinearStackAllocator<T>>
    class TArray
    {

        public:
        TArray() = default;

        TArray(size_t _InItemCount)
        {
            m_allocator.Allocate(_InItemCount);
        }

        TArray(size_t _InItemCount, T _InInitValue)
        {
            m_allocator.Allocate(_InItemCount);

            MemoryManager::Set(m_allocator.m_ptrMemLocation,
                               *(int32_t *)&_InInitValue, _InItemCount);
        }

        TArray(T *_InValues, size_t _InItemCount)
        {
            m_allocator.Allocate(_InItemCount);

            MemoryManager::Copy(_InValues, m_allocator.m_ptrMemLocation,
                                _InItemCount * sizeof(T));
        }

        ~TArray() = default;


        TArray<T, Alloc> &operator=(const TArray &_InCpy)
        {
            m_allocator = _InCpy.m_allocator;
            m_uiLastItemIndex = _InCpy.m_uiLastItemIndex;

            return *this;
        }


        void Reserve(size_t _InSize)
        {
            m_allocator.Allocate(_InSize);
        }

        void AddCapacity(size_t _InSize)
        {
            Resize(m_allocator.m_uiCapacity + _InSize);
        }

        void Add(T _InNewItem)
        {
            if (m_uiLastItemIndex >= m_allocator.m_uiCapacity)
                Resize(m_allocator.m_uiCapacity + 1U);

            m_allocator.m_ptrMemLocation[m_uiLastItemIndex] = _InNewItem;
            m_uiLastItemIndex++;
        }

        void Add(T *_InValues, size_t _InItemCount)
        {
            if (m_uiLastItemIndex + _InItemCount >= m_allocator.m_uiCapacity)
                Resize(m_allocator.m_uiCapacity + _InItemCount);

            MemoryManager::Copy(_InValues, m_allocator.m_ptrMemLocation + m_uiLastItemIndex,
                                _InItemCount * sizeof(T));
            m_uiLastItemIndex += (uint32_t)_InItemCount;
        }

        void Resize(size_t _InItemCount)
        {
            m_allocator.Resize(_InItemCount);
        }

        void Clear()
        {
            m_allocator.Deallocate();

            m_uiLastItemIndex = 0U;
        }


        T &operator[](uint32_t _InIndex)
        {
            return m_allocator.m_ptrMemLocation[_InIndex];
        }

        uint8_t IsEmpty() const
        {
            return m_uiLastItemIndex == 0 ? TRUE : FALSE;
        }

        T *GetData() const
        {
            return m_allocator.m_ptrMemLocation;
        }

        size_t Size() const
        {
            return m_allocator.m_uiCapacity;
        }

        T &Last() const
        {
            return m_allocator.m_ptrMemLocation[m_allocator.m_uiCapacity - 1U];
        }


        // Iterator
        LinearStackIterator<T> begin() const
        {
            return LinearStackIterator<T>(m_allocator.m_ptrMemLocation,
                                          m_allocator.m_uiCapacity);
        }

        LinearStackIterator<T> end() const
        {
            return LinearStackIterator<T>(m_allocator.m_ptrMemLocation +
                                              m_allocator.m_uiCapacity,
                                          0U);
        }


        private:
        Alloc m_allocator = Alloc();

        uint32_t m_uiLastItemIndex = 0U;
    };

    // using namespace DadEngine::Containers;

    namespace Test
    {
        void TestTArray();
    }
} // namespace DadEngine

#endif //__TARRAY_HPP_
