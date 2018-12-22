#include "tdictionary.hpp"


namespace DadEngine::Core
{
    namespace Test
    {
        void TestDictionary()
        {
            TDictionary<uint32_t, char> testDic;

            testDic.Add(Pair<uint32_t, char>{ 3U, 'C' });

            ASSERT(testDic.Size() == 1U);
            ASSERT(testDic.Contains(3U).k == TRUE);
        }
    } // namespace Test
}