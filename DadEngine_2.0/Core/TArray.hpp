#ifndef __TARRAY_HPP_
#define __TARRAY_HPP_


namespace DadEngine::Core//::Containers
{
	template<typename T, typename Alloc = LinearStackAllocator<T>>
	class TArray
	{

	public:

		TArray() {}// = default;

		TArray(size_t _InItemCount)
		{
			m_allocator.Allocate(_InItemCount);
		}

		~TArray() = default;


		TArray& operator= (const TArray& _InCpy)
		{
			m_allocator = _InCpy.m_allocator;
			m_uiLastItemIndex = _InCpy.m_uiLastItemIndex;
			
			return *this;
		}


		FORCE_INLINE void Reserve(size_t _InSize)
		{
			m_allocator.Allocate(_InSize);
		}

		FORCE_INLINE void AddCapacity(size_t _InSize)
		{
			Resize(m_allocator.m_uiCapacity + _InSize);
		}

		FORCE_INLINE void Add(T _InNewItem)
		{
			if (m_uiLastItemIndex >= m_allocator.m_uiCapacity)
				Resize(m_allocator.m_uiCapacity + 1U);

			m_allocator.m_ptrMemLocation[m_uiLastItemIndex] = _InNewItem;
			m_uiLastItemIndex++;
		}

		FORCE_INLINE void Resize(size_t _InItemCount)
		{
			m_allocator.Resize(_InItemCount);
		}


		FORCE_INLINE T& operator [] (uint32 _InIndex)
		{
			return m_allocator.m_ptrMemLocation[_InIndex];
		}

		FORCE_INLINE uint8 IsEmpty() const { return m_uiLastItemIndex == 0 ? TRUE : FALSE; }

		FORCE_INLINE T* GetData() const
		{
			return m_allocator.m_ptrMemLocation;
		}

		FORCE_INLINE uint32 Size() const
		{
			return m_allocator.m_uiCapacity;
		}


		// Iterator
		FORCE_INLINE LinearStackIterator<T> begin() const { return LinearStackIterator<T>(m_allocator.m_ptrMemLocation, m_allocator.m_uiCapacity); }

		FORCE_INLINE LinearStackIterator<T> end() const { return LinearStackIterator<T>(m_allocator.m_ptrMemLocation + m_allocator.m_uiCapacity, 0U); }


	private:

		Alloc m_allocator = Alloc();

		uint32 m_uiLastItemIndex = 0U;
	};

	namespace Test
	{
		FORCE_INLINE void TestTArray()
		{
			TArray<int32> eray;
			TArray<int32> bray;

			eray.Add(10);
			eray.Add(20);
			eray.Add(30);

			printf("%d\n", eray[0]);
			printf("%d\n", eray[1]);
			printf("%d\n", eray[2]);

			bray = eray;

			for(int32 i : eray)
			{
				printf("%d\n", i);
			}

			/*printf("%d\n", bray[0]);
			printf("%d\n", bray[1]);
			printf("%d\n", bray[2]);*/

			//ASSERT(eray.IsEmpty() == TRUE);

			eray.Resize(100U);

			ASSERT(eray.Size() == 100U);

			eray.Resize(10U);
			
			ASSERT(eray.Size() == 10U);

			eray.Add(10);

			ASSERT(eray.IsEmpty() == FALSE);
		}
	}

	//using namespace DadEngine::Core::Containers;
}

#endif //__TARRAY_HPP_