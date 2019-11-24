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

    struct ConsoleInfo
    {
        HWND consoleHandle = nullptr;
        const char *m_consoleName = nullptr;
        bool m_isOpen = false;
    };

    class Application
    {
        public:
        Application(); //, m_renderContext(new Rendering::OpenGLRenderContext(m_window)) {}

        Application(ApplicationInfo _appInfo, const bool _openConsole); //, m_renderContext(new Rendering::OpenGLRenderContext(m_window)) {}


        void Run();

        Window *GetWindow();

        private:
        void initApplication(const bool _openConsole);

        ApplicationInfo m_appInfo = {};
        ConsoleInfo m_consoleInfo = {};

        std::unique_ptr<Window> m_window;
        //
        // Rendering::RenderContext* m_renderContext = nullptr;
    };
} // namespace DadEngine

#endif //__APPLICATION_HPP_
