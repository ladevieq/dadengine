#ifndef __TDICTIONARY_HPP_
#define __TDICTIONARY_HPP_


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


		FORCE_INLINE Pair<uint8, Value> Contains(Key _InKeyVal)
		{
			for (size_t i = 0U; i < m_Values.Size(); i++)
			{
				if (m_Values[(uint32)i].k == _InKeyVal)
				{
					return Pair<uint8, Value> { TRUE, m_Values[(uint32)i].v };
				}
			}

			return Pair<uint8, Value> { FALSE };
		}

		FORCE_INLINE void Add(P _InNewItem)
		{
			Pair<uint8, Value> pair = Contains(_InNewItem.k);

			if (pair.k == FALSE)
			{
				m_Values.Add(_InNewItem);
			}

			else
			{
				pair.v = _InNewItem.v;
			}
		}

		FORCE_INLINE P& operator[] (const Key& _InSeekedkey)
		{
			P seekedPair = { _InSeekedkey };

			if (P mathingPair = (Contains(seekedPair).k == TRUE))
			{
				mathingPair.k = m_Values[i].k;

				return mathingPair;
			}

			LOG_ASSERT(0, "Key doesn't exist");

			return P{};
		}

		FORCE_INLINE size_t Size () const
		{
			return m_Values.Size();
		}

		TArray<P> m_Values;
	};

	namespace Test
	{
		FORCE_INLINE void TestDictionary()
		{
			TDictionary<uint32, char> testDic;

			testDic.Add(Pair<uint32, char>{3U, 'C'});

			ASSERT(testDic.Size() == 1U);
			ASSERT(testDic.Contains(3U).k == TRUE);
		}
	}
}

#endif //__TDICTIONARY_HPP_