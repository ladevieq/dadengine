#ifndef __WINDOWS_WINDOW_HPP_
#define __WINDOWS_WINDOW_HPP_

#include <Windows.h>

#include "WindowsTypes.hpp"

namespace DadEngine::Core
{
	LRESULT __stdcall WindowProcedure(HWND _InHWND, uint32 _InMsg, WPARAM _InWParam, LPARAM _InLParam);

	class WindowsWindow
	{
	public:

		WindowsWindow (const char *_InsWindowName, uint32 _InWidth, uint32 _InHeight, uint8 _InFullscreen, uint8 _InVeticalSync);

		~WindowsWindow() = default;


		void MessagePump ();

		void HandleMessages(HWND _InHWND, uint32 _InMsg, WPARAM _InWParam, LPARAM _InLParam);
		
		// Move to application
        void ToggleConsole ();

		void SetWindowTitle (const char *_InWindowName);

		/*void OnSize(HWND _InHWND, uint32 _InWidth, uint32 _InHeight)
		{
			RECT rect = {};
			GetClientRect(_InHWND, &rect);

			rect.left = _InWidth;
			rect.bottom = _InHeight;

			AdjustWindowRectEx(&rect, m_dwStyle, FALSE, m_dwExStyle);
		}*/

		HINSTANCE GetWindowHInstance() const { return m_hInstance; }

		HWND GetWindowHandle() const { return m_windowHandle; }

		uint8 GetFullscreen() { return m_uiFullscreen; }

		uint8 GetVerticalSync() { return m_uiVerticalSync; }

		RECT& GetRect() { return m_windowRect; }

		const char* const GetWindowName() { return m_sWindowName; }

		int16 KeyState(int32 _InKeyCode) { return GetAsyncKeyState(_InKeyCode); }


	private:

		void CreateWindowClass ();

		void CreateWindowsWindow (uint8 _InFullscreen, uint32 _InWidth, uint32 _InHeight);


		uint8 m_uiConsoleEnabled = FALSE;
		uint8 m_uiFullscreen = FALSE;
		uint8 m_uiVerticalSync = FALSE;
		DWORD m_dwExStyle;
		DWORD m_dwStyle;
		WNDCLASSEX m_wndClass = {};
		HWND m_windowHandle = nullptr;
		HINSTANCE m_hInstance = nullptr;
		RECT m_windowRect = {};
		
		const char* m_sClassName = "DadEngine Window Name\0";
		const char* m_sWindowName;
	};
}

using PlatformWindow = DadEngine::Core::WindowsWindow;

#endif //__WINDOWS_WINDOW_HPP_
