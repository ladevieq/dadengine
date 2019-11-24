#ifndef __STRING_HPP_
#define __STRING_HPP_

#include <cstdint>

#include "collection/tarray.hpp"


namespace DadEngine
{
    class String
    {
        public:
        String(const char *_InContent);

        String(size_t _InSize);

        ~String() = default;

        String &operator=(String &&_InSrc) = default;

        void operator=(char *&_InSrc);

        // void operator= (char*&& _InSrc);


        void Append(String &_InNewString);

        void Append(const char *_InNewCString);

        const char *Cstr() const;

        size_t Size();


        private:
        TArray<char> m_string;
    };
} // namespace DadEngine

#endif //__STRING_HPP_

