#include "TDictionary.hpp"

namespace DadEngine::Core
{
    template <typename Key, typename Value>
    Pair<uint8, Value> TDictionary<Key, Value>::Contains(Key _InKeyVal)
    {
        for (size_t i = 0U; i < this->m_Values.Size(); i++)
        {
            if (this->m_Values[(uint32)i].k == _InKeyVal)
            {
                return Pair<uint8, Value>{ TRUE, this->m_Values[(uint32)i].v };
            }
        }

        return Pair<uint8, Value>{ FALSE };
    }

	template <typename Key, typename Value>
    void TDictionary<Key, Value>::Add(P _InNewItem)
    {
        Pair<uint8, Value> pair = Contains(_InNewItem.k);

        if (pair.k == FALSE)
        {
            this->m_Values.Add(_InNewItem);
        }

        else
        {
            pair.v = _InNewItem.v;
        }
    }

	template <typename Key, typename Value>
    Pair<Key, Value> &TDictionary<Key, Value>::operator[](const Key &_InSeekedkey)
    {
        P seekedPair = { _InSeekedkey };

        if (P mathingPair = (Contains(seekedPair).k == TRUE))
        {
            // mathingPair.k = this->m_Values[i].k;

            return mathingPair;
        }

        LOG_ASSERT(0, "Key doesn't exist");

        return P{};
    }

	template <typename Key, typename Value>
    size_t TDictionary<Key, Value>::Size() const
    {
        return this->m_Values.Size();
    }

    namespace Test
    {
        static void TestDictionary()
        {
            TDictionary<uint32, char> testDic;

            testDic.Add(Pair<uint32, char>{3U, 'C'});

            ASSERT(testDic.Size() == 1U);
            ASSERT(testDic.Contains(3U).k == TRUE);
        }
    } // namespace Test
}