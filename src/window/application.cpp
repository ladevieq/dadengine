#include "application.hpp"

namespace DadEngine
{
    Application::Application()
        : m_window(new Window{ m_appInfo.m_applicationName, m_appInfo.m_width,
                               m_appInfo.m_height, m_appInfo.m_fullscreen,
                               m_appInfo.m_verticalSync })
    {
#if defined(DEBUG)
        initApplication(true);
#else
        initApplication(false);
#endif
    }

    Application::Application(ApplicationInfo _appInfo, const bool _openConsole)
        : m_appInfo(_appInfo),
          m_window(new Window{ m_appInfo.m_applicationName, m_appInfo.m_width,
                               m_appInfo.m_height, m_appInfo.m_fullscreen,
                               m_appInfo.m_verticalSync })
    {
        initApplication(_openConsole);
    }


    void Application::initApplication(const bool _openConsole)
    {
        // if (_openConsole)
        // {
        //     // TODO: Must be freed on exit
        //     AllocConsole();
        //     AttachConsole(GetCurrentProcessId());
        //     freopen("CON", "w", stdout);
        //     SetConsoleTitle("Debug Window");
        // }
    }

    void Application::Run()
    {
        while (m_window->IsOpen())
        {
            m_window->MessagePump();
        }
    }

    Window *Application::GetWindow()
    {
        return m_window.get();
    }

} // namespace DadEngine
