#ifndef __LINEAR_STACK_ITERATOR_HPP_
#define __LINEAR_STACK_ITERATOR_HPP_

namespace DadEngine::Core
{
	template<typename T>
	class LinearStackIterator : public Iterator<T>
	{

	public:

		LinearStackIterator() = default;
		LinearStackIterator(T* _InMemLocation, size_t _InSize) : Iterator<T>(_InMemLocation, _InSize) {}

		~LinearStackIterator() = default;


		FORCE_INLINE Iterator<T>& operator++ () { this->m_ptrMemLocation++; return *this; };

		FORCE_INLINE T& operator* () const { return *this->m_ptrMemLocation; };

		FORCE_INLINE uint8 operator != (const LinearStackIterator<T>& _InEqual) const { return this->m_ptrMemLocation != _InEqual.m_ptrMemLocation; };
	};
}

#endif //__LINEAR_STACK_ITERATOR_HPP_