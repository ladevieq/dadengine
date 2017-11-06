#ifndef __APPLICATION_HPP_
#define __APPLICATION_HPP_

#include "Defines.hpp"
#include "PlatformTypes.hpp"
#include "PlatformWindow.hpp"

namespace DadEngine::Core
{
	struct ApplicationInfo
	{
		const char* m_sApplicationName;
		uint32 m_uiWidth = 800U;
		uint32 m_uiHeight = 600U;
		uint8 m_bFullscreen = 0U;
		uint8 m_bVerticalSync = 0U;
	};

	class Application
	{
	public:

		Application();//, m_renderContext(new Rendering::OpenGLRenderContext(m_window)) {}

		Application(ApplicationInfo& _InAppInfo);//, m_renderContext(new Rendering::OpenGLRenderContext(m_window)) {}


		void Run();


	private:

		//void Handle

		ApplicationInfo m_AppInfo = {};
		PlatformWindow m_window;
		//RenderContext* m_renderContext = nullptr;

		uint8 m_bLoop = TRUE;
	};
}

#endif //__APPLICATION_HPP_