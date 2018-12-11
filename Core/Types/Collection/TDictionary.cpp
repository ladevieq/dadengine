#include "TDictionary.hpp"

namespace DadEngine::Core
{
    namespace Test
    {
        void TestDictionary()
        {
            TDictionary<uint32, char> testDic;

            testDic.Add(Pair<uint32, char>{3U, 'C'});

            ASSERT(testDic.Size() == 1U);
            ASSERT(testDic.Contains(3U).k == TRUE);
        }
    } // namespace Test
}