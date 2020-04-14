#include "windows-window.hpp"

#include <cassert>
#include <cstdio>

#include <utility>
#include <windowsx.h>

namespace DadEngine
{
    Window::Window(std::string &&_windowName, int32_t _width, int32_t _height, bool _fullscreen, bool _veticalSync)
        : m_fullscreen(_fullscreen), m_verticalSync(_veticalSync),
          m_hInstance(GetModuleHandle(nullptr)), m_windowName(_windowName)
    {
        createWindowClass();
        createWindow(m_fullscreen, _width, _height);

        m_isOpen = true;
    }

    void Window::MessagePump()
    {
        MSG msg = {};

        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    LRESULT Window::HandleMessages(HWND _hwnd, uint32_t _msg, WPARAM _wParam, LPARAM _lParam)
    {
        auto *window = reinterpret_cast<Window *>(GetWindowLongPtr(_hwnd, GWLP_USERDATA));

        switch (_msg) {
        case WM_CREATE:
        {
            auto *createStruct = reinterpret_cast<CREATESTRUCT *>(_lParam);
            auto *window = reinterpret_cast<Window *>(createStruct->lpCreateParams);
            SetWindowLongPtr(_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
            break;
        }
        case WM_SIZE:
        {
            break;
        }

        case WM_PAINT:
            break;

        case WM_CLOSE:
        {
            window->Close();
            break;
        }

        case WM_QUIT:
        {
            window->Close();
            break;
        }

        case WM_DESTROY:
        {
            window->Close();
            break;
        }

        case WM_KEYDOWN:
        {
            break;
        }

        case WM_KEYUP:
        {
            break;
        }

        case WM_LBUTTONDOWN:
        {
            break;
        }

        case WM_LBUTTONUP:
        {
            break;
        }

        case WM_RBUTTONDOWN:
        {
            break;
        }

        case WM_RBUTTONUP:
        {
            break;
        }

        case WM_MBUTTONDOWN:
        {
            break;
        }

        case WM_MBUTTONUP:
        {
            break;
        }

        case WM_MOUSEMOVE:
        {
            break;
        }

        case WM_MOUSEWHEEL:
        {
            break;
        }
        default:
        {
            return DefWindowProc(_hwnd, _msg, _wParam, _lParam);
        }
        }
        return 0;
    }

    void Window::SetWindowTitle(std::string &&_windowName)
    {
        m_windowName = _windowName;
        SetWindowText(m_windowHandle, m_windowName.c_str());
    }

    void Window::Close()
    {
        m_isOpen = false;
    }

    void Window::createWindowClass()
    {
        m_wndClass.cbSize        = sizeof(m_wndClass);
        m_wndClass.hInstance     = m_hInstance;
        m_wndClass.lpfnWndProc   = Window::HandleMessages;
        m_wndClass.lpszClassName = m_className.c_str();
        m_wndClass.hIcon         = LoadIcon(nullptr, IDI_APPLICATION);

        assert(RegisterClassEx(&m_wndClass));
    }

    void Window::createWindow(bool _fullscreen, int32_t _width, int32_t _height)
    {
        if (_fullscreen) {
            m_dwExStyle = WS_EX_APPWINDOW;
            m_dwStyle   = WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

            m_windowRect.right  = GetSystemMetrics(SM_CXSCREEN);
            m_windowRect.bottom = GetSystemMetrics(SM_CYSCREEN);
        }
        else {
            m_dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
            m_dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

            m_windowRect.right  = _width;
            m_windowRect.bottom = _height;
        }

        m_windowHandle = CreateWindowEx(m_dwExStyle, m_className.c_str(),
                                        m_windowName.c_str(), m_dwStyle,
                                        m_windowRect.left, m_windowRect.top,
                                        m_windowRect.right, m_windowRect.bottom,
                                        nullptr, nullptr, m_hInstance, this);

        assert(m_windowHandle != nullptr);

        ShowWindow(m_windowHandle, SW_SHOW);
        SetForegroundWindow(m_windowHandle);
        SetFocus(m_windowHandle);
    }
} // namespace DadEngine
