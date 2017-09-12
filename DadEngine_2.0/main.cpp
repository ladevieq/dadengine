#include "Core/Core.hpp"
#include "Rendering/Rendering.hpp"

#pragma comment(lib, "opengl32.lib")

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
}

int main
{
	//Application app(ApplicationInfo{"DadEngine", 1080U, 720U, FALSE });
	PlatformWindow window("DadEngine", 1080U, 720U, FALSE, FALSE);

	window.ToggleConsole();

	//RenderContext* renderContext = new OpenGLRenderContext(window);
	RenderContext* renderContext = new VulkanRenderContext(window);
	CommandBuffer cmdBuff;
	cmdBuff.Clear(Color(0.f, 1.f, 0.f, 1.f));
	cmdBuff.Present();

	Tests();

	uint8 bLoop = TRUE;

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
			Profile renderProfile ("Rendering");

			cmdBuff.Execute(renderContext);

			/*for (size_t i = 0; i < 1000000000U; i++)
			{

			}*/
		}
	}

	return 0;
}