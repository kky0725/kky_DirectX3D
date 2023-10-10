#include "Framework.h"
#include "MainGame.h"

MainGame::MainGame()
{
	Initialize();

	//scene = new TutorialScene();
	//scene = new TextureScene();
	//scene = new TestScene();
	//scene = new TerrainScene();
	//scene = new TerrainEditorScene();
	scene = new ModelExportScene();
}

MainGame::~MainGame()
{
	delete scene;

	Release();
}

void MainGame::Update()
{
	scene->Update();

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

	scene->PreRender();

	Device::GetInstance()->Clear();

	Environment::GetInstance()->SetEnvironment();

	scene->Render();
	Time::GetInstance()->Render();

	scene->PostRender();
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

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

