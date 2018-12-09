#ifndef __LINEAR_STACK_ALLOCATOR_HPP_
#define __LINEAR_STACK_ALLOCATOR_HPP_

#include "Allocator.hpp"


namespace DadEngine::Core//::Memory
{
    template<typename T>
	class LinearStackAllocator : public Allocator<T>
	{
	public:

		using Allocator<T>::Allocator;

		LinearStackAllocator() = default;

		LinearStackAllocator (const LinearStackAllocator<T> &_InMoveInstance);

		LinearStackAllocator(LinearStackAllocator<T>&& _InMoveInstance) = default;

		~LinearStackAllocator ();


		LinearStackAllocator<T>& operator= (const LinearStackAllocator<T> &_InMoveInstance);

		LinearStackAllocator<T>& operator= (LinearStackAllocator<T>&& _InMoveInstance) = default;


		void Allocate (size_t _InItemCout);

		void Deallocate ();

		void Resize (size_t _InItemCout);
	};
}

#endif //__LINEAR_STACK_ALLOCATOR_HPP_