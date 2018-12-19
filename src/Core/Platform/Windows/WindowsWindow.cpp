#include "WindowsWindow.hpp"

#include <Windowsx.h>

#include "../../Defines.hpp"
#include "../../../Gameplay/InputManager.hpp"

namespace DadEngine::Core
{
	LRESULT WindowProcedure(HWND _InHWND, uint32_t _InMsg, WPARAM _InWParam, LPARAM _InLParam)
	{
		Application::GetApp()->m_window.HandleMessages(_InHWND, _InMsg, _InWParam, _InLParam);

		return DefWindowProc(_InHWND, _InMsg, _InWParam, _InLParam);
	}
	
	WindowsWindow::WindowsWindow(const char *_InsWindowName, uint32_t _InWidth, uint32_t _InHeight, uint8_t _InFullscreen, uint8_t _InVeticalSync)
        : m_sWindowName (_InsWindowName), m_hInstance (GetModuleHandle (NULL)),
          m_uiFullscreen (_InFullscreen), m_uiVerticalSync (_InVeticalSync)
    {
        CreateWindowClass ();
        CreateWindowsWindow (m_uiFullscreen, _InWidth, _InHeight);
    }


    void WindowsWindow::MessagePump ()
    {
        MSG msg = {};

        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage (&msg);
            DispatchMessage (&msg);
        }
    }

    void WindowsWindow::HandleMessages (HWND _InHWND, uint32_t _InMsg, WPARAM _InWParam, LPARAM _InLParam)
    {
        switch (_InMsg)
        {
        case WM_SIZE:
        {
            // uint32 uiWidth = LOWORD(_InLParam);
            // uint32 uiHeight = HIWORD(_InLParam);

            // OnSize(_InHWND, uiWidth, uiHeight);
            // GetClientRect(_InHWND, );

            break;
        }

        case WM_PAINT:
            break;

        case WM_CLOSE:
        {
            DestroyWindow (_InHWND);
            break;
        }

        case WM_QUIT:
        {
            PostQuitMessage (0);
            break;
        }

        case WM_DESTROY:
        {
            PostQuitMessage (0);
            break;
        }

        case WM_KEYDOWN:
        {
            // printf("%d\n", MapVirtualKey((UINT)_InWParam, MAPVK_VK_TO_CHAR));

            Gameplay::InputManager::GetInputManager ()->UpdateKeyState (
            (Gameplay::KeyCode)MapVirtualKey ((UINT)_InWParam, MAPVK_VK_TO_CHAR), Gameplay::KEY_STATE_KEY_PRESSED);

            break;
        }

        case WM_KEYUP:
        {
            Gameplay::InputManager::GetInputManager ()->UpdateKeyState (
            (Gameplay::KeyCode)MapVirtualKey ((UINT)_InWParam, MAPVK_VK_TO_CHAR), Gameplay::KEY_STATE_KEY_RELEASED);

            break;
        }

        case WM_LBUTTONDOWN:
        {
            Gameplay::InputManager::GetInputManager ()->UpdateButtonState (Gameplay::BUTTON_LEFT_BUTTON,
                                                                           Gameplay::BUTTON_STATE_BUTTON_DOWN);
            break;
        }

        case WM_LBUTTONUP:
        {
            Gameplay::InputManager::GetInputManager ()->UpdateButtonState (Gameplay::BUTTON_LEFT_BUTTON,
                                                                           Gameplay::BUTTON_STATE_BUTTON_UP);
            break;
        }

        case WM_RBUTTONDOWN:
        {
            Gameplay::InputManager::GetInputManager ()->UpdateButtonState (Gameplay::BUTTON_RIGHT_BUTTON,
                                                                           Gameplay::BUTTON_STATE_BUTTON_DOWN);
            break;
        }

        case WM_RBUTTONUP:
        {
            Gameplay::InputManager::GetInputManager ()->UpdateButtonState (Gameplay::BUTTON_RIGHT_BUTTON,
                                                                           Gameplay::BUTTON_STATE_BUTTON_UP);
            break;
        }

        case WM_MBUTTONDOWN:
        {
            Gameplay::InputManager::GetInputManager ()->UpdateButtonState (Gameplay::BUTTON_MIDDLE_BUTTON,
                                                                           Gameplay::BUTTON_STATE_BUTTON_DOWN);
            break;
        }

        case WM_MBUTTONUP:
        {
            Gameplay::InputManager::GetInputManager ()->UpdateButtonState (Gameplay::BUTTON_MIDDLE_BUTTON,
                                                                           Gameplay::BUTTON_STATE_BUTTON_UP);
            break;
        }

        case WM_MOUSEMOVE:
        {
            Gameplay::InputManager::GetInputManager ()->UpdateMousePosition (GET_X_LPARAM (_InLParam),
                                                                             GET_Y_LPARAM (_InLParam));
            break;
        }

        case WM_MOUSEWHEEL:
        {
            Gameplay::InputManager::GetInputManager ()->UpdateWheelDelta (GET_WHEEL_DELTA_WPARAM (_InWParam));
            break;
        }
        }
    }

    // Move to application
    void WindowsWindow::ToggleConsole ()
    {
        if (m_uiConsoleEnabled == FALSE)
        {
            AllocConsole ();
            AttachConsole (GetCurrentProcessId ());
            freopen ("CONOUT$", "w", stdout);
            SetConsoleTitle ("Debug Window");
        }

        else
        {
            FreeConsole ();
        }

        m_uiConsoleEnabled = !m_uiConsoleEnabled;
    }

	void WindowsWindow::SetWindowTitle (const char *_InWindowName)
    {
        SetWindowText (m_windowHandle, _InWindowName);
    }


	void WindowsWindow::CreateWindowClass ()
    {
        m_wndClass.cbSize = sizeof (m_wndClass);
        m_wndClass.hInstance = m_hInstance;
        m_wndClass.lpfnWndProc = WindowProcedure;
        m_wndClass.lpszClassName = m_sClassName;
        m_wndClass.hIcon = LoadIcon (NULL, IDI_APPLICATION);

        ASSERT (RegisterClassEx (&m_wndClass));
    }

    void WindowsWindow::CreateWindowsWindow (uint8_t _InFullscreen, uint32_t _InWidth, uint32_t _InHeight)
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

        uint32_t screenWidth = GetSystemMetrics(SM_CXSCREEN);
        uint32_t screenHeight = GetSystemMetrics(SM_CYSCREEN);

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

        m_windowHandle = CreateWindowEx (m_dwExStyle, m_sClassName, m_sWindowName, m_dwStyle,
                                         m_windowRect.left, m_windowRect.top, m_windowRect.right,
                                         m_windowRect.bottom, NULL, NULL, m_hInstance, 0);

        ASSERT (m_windowHandle);

        ShowWindow (m_windowHandle, SW_SHOW);
        SetForegroundWindow (m_windowHandle);
        SetFocus (m_windowHandle);
    }
}