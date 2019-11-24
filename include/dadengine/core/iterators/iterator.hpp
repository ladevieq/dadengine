#ifndef __ITERATOR_HPP_
#define __ITERATOR_HPP_


namespace DadEngine
{
    template <typename T>
    struct Iterator
    {
        Iterator() = default;
        Iterator(T *_InMemLocation, size_t _InSize)
            : m_ptrMemLocation(_InMemLocation), m_size(_InSize)
        {
        }


        protected:
        T *m_ptrMemLocation = nullptr;
        const size_t m_typeSize = sizeof(T);
        const size_t m_size = 0U;
    };
} // namespace DadEngine

#endif //__ITERATOR_HPP_

