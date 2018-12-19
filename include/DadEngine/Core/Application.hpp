#ifndef __APPLICATION_HPP_
#define __APPLICATION_HPP_

#include <stdint.h>

#include "Defines.hpp"
#include "Platform/Window.hpp"


namespace DadEngine::Core
{
    // class PlatformWindow;

	struct ApplicationInfo
    {
        ApplicationInfo() = default;

        ApplicationInfo(const char *sApplicationName, uint32_t _uiWidth, uint32_t _uiHeight, uint8_t _bFullscreen, uint8_t _bVerticalSync);

        const char *m_sApplicationName = nullptr;
        uint32_t m_uiWidth = 800U;
        uint32_t m_uiHeight = 600U;
        uint8_t m_bFullscreen = 0U;
        uint8_t m_bVerticalSync = 0U;
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

        uint8_t m_bLoop = TRUE;
    };
} // namespace DadEngine::Core

#endif //__APPLICATION_HPP_