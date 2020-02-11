#ifndef __LINEAR_STACK_ITERATOR_HPP_
#define __LINEAR_STACK_ITERATOR_HPP_

#include <cstdint>

#include "iterator.hpp"


namespace DadEngine
{
    template <typename T>
    class LinearStackIterator : public Iterator<T>
    {

        public:
        LinearStackIterator() = default;
        LinearStackIterator(T *_InMemLocation, size_t _InSize)
            : Iterator<T>(_InMemLocation, _InSize)
        {
        }


        Iterator<T> &operator++()
        {
            this->m_ptrMemLocation++;
            return *this;
        }

        T &operator*() const
        {
            return *this->m_ptrMemLocation;
        }

        uint8_t operator!=(const LinearStackIterator<T> &_InEqual) const
        {
            return this->m_ptrMemLocation != _InEqual.m_ptrMemLocation;
        }
    };
} // namespace DadEngine

#endif //__LINEAR_STACK_ITERATOR_HPP_

