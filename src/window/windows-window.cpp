#include "windows-window.hpp"

#include <windowsx.h>

#include "debug.hpp"
// #include "../../../gameplay/input-manager.hpp"

namespace DadEngine
{
    LRESULT WindowProcedure(HWND _hwnd, uint32_t _msg, WPARAM _wParam, LPARAM _lParam)
    {
        Application::GetApp()->m_window.HandleMessages(_hwnd, _msg, _wParam, _lParam);

        // return DefWindowProc(_hwnd, _msg, _wParam, _lParam);
    }

    Window::Window(const char *_windowName, int32_t _width, int32_t _height, bool _fullscreen, bool _veticalSync)
        : m_fullscreen(_fullscreen), m_verticalSync(_veticalSync),
          m_hInstance(GetModuleHandle(nullptr)), m_windowName(_windowName)
    {
        createWindowClass();
        createWindowsWindow(m_fullscreen, _width, _height);

        m_isOpen = true;
    }


    void Window::MessagePump()
    {
        MSG msg = {};

        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    void Window::HandleMessages(HWND _hwnd, uint32_t _msg, WPARAM _wParam, LPARAM _lParam)
    {
        switch (_msg)
        {
        case WM_SIZE:
        {
            // uint32_t uiWidth = LOWORD(_InLParam);
            // uint32_t uiHeight = HIWORD(_InLParam);

            // OnSize(_InHWND, uiWidth, uiHeight);
            // GetClientRect(_InHWND, );

            break;
        }

        case WM_PAINT:
            break;

        case WM_CLOSE:
        {
            // EventManager.emitEvent()
            DestroyWindow(_hwnd);
            break;
        }

        case WM_QUIT:
        {
            PostQuitMessage(0);
            break;
        }

        case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }

        case WM_KEYDOWN:
        {
            // printf("%d\n", MapVirtualKey((UINT)_InWParam, MAPVK_VK_TO_CHAR));

            // Gameplay::InputManager::GetInputManager ()->UpdateKeyState (
            // (Gameplay::KeyCode)MapVirtualKey ((UINT)_InWParam, MAPVK_VK_TO_CHAR), Gameplay::KEY_STATE_KEY_PRESSED);

            break;
        }

        case WM_KEYUP:
        {
            /*Gameplay::InputManager::GetInputManager ()->UpdateKeyState (
            (Gameplay::KeyCode)MapVirtualKey ((UINT)_InWParam, MAPVK_VK_TO_CHAR), Gameplay::KEY_STATE_KEY_RELEASED);*/

            break;
        }

        case WM_LBUTTONDOWN:
        {
            /*Gameplay::InputManager::GetInputManager ()->UpdateButtonState (Gameplay::BUTTON_LEFT_BUTTON,
                                                                           Gameplay::BUTTON_STATE_BUTTON_DOWN);*/
            break;
        }

        case WM_LBUTTONUP:
        {
            /*Gameplay::InputManager::GetInputManager ()->UpdateButtonState (Gameplay::BUTTON_LEFT_BUTTON,
                                                                           Gameplay::BUTTON_STATE_BUTTON_UP);*/
            break;
        }

        case WM_RBUTTONDOWN:
        {
            /*Gameplay::InputManager::GetInputManager ()->UpdateButtonState (Gameplay::BUTTON_RIGHT_BUTTON,
                                                                           Gameplay::BUTTON_STATE_BUTTON_DOWN);*/
            break;
        }

        case WM_RBUTTONUP:
        {
            /*Gameplay::InputManager::GetInputManager ()->UpdateButtonState (Gameplay::BUTTON_RIGHT_BUTTON,
                                                                           Gameplay::BUTTON_STATE_BUTTON_UP);*/
            break;
        }

        case WM_MBUTTONDOWN:
        {
            /*Gameplay::InputManager::GetInputManager ()->UpdateButtonState (Gameplay::BUTTON_MIDDLE_BUTTON,
                                                                           Gameplay::BUTTON_STATE_BUTTON_DOWN); */
            break;
        }

        case WM_MBUTTONUP:
        {
            /*Gameplay::InputManager::GetInputManager ()->UpdateButtonState (Gameplay::BUTTON_MIDDLE_BUTTON,
                                                                           Gameplay::BUTTON_STATE_BUTTON_UP);*/
            break;
        }

        case WM_MOUSEMOVE:
        {
            /*Gameplay::InputManager::GetInputManager ()->UpdateMousePosition
               (GET_X_LPARAM (_InLParam), GET_Y_LPARAM (_InLParam));*/
            break;
        }

        case WM_MOUSEWHEEL:
        {
            // Gameplay::InputManager::GetInputManager ()->UpdateWheelDelta (GET_WHEEL_DELTA_WPARAM (_InWParam));
            break;
        }
        }
    }

    void Window::Close()
    {
        exit(0);
    }

    void Window::SetWindowTitle(const char *_windowName)
    {
        m_windowName = _windowName;
        SetWindowText(m_windowHandle, m_windowName);
    }


    void Window::createWindowClass()
    {
        m_wndClass.cbSize = sizeof(m_wndClass);
        m_wndClass.hInstance = m_hInstance;
        m_wndClass.lpfnWndProc = WindowProcedure;
        m_wndClass.lpszClassName = m_className;
        m_wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);

        Assert(RegisterClassEx(&m_wndClass));
    }

    void Window::createWindowsWindow(bool _fullscreen, int32_t _width, int32_t _height)
    {
        if (_fullscreen == true)
        {
            m_dwExStyle = WS_EX_APPWINDOW;
            m_dwStyle = WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

            m_windowRect.right = GetSystemMetrics(SM_CXSCREEN);
            m_windowRect.bottom = GetSystemMetrics(SM_CYSCREEN);
        }
        else
        {
            m_dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
            m_dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

            m_windowRect.right = _width;
            m_windowRect.bottom = _height;
        }

        m_windowHandle = CreateWindowEx(m_dwExStyle, m_className, m_windowName, m_dwStyle,
                                        m_windowRect.left, m_windowRect.top,
                                        m_windowRect.right, m_windowRect.bottom,
                                        nullptr, nullptr, m_hInstance, nullptr);

        LogAssert(m_windowHandle != nullptr, "Failed to create window !", __FILE__, __LINE__);

        ShowWindow(m_windowHandle, SW_SHOW);
        SetForegroundWindow(m_windowHandle);
        SetFocus(m_windowHandle);
    }
} // namespace DadEngine
