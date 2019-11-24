#include "application.hpp"
// #include "../Rendering/Rendering.hpp"

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
        if (_openConsole)
        {
            // Must be freed on exit
            AllocConsole();
            AttachConsole(GetCurrentProcessId());
            freopen("CONOUT$", "w", stdout);
            SetConsoleTitle("Debug Window");
        }
    }

    void Application::Run()
    {
        while (m_window->IsOpen())
        {
            m_window->MessagePump();
            MSG msg = {};

            if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
            {
                if (msg.message == WM_QUIT)
                {
                    m_window->Close();
                }

                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            //
            // else
            // {
            //     // Profile renderProfile ("Rendering");
            //     CommandBuffer cmdBuff;
            //     ViewPacket view;
            //     FramePacket frame;
            //     Camera cam;
            //
            //     // Extract visible objects
            //     cam.ExtractVisibleObjects(WorldObjects, frame);
            //
            //     // Extract rendernode / component data
            //     frame.Extract();
            //
            //     // Foreach feature generate the rendering instructions
            //     renderFeature.SubmitViewBegin(view, cmdBuff);
            //
            //
            //     cmdBuff.BindVertexBuffer(vb);
            //     cmdBuff.DrawVertexBuffer(vb);
            //
            //
            //     if (renderFeatureInfo.SubmitNode == TRUE)
            //     {
            //         // renderFeature.SubmitNode();
            //     }
            //
            //     if (renderFeatureInfo.SubmitNodes == TRUE)
            //     {
            //         // renderFeature.SubmitNodes();
            //     }
            //
            //     renderFeature.SubmitViewEnd(view, cmdBuff);
            //
            //
            //     // Sync rendering and game threads
            //     // Exchange extracted datas and rendering commands
            //
            //     // Resume threads
            //
            //     cmdBuff.Execute(renderContext);
            //
            //
            //     if (fpsTimer.GetMilliseconds() >= 1000U)
            //     {
            //         // sprintf(name, "%u\0", uiCounter);
            //         printf("%u\n", uiCounter);
            //
            //         // window.SetWindowTitle(name);
            //         fpsTimer.Reset();
            //         uiCounter = 0U;
            //     }
            //
            //     uiCounter++;
            // }
        }
    } // namespace DadEngine

    Window *Application::GetWindow()
    {
        return m_window.get();
    }

} // namespace DadEngine
