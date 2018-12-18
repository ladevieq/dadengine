#ifndef __ALLOCATOR_HPP_
#define __ALLOCATOR_HPP_


namespace DadEngine::Core//::Memory
{
	template<typename T>
	struct Allocator
	{
		Allocator() = default;

		/*virtual void Allocate(size_t _InItemCout) = 0;

		virtual void Deallocate() = 0;

		virtual void Resize(size_t _InItemCout) = 0;*/

		void Allocate(size_t _InItemCout);

		void Deallocate();

		void Resize(size_t _InItemCout);


		T* m_ptrMemLocation = nullptr;
		size_t m_ItemSize = sizeof(T);
		size_t m_uiCapacity = 0U;
	};
}

#endif //__ALLOCATOR_HPP_