#ifndef __APPLICATION_HPP_
#define __APPLICATION_HPP_

#include <cstdint>
#include <memory>

#include "windows-window.hpp"

namespace DadEngine
{
    struct ApplicationInfo
    {
        const char *m_applicationName = nullptr;
        int32_t m_width = 800;
        int32_t m_height = 600;
        bool m_fullscreen = false;
        bool m_verticalSync = false;
    };

    class Window;

    class Application
    {
        public:
        Application();
        Application(ApplicationInfo _appInfo);

        void Run();

        Window& GetWindow();

        private:
        ApplicationInfo m_appInfo = {};

        Window m_window;
    };
} // namespace DadEngine

#endif //__APPLICATION_HPP_
