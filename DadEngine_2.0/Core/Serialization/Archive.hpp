#ifndef __ARCHIVE_HPP_
#define __ARCHIVE_HPP_


namespace DadEngine::Core
{

	// Try to remove the useless vtable generation

	class Archive
	{

	public:

		Archive() = default;
		Archive(TArray<uint8>& _InData) : m_Data(_InData) {}

		FORCE_INLINE TArray<uint8>& GetData() { return m_Data; }

		FORCE_INLINE virtual void Serialize(void* _InValue, int32 _InSize) = 0;
		

	private:

		template<typename T>
		FORCE_INLINE friend Archive& operator << (Archive& _InAr, T& _InValue)
		{
			_InAr.Serialize(&_InValue, sizeof(_InValue));

			return _InAr;
		}

		template<typename T>
		FORCE_INLINE friend Archive& operator << (Archive& _InAr, TArray<T>& _InValue)
		{
			size_t size = _InValue.Size();
			_InAr << size;

			if (_InAr.m_bIsReading == TRUE)
			{
				_InValue.Reserve(size);
			}

			for (size_t i = 0U; i < _InValue.Size(); i++)
				_InAr.Serialize(&_InValue[(uint32)i], sizeof(_InValue[(uint32)i]));

			return _InAr;
		}

	protected:

		TArray<uint8> m_Data;

		uint32 m_uiOffset = 0U;
		uint8 m_bIsReading : 1;
	};

	namespace Test
	{
		struct TestStructSerialization
		{
			float a;
			bool b;

			TArray<float> floats;
		};

		SERIALIZATION_CLASS_BEGIN(TestStructSerialization);
		SERIALIZATION_CLASS_PROPERTY(TestStructSerialization::a);
		SERIALIZATION_CLASS_PROPERTY(TestStructSerialization::b);
		SERIALIZATION_CLASS_PROPERTY(TestStructSerialization::floats);
		SERIALIZATION_CLASS_END(TestStructSerialization);

		FORCE_INLINE void TestSerialization()
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
	}
}

#endif //__ARCHIVE_HPP_