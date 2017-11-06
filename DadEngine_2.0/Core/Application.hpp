#ifndef __APPLICATION_HPP_
#define __APPLICATION_HPP_



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

		Application() : m_window(m_AppInfo.m_sApplicationName, m_AppInfo.m_uiWidth, m_AppInfo.m_uiHeight, m_AppInfo.m_bFullscreen, m_AppInfo.m_bVerticalSync) {}//, m_renderContext(new Rendering::OpenGLRenderContext(m_window)) {}

		Application(ApplicationInfo& _InAppInfo) : m_AppInfo(_InAppInfo), m_window(m_AppInfo.m_sApplicationName, m_AppInfo.m_uiWidth, m_AppInfo.m_uiHeight, m_AppInfo.m_bFullscreen, m_AppInfo.m_bVerticalSync) {}//, m_renderContext(new Rendering::OpenGLRenderContext(m_window)) {}


		void Run()
		{
			while (m_bLoop)
			{

			}
		}


	private:

		//void Handle

		ApplicationInfo m_AppInfo = {};
		PlatformWindow m_window;
		//Rendering::RenderContext* m_renderContext = nullptr;

		uint8 m_bLoop = TRUE;
	};
}

#endif //__APPLICATION_HPP_