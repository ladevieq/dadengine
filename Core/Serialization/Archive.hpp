#ifndef __ARCHIVE_HPP_
#define __ARCHIVE_HPP_

#include "../Platform/Types.hpp"
#include "../Types/Collection/TArray.hpp"


namespace DadEngine::Core
{
    // Try to remove the useless vtable generation

    class Archive
    {

        public:
        Archive() = default;
        Archive(TArray<uint8> &_InData, b8 _InReading);

        TArray<uint8> &GetData();

        virtual void Serialize(void *_InValue, int32 _InSize) = 0;


        private:
        template <typename T>
        friend Archive &operator<<(Archive &_InAr, T &_InValue)
        {
            _InAr.Serialize(&_InValue, sizeof(_InValue));

            return _InAr;
        }

        template <typename T>
        friend Archive &operator<<(Archive &_InAr, TArray<T> &_InValue)
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
        b8 m_bIsReading : 1;
    };

    namespace Test
    {
        void TestSerialization();
    }
} // namespace DadEngine::Core

#endif //__ARCHIVE_HPP_