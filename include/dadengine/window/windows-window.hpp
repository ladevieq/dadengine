#ifndef __WINDOWS_WINDOW_HPP_
#define __WINDOWS_WINDOW_HPP_

#include <cassert>
#include <cstdint>

#include <Windows.h>


namespace DadEngine
{
    LRESULT __stdcall WindowProcedure(HWND _hwnd, uint32_t _msg, WPARAM _wParam, LPARAM _lParam);

    class Window
    {
        public:
        Window(const char *_windowName, int32_t _width, int32_t _height, bool _fullscreen, bool _veticalSync);


        void MessagePump();

        void HandleMessages(HWND _hwnd, uint32_t _msg, WPARAM _wParam, LPARAM _lParam);

        void Close();

        void SetWindowTitle(const char *_windowName);

        /*void OnSize(HWND _InHWND, uint32 _InWidth, uint32 _InHeight)
        {
            RECT rect = {};
            GetClientRect(_InHWND, &rect);

            rect.left = _InWidth;
            rect.bottom = _InHeight;

            AdjustWindowRectEx(&rect, m_dwStyle, FALSE, m_dwExStyle);
        }*/

        HINSTANCE GetWindowHInstance() const
        {
            return m_hInstance;
        }

        HWND GetWindowHandle() const
        {
            return m_windowHandle;
        }

        bool GetFullscreen()
        {
            return m_fullscreen;
        }

        bool GetVerticalSync()
        {
            return m_verticalSync;
        }

        RECT &GetRect()
        {
            return m_windowRect;
        }

        const char *GetWindowName()
        {
            return m_windowName;
        }

        bool IsOpen()
        {
            return this->m_isOpen;
        }


        private:
        void createWindowClass();

        void createWindowsWindow(bool _fullscreen, int32_t _width, int32_t _height);


        bool m_isOpen = false;
        bool m_fullscreen = false;
        bool m_verticalSync = false;
        DWORD m_dwExStyle;
        DWORD m_dwStyle;
        WNDCLASSEX m_wndClass = {};
        HWND m_windowHandle = nullptr;
        HINSTANCE m_hInstance = nullptr;
        RECT m_windowRect = { 0, 0, 0, 0 };

        const char *m_className = "DadEngine Class Name\0";
        const char *m_windowName = "DadEngine Window Name\0";
    };
} // namespace DadEngine

#endif //__WINDOWS_WINDOW_HPP_
