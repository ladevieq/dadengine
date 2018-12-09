#ifndef __TDICTIONARY_HPP_
#define __TDICTIONARY_HPP_

#include "../../Platform/Types.hpp"
#include "TArray.hpp"


namespace DadEngine::Core//::Containers
{
	template<typename Key, typename  Value>
	struct Pair
	{
		Key k;
		Value v;
	};

	template<typename Key, typename  Value>
	class TDictionary
	{
	public:
		using P = Pair<Key, Value>;


		Pair<uint8, Value> Contains(Key _InKeyVal);


		void Add(P _InNewItem);

		P &operator[](const Key &_InSeekedkey);

		size_t Size() const;

		TArray<P> m_Values;
	};
}

#endif //__TDICTIONARY_HPP_