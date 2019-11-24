#ifndef __TDICTIONARY_HPP_
#define __TDICTIONARY_HPP_

#include <cstdint>
#include <list>
#include <utility>
#include <vector>

// #include "tarray.hpp"


namespace DadEngine
{
    template <typename Key, typename Value, const uint32_t PoolSize = 1024U>
    class TDictionary
    {
        public:
        using P = std::pair<Key, Value>;

        TDictionary() = default;

        /**
         * Find an element inside the map using it's key
         */
        bool Insert(P _InNewPair)
        {
            if (this[_InNewPair.first].first == false)
            {
                const auto hashedKey = this->m_hashFunction(_InNewPair.first) % PoolSize;

                this->m_HashMap[hashedKey].insert(_InNewPair);

                return true;
            }

            return false;
        }

        /**
         * Find an element inside the map using it's key
         */
        std::pair<Key, Value> &operator[](const Key &_InSeekedKey)
        {
            const auto hashedKey = this->m_hashFunction(_InSeekedKey) % PoolSize;
            const auto matchedList = this->m_HashMap[hashedKey];
            v

                for (const auto &currentPair : matchedList)
            {
                if (_InSeekedKey == _InSeekedPair.first)
                {
                    return std::make_pair(true, currentPair);
                }
            }

            return std::make_pair(true, P());
        }

        auto Data()
        {
            return this->m_HashMap;
        }


        private:
        std::hash<Key> m_hashFunction = std::hash<Key>();
        std::vector<std::list<P>> m_HashMap = std::vector<std::list<P>>(PoolSize);
    };
} // namespace DadEngine

#endif //__TDICTIONARY_HPP_
