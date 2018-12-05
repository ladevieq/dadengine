#ifndef __APPLICATION_HPP_
#define __APPLICATION_HPP_

#include "Defines.hpp"
#include "PlatformTypes.hpp"
#include "PlatformWindow.hpp"


namespace DadEngine::Core
{
	//class ::DadEngine::Rendering::RenderContext;

	struct ApplicationInfo
	{
		ApplicationInfo() = default;

		ApplicationInfo(const char* sApplicationName,
			uint32 _uiWidth, uint32 _uiHeight,
			uint8 _bFullscreen, uint8 _bVerticalSync)
			: m_sApplicationName(sApplicationName),
			m_uiWidth(_uiWidth),
			m_uiHeight(_uiHeight),
			m_bFullscreen(_bFullscreen),
			m_bVerticalSync(_bVerticalSync)
		{}

		const char* m_sApplicationName = "\0";
		uint32 m_uiWidth = 800U;
		uint32 m_uiHeight = 600U;
		uint8 m_bFullscreen = 0U;
		uint8 m_bVerticalSync = 0U;
	};

	class Application
	{
	public:

		Application();//, m_renderContext(new Rendering::OpenGLRenderContext(m_window)) {}

		Application(ApplicationInfo _InAppInfo);//, m_renderContext(new Rendering::OpenGLRenderContext(m_window)) {}


		void Run();


		FORCE_INLINE PlatformWindow GetWindow() { return m_window; }


		static Application* GetApp();

	//private:

		//void Handle

		ApplicationInfo m_AppInfo = {};
		PlatformWindow m_window;
		//Rendering::RenderContext* m_renderContext = nullptr;

		uint8 m_bLoop = TRUE;
	};
}

#endif //__APPLICATION_HPP_