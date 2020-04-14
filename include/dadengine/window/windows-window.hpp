#ifndef __WINDOWS_WINDOW_HPP_
#define __WINDOWS_WINDOW_HPP_

#include <cassert>
#include <cstdint>
#include <string>

#include <Windows.h>


namespace DadEngine
{
    class Window
    {
        public:
        Window(std::string &&_windowName, int32_t _width, int32_t _height, bool _fullscreen, bool _veticalSync);


        void MessagePump();

        static WINAPI LRESULT HandleMessages(HWND _hwnd, uint32_t _msg, WPARAM _wParam, LPARAM _lParam);

        void SetWindowTitle(std::string &&_windowName);

        void Close();

        [[nodiscard]] HINSTANCE GetWindowHInstance() const
        {
            return m_hInstance;
        }

        [[nodiscard]] HWND GetWindowHandle() const
        {
            return m_windowHandle;
        }

        [[nodiscard]] bool GetFullscreen() const
        {
            return m_fullscreen;
        }

        [[nodiscard]] bool GetVerticalSync() const
        {
            return m_verticalSync;
        }

        RECT &GetRect()
        {
            return m_windowRect;
        }

        std::string GetWindowName()
        {
            return m_windowName;
        }

        [[nodiscard]] bool IsOpen() const
        {
            return this->m_isOpen;
        }


        private:
        void createWindowClass();

        void createWindow(bool _fullscreen, int32_t _width, int32_t _height);


        bool m_isOpen       = false;
        bool m_fullscreen   = false;
        bool m_verticalSync = false;
        DWORD m_dwExStyle;
        DWORD m_dwStyle;
        WNDCLASSEX m_wndClass = {};
        HWND m_windowHandle   = nullptr;
        HINSTANCE m_hInstance = nullptr;
        RECT m_windowRect     = { 0, 0, 0, 0 };

        std::string m_className  = "DadEngine Class Name";
        std::string m_windowName = "DadEngine Window Name";
    };
} // namespace DadEngine

#endif //__WINDOWS_WINDOW_HPP_
