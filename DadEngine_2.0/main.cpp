#include "Core/Core.hpp"
#include "Rendering/Rendering.hpp"
#include "Math/Math.hpp"

#define /*DADOPNEGL//*/ DADVULKAN
#define TEST

void Tests()
{
	//Test::TestTypes();
	//Test::Test();
	//Test::Test();
	//DadEngine::Core::Test::TestTArray();
	//Test::TestDictionary();
	//Test::TestThread();
	//Test::TestTime();
	//Test::TestProfile();
	//Test::TestSerialization();
	//DadEngine::Math::Test::TestMathConstants();
	//DadEngine::Math::Test::TestMathFunctions();
	//DadEngine::Math::Test::TestMatrix2x2();
	//DadEngine::Math::Test::TestMatrix3x3();
	//DadEngine::Math::Test::TestMatrix4x4();
}

int main
{
#if defined(_DEBUG)
	Tests();
#endif

	//Application app(ApplicationInfo{"DadEngine", 1080U, 720U, FALSE });
	PlatformWindow window("DadEngine", 1080U, 720U, FALSE, FALSE);

	window.ToggleConsole();


#if defined(DADOPNEGL)
	RenderContext* renderContext = new OpenGLRenderContext(window);
	IFile* vertexShaderReader = PlatformFileSystem::CreateFileReader("test.vert", IO_MODE_TEXT);

	IFile* fragmentShaderReader = PlatformFileSystem::CreateFileReader("test.frag", IO_MODE_TEXT);
#elif defined(DADVULKAN)
	RenderContext* renderContext = new VulkanRenderContext(window);
	IFile* vertexShaderReader = PlatformFileSystem::CreateFileReader("test.vert.spv", IO_MODE_BINARY);

	IFile* fragmentShaderReader = PlatformFileSystem::CreateFileReader("test.frag.spv", IO_MODE_BINARY);
#endif

	String vertexShaderCode(vertexShaderReader->Size());
	b8 ret = vertexShaderReader->Read(vertexShaderCode);

	String fragmentShaderCode(fragmentShaderReader->Size());
	fragmentShaderReader->Read(fragmentShaderCode);


	RawMesh triangle;
	triangle.m_vertices.Add(RawVertex{ Vector3f{ -0.5f, -0.5f, 0.f }, Vector3f{ 1.0f, 0.0f, 0.0f } });
	triangle.m_vertices.Add(RawVertex{ Vector3f{ 0.5f, -0.5f, 0.f }, Vector3f{ 0.0f, 1.0f, 0.0f } });
	triangle.m_vertices.Add(RawVertex{ Vector3f{ 0.0f, 0.5f, 0.f }, Vector3f{ 0.0f, 0.0f, 1.0f } });

	TArray<VertexInput> vertexLayout;
	vertexLayout.Add({ 0U, VertexInputType::VERTEX_INPUT_TYPE_POSITION });
	vertexLayout.Add({ 1U, VertexInputType::VERTEX_INPUT_TYPE_COLOR });
	uint32 uiStride = 0U;


	RenderPass* renderPass = renderContext->GetRenderPass();
	Framebuffer* framebuffer = nullptr;
	VertexShader* vertexShader = renderContext->CreateVertexShader(vertexShaderCode.Cstr(), vertexShaderCode.Size(), vertexLayout);
	FragmentShader* fragmentShader = renderContext->CreateFragmentShader(fragmentShaderCode.Cstr(), fragmentShaderCode.Size());
	Shader* mainShader = renderContext->CreateShader(vertexShader, nullptr, fragmentShader, renderPass);
	CommandBuffer* cmdBuff = renderContext->CreateCommandBuffer();

	TArray<float> rawPosition;
	Vertexfactory::Create(triangle, rawPosition, vertexLayout, uiStride);

	VertexBuffer* vb = renderContext->CreateVertexBuffer((uint32)triangle.m_vertices.Size(), rawPosition, vertexLayout, uiStride);

	RenderingFeatureInfo renderFeatureInfo;
	StaticMeshRenderingFeature renderFeature;
	StaticMeshComponent meshComponent;

	renderFeature.Initialize(renderFeatureInfo);
	renderFeature.AddComponent(&meshComponent);

	TArray<RenderObject*> WorldObjects;
	WorldObjects.Add(meshComponent.m_RenderObjectHandle);

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
			ViewPacket view;
			FramePacket frame;
			Camera cam;

			renderContext->BeginFrame();

			framebuffer = renderContext->GetBackFramebuffer();

			cmdBuff->BeginRecord();
			cmdBuff->ClearColor(Color{ 0.0f, 0.0f, 0.0f, 1.0f });
			cmdBuff->ClearDepthStencil(0.0f, UINT32_MAX);
			cmdBuff->BeginRenderPass(renderPass, framebuffer);
			cmdBuff->BindShader(mainShader);
			cmdBuff->BindVertexBuffer(vb);
			cmdBuff->DrawVertexBuffer(vb);
			cmdBuff->EndRenderPass(renderPass);
			cmdBuff->Present();
			cmdBuff->EndRecord();

			// Extract visible objects
			cam.ExtractVisibleObjects(WorldObjects, frame);

			// Extract rendernode / component data
			frame.Extract();

			// Foreach feature generate the rendering instructions
			//renderFeature.SubmitViewBegin(view, cmdBuff);


			if (renderFeatureInfo.SubmitNode == TRUE)
			{
				//renderFeature.SubmitNode();
			}

			if (renderFeatureInfo.SubmitNodes == TRUE)
			{
				//renderFeature.SubmitNodes();
			}

			//renderFeature.SubmitViewEnd(view, cmdBuff);


			// Sync rendering and game threads
			// Exchange extracted datas and rendering commands
			
			// Resume threads
			renderContext->EndFrame();


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