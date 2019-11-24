#include "archive.hpp"

namespace DadEngine
{
    Archive::Archive(TArray<uint8_t> &_InData, uint8_t _InReading)
        : m_Data(_InData)
    {
    }

    TArray<uint8_t> &Archive::GetData()
    {
        return m_Data;
    }

    namespace Test
    {
        struct TestStructSerialization
        {
            float a;
            bool b;

            TArray<float> floats;
        };

        /*SERIALIZATION_CLASS_BEGIN(TestStructSerialization);
        SERIALIZATION_CLASS_PROPERTY(TestStructSerialization::a);
        SERIALIZATION_CLASS_PROPERTY(TestStructSerialization::b);
        SERIALIZATION_CLASS_PROPERTY(TestStructSerialization::floats);
        SERIALIZATION_CLASS_END(TestStructSerialization);*/

        void TestSerialization()
        {
            /*Archive ar;
            MemoryWriter memWriter;
            TestStructSerialization a = { 3.f, TRUE };
            TestStructSerialization b = {};

            a.a = 3.f;
            a.b = TRUE;
            a.floats.Add(1.f);
            a.floats.Add(2.f);
            a.floats.Add(31.f);

            ar << a;

            memWriter << a;

            MemoryReader memReader(memWriter.GetData());

            memReader << b;

            printf("%f\n", b.floats[0]);
            printf("%f\n", b.floats[1]);
            printf("%f\n", b.floats[2]);*/
        }
    } // namespace Test
} // namespace DadEngine

