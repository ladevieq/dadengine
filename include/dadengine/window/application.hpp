#pragma once

#include <cstdint>
#include <memory>

#include "window.hpp"

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

    class Application
    {
        public:
        Application();
        Application(ApplicationInfo _appInfo, const bool _openConsole);

        void Run();

        Window *GetWindow();

        private:
        void initApplication(const bool _openConsole);

        void closeApplication();

        ApplicationInfo m_appInfo = {};
        // ConsoleInfo m_consoleInfo = {};

        std::unique_ptr<Window> m_window;
    };
} // namespace DadEngine
