#ifndef __WINDOWS_WINDOW_HPP_
#define __WINDOWS_WINDOW_HPP_

#include <Windows.h>
#include <stdio.h>

#include "../../Defines.hpp"
#include "../../PlatformTypes.hpp"

namespace DadEngine::Core
{
	LRESULT __stdcall WindowProcedure(HWND _InHWND, uint32 _InMsg, WPARAM _InWParam, LPARAM _InLParam);

	class WindowsWindow
	{
	public:

		WindowsWindow(const char* _InsWindowName, uint32 _InWidth, uint32 _InHeight, uint8 _InFullscreen, uint8 _InVeticalSync)
			: m_sWindowName(_InsWindowName),
			m_hInstance(GetModuleHandle(NULL)),
			m_uiFullscreen(_InFullscreen),
			m_uiVerticalSync(_InVeticalSync)
		{
			CreateWindowClass();
			CreateWindowsWindow(m_uiFullscreen, _InWidth, _InHeight);
		}


		~WindowsWindow() = default;


		FORCE_INLINE void MessagePump()
		{
			MSG msg = {};

			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		void HandleMessages(HWND _InHWND, uint32 _InMsg, WPARAM _InWParam, LPARAM _InLParam);
		
		// Move to application
		FORCE_INLINE void ToggleConsole()
		{
			if (m_uiConsoleEnabled == FALSE)
			{
				AllocConsole();
				AttachConsole(GetCurrentProcessId());
				freopen("CONOUT$", "w", stdout);
				SetConsoleTitle("Debug Window");
			}
			
			else
			{
				FreeConsole();
			}

			m_uiConsoleEnabled = !m_uiConsoleEnabled;
		}

		FORCE_INLINE void SetWindowTitle(const char* _InWindowName) { SetWindowText(m_windowHandle, _InWindowName); }

		/*void OnSize(HWND _InHWND, uint32 _InWidth, uint32 _InHeight)
		{
			RECT rect = {};
			GetClientRect(_InHWND, &rect);

			rect.left = _InWidth;
			rect.bottom = _InHeight;

			AdjustWindowRectEx(&rect, m_dwStyle, FALSE, m_dwExStyle);
		}*/

		FORCE_INLINE HINSTANCE GetWindowHInstance() const { return m_hInstance; }

		FORCE_INLINE HWND GetWindowHandle() const { return m_windowHandle; }

		FORCE_INLINE uint8 GetFullscreen() { return m_uiFullscreen; }

		FORCE_INLINE uint8 GetVerticalSync() { return m_uiVerticalSync; }

		FORCE_INLINE RECT& GetRect() { return m_windowRect; }

		FORCE_INLINE const char* const GetWindowName() { return m_sWindowName; }

		FORCE_INLINE int16 KeyState(int32 _InKeyCode) { return GetAsyncKeyState(_InKeyCode); }


	private:

		void CreateWindowClass()
		{
			m_wndClass.cbSize = sizeof(m_wndClass);
			m_wndClass.hInstance = m_hInstance;
			m_wndClass.lpfnWndProc = WindowProcedure;
			m_wndClass.lpszClassName = m_sClassName;
			m_wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);

			ASSERT(RegisterClassEx(&m_wndClass));
		}

		void CreateWindowsWindow(uint8 _InFullscreen, uint32 _InWidth, uint32 _InHeight)
		{
			if (_InFullscreen == TRUE)
			{
				m_dwExStyle = WS_EX_APPWINDOW;
				m_dwStyle = WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
			}

			else
			{
				m_dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
				m_dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
			}

			uint32 screenWidth = GetSystemMetrics(SM_CXSCREEN);
			uint32 screenHeight = GetSystemMetrics(SM_CYSCREEN);

			m_windowRect = { 0, 0, 0, 0 };

			if (_InFullscreen == TRUE)
			{
				m_windowRect.right = screenWidth;
				m_windowRect.bottom = screenHeight;
			}

			else
			{
				m_windowRect.right = _InWidth;
				m_windowRect.bottom = _InHeight;
			}

			m_windowHandle = CreateWindowEx(m_dwExStyle, m_sClassName, m_sWindowName, m_dwStyle, m_windowRect.left, m_windowRect.top, m_windowRect.right, m_windowRect.bottom, NULL, NULL, m_hInstance, 0);

			ASSERT(m_windowHandle);

			ShowWindow(m_windowHandle, SW_SHOW);
			SetForegroundWindow(m_windowHandle);
			SetFocus(m_windowHandle);
		}


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
