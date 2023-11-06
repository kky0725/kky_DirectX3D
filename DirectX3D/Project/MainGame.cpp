#include "Framework.h"
#include "MainGame.h"

MainGame::MainGame()
{
	srand(time(NULL));
	//srand((unsigned int)time(nullptr));

	Initialize();

	//scene = new TutorialScene();
	//scene = new TextureScene();
	//scene = new TestScene();
	//scene = new TerrainScene();
	//scene = new TerrainEditorScene();
	//scene = new ModelExportScene();
	//scene = new ModelAnimationScene();
	//scene = new CollisionScene();

	SCENE->Create("Grid", new GridScene());
	//SCENE->Create("Collision", new CollisionScene);
	SCENE->Create("ModelAnimation", new ModelAnimationScene);
	//SCENE->Create("Instancing", new InstancingScene);
	//SCENE->Create("Start", new ModelInstancingScene);
	SCENE->Create("Start", new LightScene);
	//SCENE->Create("Export", new ModelExportScene);

	SCENE->Add("Grid");
	//SCENE->Add("Collision");
	SCENE->Add("ModelAnimation");
	SCENE->Add("Start");
	//SCENE->Add("Export");
}

MainGame::~MainGame()
{
	SceneManager::Delete();

	Release();
}

void MainGame::Update()
{
	SCENE->Update();

	Time::GetInstance()->Update();
	Keyboard::GetInstance()->Update();
	Camera::GetInstance()->Update();
}

void MainGame::Render()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (_isWireFrame)
	{
		RS->ChangeState(D3D11_FILL_WIREFRAME);
	}
	else
		RS->ChangeState(D3D11_FILL_SOLID);

	SCENE->PreRender();

	Device::GetInstance()->Clear();

	Environment::GetInstance()->SetEnvironment();

	SCENE->Render();
	Time::GetInstance()->Render();

	Environment::GetInstance()->PostSet();

	SCENE->PostRender();
	Camera::GetInstance()->Debug();
	Environment::GetInstance()->PostRneder();

	ImGui::Checkbox("WireFrame", &_isWireFrame);

	ImGui::Render();

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::GetInstance()->Present();
}

void MainGame::Initialize()
{
	//Device::GetInstance();
	Environment::GetInstance();
	Keyboard::GetInstance();
	Time::GetInstance();
	StateManager::GetInstance();

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(DEVICE, DC);
}

void MainGame::Release()
{
	StateManager::Delete();
	Time::Delete();
	Keyboard::Delete();
	Shader::Delete();
	Environment::Delete();
	Device::Delete();
	Camera::Delete();
	Texture::Delete();
	//SceneManager::Delete();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

