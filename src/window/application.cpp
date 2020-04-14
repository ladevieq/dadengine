#include "application.hpp"

namespace DadEngine
{
    Application::Application()
        : m_window({ m_appInfo.m_applicationName, m_appInfo.m_width, m_appInfo.m_height,
                     m_appInfo.m_fullscreen, m_appInfo.m_verticalSync })
    {
    }

    Application::Application(ApplicationInfo _appInfo)
        : m_appInfo(_appInfo),
          m_window({ m_appInfo.m_applicationName, m_appInfo.m_width, m_appInfo.m_height,
                     m_appInfo.m_fullscreen, m_appInfo.m_verticalSync })
    {
    }


    void Application::Run()
    {
        while (m_window.IsOpen())
        {
            m_window.MessagePump();
        }
    }

    Window& Application::GetWindow()
    {
        return m_window;
    }

} // namespace DadEngine
