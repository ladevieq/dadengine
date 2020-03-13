#pragma once

#include <cstdint>
#include <xcb/xcb.h>

namespace DadEngine {
    class Window {
        public:
        Window(const char *_windowName, int32_t _width, int32_t _height, bool _fullscreen, bool _veticalSync);
        ~Window();


        void MessagePump() {}

        bool GetFullscreen()
        {
            return m_fullscreen;
        }

        bool GetVerticalSync()
        {
            return m_verticalSync;
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
        bool m_isOpen = false;
        bool m_fullscreen = false;
        bool m_verticalSync = false;

        const char *m_windowName = "DadEngine Window Name\0";

        xcb_connection_t *m_ptrConnection = nullptr;
    };
}
