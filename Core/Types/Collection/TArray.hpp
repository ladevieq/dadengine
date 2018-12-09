#ifndef __TARRAY_HPP_
#define __TARRAY_HPP_

#include "../../Platform/Types.hpp"
#include "../../Memory/LinearStackAllocator.hpp"
#include "../../Iterators/LinearStackIterator.hpp"

namespace DadEngine::Core//::Containers
{
    template<typename T, typename Alloc = LinearStackAllocator<T>>
	class TArray
	{

	public:
		TArray() = default;

		TArray (size_t _InItemCount);

		TArray (size_t _InItemCount, T _InInitValue);

		TArray (T *_InValues, size_t _InItemCount);

		~TArray() = default;


		TArray<T, Alloc> &operator= (const TArray &_InCpy);


		void Reserve (size_t _InSize);

		void AddCapacity (size_t _InSize);

		void Add (T _InNewItem);

		void Add (T *_InValues, size_t _InItemCount);

		void Resize (size_t _InItemCount);
		
		void Clear ();


		T &operator[] (uint32 _InIndex);

		uint8 IsEmpty () const;

		T *GetData () const;

		size_t Size () const;

		T &Last () const;


		// Iterator
        LinearStackIterator<T> begin () const;

		LinearStackIterator<T> end () const;


	private:

		Alloc m_allocator = Alloc();

		uint32 m_uiLastItemIndex = 0U;
	};

	//using namespace DadEngine::Core::Containers;
}

#endif //__TARRAY_HPP_