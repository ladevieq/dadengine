//#define DADOPENGL //DADOPENGLES
//#define DADVULKAN

#include "Core/Core.hpp"
#include "Rendering/Rendering.hpp"
#include "Math/Math.hpp"
#include "Gameplay/Gameplay.hpp"

void Tests()
{
	DadEngine::Core::Test::TestTypes();
	//DadEngine::Core::Test::Test();
	//DadEngine::Core::Test::Test();
	DadEngine::Core::Test::TestTArray();
	DadEngine::Core::Test::TestDictionary();
	DadEngine::Core::Test::TestThread();
	DadEngine::Core::Test::TestTime();
	DadEngine::Core::Test::TestProfile();
	DadEngine::Core::Test::TestSerialization();
	DadEngine::Math::Test::TestMathConstants();
	DadEngine::Math::Test::TestMathFunctions();
	DadEngine::Math::Test::TestMatrix2x2();
	DadEngine::Math::Test::TestMatrix3x3();
	DadEngine::Math::Test::TestMatrix4x4();
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

Actor* player = nullptr;
Camera* cam = nullptr;
TArray<RenderObject*> WorldObjects;

uint8 bLoop = TRUE;
uint32 uiCounter = 0U;
PlatformTimer fpsTimer;

/*
 * Inputs
*/
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


/*
 * Engine stuff
*/
void setupRenderContextAndRederingStuffs() {
#if defined(_DEBUG)
	//Tests();
#endif
	Application::GetApp()->m_window.ToggleConsole();

#if defined(DADOPENGL)
	Application::GetApp()->m_window.SetWindowTitle("OpenGL");
	renderContext = new OpenGLRenderContext(Application::GetApp()->m_window);

	vertexShaderReader = PlatformFileSystem::CreateFileReader("test_multiple.vert", IO_MODE_TEXT);
	fragmentShaderReader = PlatformFileSystem::CreateFileReader("test_multiple.frag", IO_MODE_TEXT);

	// We add one because we need the null character
	String vertexShaderCode(vertexShaderReader->Size() + 1);
	vertexShaderReader->Read(vertexShaderCode);

	String fragmentShaderCode(fragmentShaderReader->Size() + 1);
	fragmentShaderReader->Read(fragmentShaderCode);
#elif defined (DADOPENGLES)
	Application::GetApp()->m_window.SetWindowTitle("OpenGLES");
	renderContext = new OpenGLESRenderContext(Application::GetApp()->m_window);

	vertexShaderReader = PlatformFileSystem::CreateFileReader("test_es.vert", IO_MODE_TEXT);
	fragmentShaderReader = PlatformFileSystem::CreateFileReader("test_es.frag", IO_MODE_TEXT);
#elif defined(DADVULKAN)
	Application::GetApp()->m_window.SetWindowTitle("Vulkan");
	renderContext = new VulkanRenderContext(Application::GetApp()->m_window);

	vertexShaderReader = PlatformFileSystem::CreateFileReader("test_vk.vert.spv", IO_MODE_BINARY);
	fragmentShaderReader = PlatformFileSystem::CreateFileReader("test_vk.frag.spv", IO_MODE_BINARY);

	String vertexShaderCode(vertexShaderReader->Size());
	vertexShaderReader->Read(vertexShaderCode);

	String fragmentShaderCode(fragmentShaderReader->Size());
	fragmentShaderReader->Read(fragmentShaderCode);
#endif

	renderPass = renderContext->GetRenderPass();
	cmdBuff = renderContext->CreateCommandBuffer();

	vertexLayout.Add({ 0U, VertexInputType::VERTEX_INPUT_TYPE_POSITION });
	vertexLayout.Add({ 1U, VertexInputType::VERTEX_INPUT_TYPE_COLOR });

	vertexShader = renderContext->CreateVertexShader(vertexShaderCode.Cstr(), vertexShaderCode.Size(), vertexLayout);
	fragmentShader = renderContext->CreateFragmentShader(fragmentShaderCode.Cstr(), fragmentShaderCode.Size());
	mainShader = renderContext->CreateShader(vertexShader, nullptr, fragmentShader, renderPass);

	/* triangle.m_vertices.Add(RawVertex{ Vector3f{ -0.5f, -0.5f, -1.f }, Vector3f{ 1.0f, 0.0f, 0.0f } });
	triangle.m_vertices.Add(RawVertex{ Vector3f{ 0.5f, -0.5f, -1.f }, Vector3f{ 0.0f, 1.0f, 0.0f } });
	triangle.m_vertices.Add(RawVertex{ Vector3f{ 0.0f, 0.5f, -1.f }, Vector3f{ 0.0f, 0.0f, 1.0f } }); */
	triangle.m_vertices.Add(RawVertex{ Vector3f{ -999.5f, -999.5f, -999.f }, Vector3f{ 1.0f, 0.0f, 0.0f } });
	triangle.m_vertices.Add(RawVertex{ Vector3f{ -998.5f, -999.5f, -999.f }, Vector3f{ 0.0f, 1.0f, 0.0f } });
	triangle.m_vertices.Add(RawVertex{ Vector3f{ -999.0f, -998.5f, -999.f }, Vector3f{ 0.0f, 0.0f, 1.0f } });

	Vertexfactory::Create(triangle, rawPosition, vertexLayout, uiStride);

	vb = renderContext->CreateVertexBuffer((uint32)triangle.m_vertices.Size(), rawPosition, vertexLayout, uiStride);

	renderFeature.Initialize(renderFeatureInfo);
	renderFeature.AddComponent(&meshComponent);

	player = new Actor(nullptr);
	cam = new Camera(player);
	WorldObjects.Add(meshComponent.m_RenderObjectHandle);

	InputManager::GetInputManager()->m_Inputs.Add(new WInput{ player });
	InputManager::GetInputManager()->m_Inputs.Add(new SInput{ player });
	InputManager::GetInputManager()->m_Inputs.Add(new AInput{ player });
	InputManager::GetInputManager()->m_Inputs.Add(new DInput{ player });

	fpsTimer.Start();
}

void messagePump() {
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
}

void updateFpsCounter() {
	if (fpsTimer.GetMilliseconds() >= 1000U)
	{
		char name[128];
		sprintf(name, "%u\0", uiCounter);
		//printf("%u\n", uiCounter);

		Application::GetApp()->m_window.SetWindowTitle(name);
		fpsTimer.Reset();
		uiCounter = 0U;
	}

	uiCounter++;
}

void renderLoop() {
	if (bLoop)
	{
		InputManager::GetInputManager()->Update();

		/*Matrix4x4 pers = CameraManager::GetCameraManager()->GetMainCamera()->GetProjectionMatrix();
		Matrix4x4 view;
		Vector3f eyePos = CameraManager::GetCameraManager()->GetMainCamera()->m_Owner->GetRelativeLocation();
		Vector3f targetPosition = Vector3f{ eyePos.x, eyePos.y, -1.f };
		Vector3f up = Vector3f{ 0.f, 1.f, 0.f };
		view.LookAt(eyePos, targetPosition, up);
		Matrix4x4 vp = pers * view;

		Vector4f v1 = Vector4f(triangle.m_vertices[0U].Position.x, triangle.m_vertices[0U].Position.y, triangle.m_vertices[0U].Position.z, 1.0);
		v1 = vp * v1;*/

		//Profile renderProfile ("Rendering");
		ViewPacket view;
		FramePacket frame;

		renderContext->BeginFrame();

		framebuffer = renderContext->GetBackFramebuffer();

		cmdBuff->BeginRecord();
		cmdBuff->ClearColor(Color{ 0.0f, 0.1f, 1.0f, 1.0f });
		cmdBuff->ClearDepthStencil(1.0f, 0U);
		cmdBuff->BeginRenderPass(renderPass, framebuffer);
		cmdBuff->BindShader(mainShader);
		cmdBuff->BindVertexBuffer(vb);
		cmdBuff->DrawVertexBufferMultipleTimes(vb, 100);
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

		updateFpsCounter();
	}
}


/*
 * Main
*/
int main {
	setupRenderContextAndRederingStuffs();

	while (bLoop)
	{
		messagePump();
		renderLoop();
	}

	return 0;
}