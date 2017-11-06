#include "Core/Core.hpp"
#include "Rendering/Rendering.hpp"
#include "Math/Math.hpp"

void Tests()
{
	//Test::TestTypes();
	//Test::Test();
	//Test::Test();
	//Test::TestTArray();
	//Test::TestDictionary();
	//Test::TestThread();
	//Test::TestTime();
	//Test::TestProfile();
	//Test::TestSerialization();
	DadEngine::Math::Test::TestMathConstants();
	DadEngine::Math::Test::TestMathFunctions();
	DadEngine::Math::Test::TestMatrix2x2();
	DadEngine::Math::Test::TestMatrix3x3();
	DadEngine::Math::Test::TestMatrix4x4();
}

int main
{
	//Application app(ApplicationInfo{"DadEngine", 1080U, 720U, FALSE });
	PlatformWindow window("DadEngine", 1080U, 720U, FALSE, FALSE);

	window.ToggleConsole();

	//RenderContext* renderContext = new OpenGLRenderContext(window);
	RenderContext* renderContext = new VulkanRenderContext(window);
	RenderingFeatureInfo renderFeatureInfo;
	StaticMeshRenderingFeature renderFeature;
	StaticMeshComponent meshComponent;

	renderFeature.Initialize(renderFeatureInfo);
	renderFeature.AddComponent(&meshComponent);

	TArray<RenderObject*> WorldObjects;
	WorldObjects.Add(meshComponent.m_RenderObjectHandle);

	Tests();

	uint8 bLoop = TRUE;
	uint32 uiCounter = 0U;
	PlatformTimer fpsTimer;
	fpsTimer.Start();

	while (bLoop)
	{
		//window.MessagePump();
		MSG msg = {};

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				bLoop = FALSE;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		else
		{
			//Profile renderProfile ("Rendering");
			CommandBuffer cmdBuff;
			ViewPacket view;
			FramePacket frame;
			Camera cam;

			// Extract visible objects
			cam.ExtractVisibleObjects(WorldObjects, frame);

			// Extract rendernode / component data
			frame.Extract();

			// Foreach feature generate the rendering instructions
			renderFeature.SubmitViewBegin(view, cmdBuff);

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

			uiCounter++;
		}
	}

	return 0;
}