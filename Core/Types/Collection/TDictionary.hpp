#ifndef __TDICTIONARY_HPP_
#define __TDICTIONARY_HPP_

#include "../../Platform/Types.hpp"
#include "TArray.hpp"


namespace DadEngine::Core //::Containers
{
    template <typename Key, typename Value>
    struct Pair
    {
        Key k;
        Value v;
    };

    template <typename Key, typename Value>
    class TDictionary
    {
        public:
        using P = Pair<Key, Value>;


        Pair<uint8, Value> Contains(Key _InKeyVal)
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

        void Add(P _InNewItem)
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

        Pair<Key, Value>& operator[](const Key &_InSeekedkey)
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

        size_t Size() const
        {
            return this->m_Values.Size();
        }


        TArray<P> m_Values;
    };

    namespace Test
    {
        void TestDictionary();
    } // namespace Test
} // namespace DadEngine::Core

#endif //__TDICTIONARY_HPP_