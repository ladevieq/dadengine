#ifndef __APPLICATION_HPP_
#define __APPLICATION_HPP_

#include "Platform/Types.hpp"
#include "Platform/Window.hpp"


namespace DadEngine::Core
{
	struct ApplicationInfo
    {
        ApplicationInfo() = default;

        ApplicationInfo(const char *sApplicationName, uint32 _uiWidth, uint32 _uiHeight, uint8 _bFullscreen, uint8 _bVerticalSync);

        const char *m_sApplicationName = nullptr;
        uint32 m_uiWidth = 800U;
        uint32 m_uiHeight = 600U;
        uint8 m_bFullscreen = 0U;
        uint8 m_bVerticalSync = 0U;
    };

    class Application
    {
        public:
        Application(); //, m_renderContext(new Rendering::OpenGLRenderContext(m_window)) {}

        Application(ApplicationInfo _InAppInfo); //, m_renderContext(new Rendering::OpenGLRenderContext(m_window)) {}


        // void Run();


        PlatformWindow GetWindow();


        static Application *GetApp();

        // private:

        // void Handle

        ApplicationInfo m_AppInfo = {};
        PlatformWindow m_window;
        // Rendering::RenderContext* m_renderContext = nullptr;

        uint8 m_bLoop = TRUE;
    };
} // namespace DadEngine::Core

#endif //__APPLICATION_HPP_