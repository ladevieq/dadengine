#ifndef __WINDOWS_TEXT_FILE_IO_HPP_
#define __WINDOWS_TEXT_FILE_IO_HPP_

#include <Windows.h>

namespace DadEngine::Core
{
	// Use windows IO stuff ?

	struct WindowsTextFile : public IFile
	{
		WindowsTextFile(const char* _InFilePath, IOModeFlag _InIOMode)
		{
			switch (_InIOMode)
			{
			case IO_MODE_READ:
				LOG_ASSERT(OpenRead(_InFilePath) != FALSE, "File doesn't exist !");
				break;
			case IO_MODE_WRITE:
				LOG_ASSERT(OpenWrite(_InFilePath) != FALSE, "File doesn't exist !");
				break;
			case IO_MODE_WRITE | IO_MODE_READ:
				m_fileHandle = fopen(_InFilePath, "r+");
				break;
			case IO_MODE_APPEND:
				m_fileHandle = fopen(_InFilePath, "a");
				break;
			}
		}
		
		~WindowsTextFile()
		{
			fclose(m_fileHandle);
		}


		b8 OpenRead(const char* _InFilePath) override final
		{
			m_fileHandle = fopen(_InFilePath, "rt");

			return m_fileHandle != nullptr;
		}

		b8 Read(uint8* _InDst, size_t _InBytesToRead) override final
		{
			size_t size = fread(_InDst, 1U, _InBytesToRead, m_fileHandle);
			return size == _InBytesToRead;
		}

		b8 Read(String& _InDst) override final
		{
			size_t size = fread((void*)_InDst.Cstr(), sizeof(uint8), _InDst.Size(), m_fileHandle);
			return size == _InDst.Size();
		}
		

		b8 OpenWrite(const char* _InFilePath) override final
		{
			m_fileHandle = fopen(_InFilePath, "wt");

			return m_fileHandle != nullptr;
		}

		b8 Write(uint8* _InSrc, size_t _InBytesToWrite) override final
		{
			size_t size = fwrite(_InSrc, 1U, _InBytesToWrite, m_fileHandle);
			return size == _InBytesToWrite;
		}

		b8 Write(String& _InDst) override final
		{
			size_t size = fread((void*)_InDst.Cstr(), 1U, _InDst.Size(), m_fileHandle);
			return size == _InDst.Size();
		}

		void Close() override final
		{
			fclose(m_fileHandle);
		}

		size_t Size() override final
		{
			int64 pos;
			size_t size = 0U;
			fgetpos(m_fileHandle, &pos);
			fseek(m_fileHandle, 0, SEEK_END);

			size = (size_t) ftell(m_fileHandle);

			fseek(m_fileHandle, (int32)pos, SEEK_SET);

			return size;
		}

		FILE* m_fileHandle = nullptr;
	};

	using PlatformTextFile = WindowsTextFile;
}

#endif //!__WINDOWS_TEXT_FILE_IO_HPP_