#ifndef __IFILE_HPP_
#define __IFILE_HPP_

#include "Platform/Types.hpp"
#include "Types/String.hpp"


namespace DadEngine::Core
{
	enum IOMode : uint8
	{
		IO_MODE_READ = 0x1,
		IO_MODE_WRITE = 0x2,
		IO_MODE_APPEND = 0x4,
		IO_MODE_TEXT = 0x8,
		IO_MODE_BINARY = 0xf,
		MAX_IO_MODE = 0xff
	};

	using IOModeFlag = uint8;

	struct IFile
	{
		virtual b8 OpenRead(const char* _InFilePath) = 0;
		virtual b8 Read(uint8* _InDst, size_t _InBytesToRead) = 0;
		virtual b8 Read(String& _InDst) = 0;

		virtual b8 OpenWrite(const char* _InFilePath) = 0;
		virtual b8 Write(uint8* _InSrc, size_t _InBytesToWrite) = 0;
		virtual b8 Write(String& _InDst) = 0;

		virtual void Close() = 0;

		virtual size_t Size() = 0;
	};
}

#endif //__IFILE_HPP_