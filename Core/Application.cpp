#include "Application.hpp"

#include "../Rendering/Rendering.hpp"

namespace DadEngine::Core
{
	Application* s_App = new Application(ApplicationInfo{ "DadEngine", 1080U, 720U, FALSE, FALSE });

	Application::Application()
		: m_window(m_AppInfo.m_sApplicationName, m_AppInfo.m_uiWidth, m_AppInfo.m_uiHeight, m_AppInfo.m_bFullscreen, m_AppInfo.m_bVerticalSync)
	{}

	Application::Application(ApplicationInfo _InAppInfo)
		: m_AppInfo(_InAppInfo),
		m_window(m_AppInfo.m_sApplicationName, m_AppInfo.m_uiWidth, m_AppInfo.m_uiHeight, m_AppInfo.m_bFullscreen, m_AppInfo.m_bVerticalSync)
	{	
	}


	void Application::Run()
	{
		while (m_bLoop)
		{
			//window.MessagePump();
			MSG msg = {};

			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
				{
					m_bLoop = FALSE;
				}

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			else
			{
				//Profile renderProfile ("Rendering");
				/*CommandBuffer cmdBuff;
				ViewPacket view;
				FramePacket frame;
				Camera cam;

				// Extract visible objects
				cam.ExtractVisibleObjects(WorldObjects, frame);

				// Extract rendernode / component data
				frame.Extract();

				// Foreach feature generate the rendering instructions
				renderFeature.SubmitViewBegin(view, cmdBuff);


				cmdBuff.BindVertexBuffer(vb);
				cmdBuff.DrawVertexBuffer(vb);


				if (renderFeatureInfo.SubmitNode == TRUE)
				{
					//renderFeature.SubmitNode();
				}

				if (renderFeatureInfo.SubmitNodes == TRUE)
				{
					//renderFeature.SubmitNodes();
				}

				renderFeature.SubmitViewEnd(view, cmdBuff);


				// Sync rendering and game threads
				// Exchange extracted datas and rendering commands

				// Resume threads

				cmdBuff.Execute(renderContext);


				if (fpsTimer.GetMilliseconds() >= 1000U)
				{
					//sprintf(name, "%u\0", uiCounter);
					printf("%u\n", uiCounter);

					//window.SetWindowTitle(name);
					fpsTimer.Reset();
					uiCounter = 0U;
				}

				uiCounter++;*/
			}
		}
	}

	Application * Application::GetApp()
	{
		return s_App;
	}
}