#define DADOPENGL/*DADVULKAN*/ //DADOPENGLES
//#define TEST

//#define WEB_TARGET
#if defined (WEB_TARGET)
	#include <emscripten/emscripten.h>
#endif

#include "Core/Core.hpp"
#include "Rendering/Rendering.hpp"
#include "Math/Math.hpp"
#include "Gameplay/Gameplay.hpp"

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


RenderContext* renderContext = nullptr;
IFile* vertexShaderReader = nullptr;
IFile * fragmentShaderReader = nullptr;

RenderPass* renderPass = nullptr;
Framebuffer* framebuffer = nullptr;

RawMesh triangle;
TArray<VertexInput> vertexLayout;
TArray<float> rawPosition;
uint32 uiStride = 0U;

VertexShader* vertexShader = nullptr;
FragmentShader* fragmentShader = nullptr;
Shader* mainShader = nullptr;
CommandBuffer* cmdBuff = nullptr;

VertexBuffer* vb = nullptr;

RenderingFeatureInfo renderFeatureInfo;
StaticMeshRenderingFeature renderFeature;
StaticMeshComponent meshComponent;

uint8 bLoop = TRUE;
uint32 uiCounter = 0U;
PlatformTimer fpsTimer;


void render_loop()
{
	//window.MessagePump();
	MSG msg = {};

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			bLoop = FALSE;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//else
	{
		InputManager::GetInputManager()->Update();

		//Profile renderProfile ("Rendering");
		ViewPacket view;
		FramePacket frame;

		renderContext->BeginFrame();

		framebuffer = renderContext->GetBackFramebuffer();

		cmdBuff->BeginRecord();
		cmdBuff->ClearColor(Color{ 0.0f, 0.1f, 1.0f, 1.0f });
		cmdBuff->ClearDepthStencil(0.0f, MAX_INT32);
		cmdBuff->BeginRenderPass(renderPass, framebuffer);
		cmdBuff->BindShader(mainShader);
		cmdBuff->BindVertexBuffer(vb);
		cmdBuff->DrawVertexBuffer(vb);
		cmdBuff->EndRenderPass(renderPass);
		cmdBuff->Present();
		cmdBuff->EndRecord();

		// Extract visible objects
		//cam.ExtractVisibleObjects(WorldObjects, frame);

		// Extract rendernode / component data
		//frame.Extract();

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

int main
{
#if defined(_DEBUG)
	Tests();
#endif
	Application::GetApp()->m_window.ToggleConsole();

#if defined(DADOPENGL)
	renderContext = new OpenGLRenderContext(Application::GetApp()->m_window);

	vertexShaderReader = PlatformFileSystem::CreateFileReader("test.vert", IO_MODE_TEXT);
	fragmentShaderReader = PlatformFileSystem::CreateFileReader("test.frag", IO_MODE_TEXT);
#elif defined (DADOPENGLES)
	renderContext = new OpenGLESRenderContext(Application::GetApp()->m_window);

	vertexShaderReader = PlatformFileSystem::CreateFileReader("test_es.vert", IO_MODE_TEXT);
	fragmentShaderReader = PlatformFileSystem::CreateFileReader("test_es.frag", IO_MODE_TEXT);
#elif defined(DADVULKAN)
	renderContext = new VulkanRenderContext(Application::GetApp()->m_window);

	vertexShaderReader = PlatformFileSystem::CreateFileReader("test.vert.spv", IO_MODE_BINARY);
	fragmentShaderReader = PlatformFileSystem::CreateFileReader("test.frag.spv", IO_MODE_BINARY);
#endif

	renderPass = renderContext->GetRenderPass();
	cmdBuff = renderContext->CreateCommandBuffer();

	String vertexShaderCode(vertexShaderReader->Size());
	vertexShaderReader->Read(vertexShaderCode);

	String fragmentShaderCode(fragmentShaderReader->Size());
	fragmentShaderReader->Read(fragmentShaderCode);
	

	vertexShader = renderContext->CreateVertexShader(vertexShaderCode.Cstr(), vertexShaderCode.Size(), vertexLayout);
	fragmentShader = renderContext->CreateFragmentShader(fragmentShaderCode.Cstr(), fragmentShaderCode.Size());
	mainShader = renderContext->CreateShader(vertexShader, nullptr, fragmentShader, renderPass);


	vertexLayout.Add({ 0U, VertexInputType::VERTEX_INPUT_TYPE_POSITION });
	vertexLayout.Add({ 1U, VertexInputType::VERTEX_INPUT_TYPE_COLOR });

	triangle.m_vertices.Add(RawVertex{ Vector3f{ -0.5f, -0.5f, 0.f }, Vector3f{ 1.0f, 0.0f, 0.0f } });
	triangle.m_vertices.Add(RawVertex{ Vector3f{ 0.5f, -0.5f, 0.f }, Vector3f{ 0.0f, 1.0f, 0.0f } });
	triangle.m_vertices.Add(RawVertex{ Vector3f{ 0.0f, 0.5f, 0.f }, Vector3f{ 0.0f, 0.0f, 1.0f } });
	
	Vertexfactory::Create(triangle, rawPosition, vertexLayout, uiStride);

	vb = renderContext->CreateVertexBuffer((uint32)triangle.m_vertices.Size(), rawPosition, vertexLayout, uiStride);

	renderFeature.Initialize(renderFeatureInfo);
	renderFeature.AddComponent(&meshComponent);

	Actor player(nullptr);
	Camera cam(&player);
	player.AddComponent(&cam);
	TArray<RenderObject*> WorldObjects;
	WorldObjects.Add(meshComponent.m_RenderObjectHandle);

	struct WInput : Input
	{
		WInput(Actor* _InPlayer)
			: Input(KEY_W),
			player(_InPlayer)
		{}

		void Action() override final
		{
			//printf("W\n");
			player->MoveLocation(Vector3f{ 0.f, 0.001f, 0.f });
		}

		Actor* player;
	};

	struct SInput : Input
	{
		SInput(Actor* _InPlayer)
			: Input(KEY_S),
			player(_InPlayer)
		{}

		void Action() override final
		{
			//printf("S\n");
			player->MoveLocation(Vector3f{ 0.f, -0.001f, 0.f });
		}

		Actor* player;
	};

	struct DInput : Input
	{
		DInput(Actor* _InPlayer)
			: Input(KEY_D),
			player(_InPlayer)
		{}

		void Action() override final
		{
			//printf("D\n");
			player->MoveLocation(Vector3f{ -0.001f, 0.f, 0.f });
		}

		Actor* player;
	};

	struct AInput : Input
	{
		AInput(Actor* _InPlayer)
			: Input(KEY_A),
			player(_InPlayer)
		{}

		void Action() override final
		{
			//printf("A\n");
			player->MoveLocation(Vector3f{ 0.001f, 0.f, 0.f });
		}

		Actor* player;
	};

	InputManager::GetInputManager()->m_Inputs.Add(new WInput{ &player});
	InputManager::GetInputManager()->m_Inputs.Add(new SInput{ &player });
	InputManager::GetInputManager()->m_Inputs.Add(new AInput{ &player });
	InputManager::GetInputManager()->m_Inputs.Add(new DInput{ &player });


	fpsTimer.Start();

#if defined (WEB_TARGET)
	emscripten_set_main_loop(render_loop, 0, 0);
#else
	while (bLoop)
	{
		//window.MessagePump();
		MSG msg = {};

		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				bLoop = FALSE;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//else
		{
			InputManager::GetInputManager()->Update();

			//Profile renderProfile ("Rendering");
			ViewPacket view;
			FramePacket frame;

			renderContext->BeginFrame();

			framebuffer = renderContext->GetBackFramebuffer();

			cmdBuff->BeginRecord();
			cmdBuff->ClearColor(Color{ 0.0f, 0.1f, 1.0f, 1.0f });
			cmdBuff->ClearDepthStencil(0.0f, MAX_UINT32);
			cmdBuff->BeginRenderPass(renderPass, framebuffer);
			cmdBuff->BindShader(mainShader);
			cmdBuff->BindVertexBuffer(vb);
			cmdBuff->DrawVertexBuffer(vb);
			cmdBuff->EndRenderPass(renderPass);
			cmdBuff->Present();
			cmdBuff->EndRecord();

			// Extract visible objects
			//cam.ExtractVisibleObjects(WorldObjects, frame);

			// Extract rendernode / component data
			//frame.Extract();

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
#endif

	return 0;
}