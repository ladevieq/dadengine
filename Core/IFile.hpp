#ifndef __IFILE_HPP_
#define __IFILE_HPP_

#include <stdint.h>

// #include "Types/String.hpp"


namespace DadEngine::Core
{
	class String;

	enum IOMode : uint8_t
	{
		IO_MODE_READ = 0x1,
		IO_MODE_WRITE = 0x2,
		IO_MODE_APPEND = 0x4,
		IO_MODE_TEXT = 0x8,
		IO_MODE_BINARY = 0xf,
		MAX_IO_MODE = 0xff
	};

	using IOModeFlag = uint8_t;

	struct IFile
	{
		virtual uint8_t OpenRead(const char* _InFilePath) = 0;
		virtual uint8_t Read(uint8_t* _InDst, size_t _InBytesToRead) = 0;
		virtual uint8_t Read(String& _InDst) = 0;

		virtual uint8_t OpenWrite(const char* _InFilePath) = 0;
		virtual uint8_t Write(uint8_t* _InSrc, size_t _InBytesToWrite) = 0;
		virtual uint8_t Write(String& _InDst) = 0;

		virtual void Close() = 0;

		virtual size_t Size() = 0;
	};
}

#endif //__IFILE_HPP_