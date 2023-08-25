#include "Framework.h"
#include "MainGame.h"

MainGame::MainGame()
{
	Initialize();

	scene = new TextureScene();
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
}

void MainGame::Render()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	scene->PreRender();

	Device::GetInstance()->Clear();

	scene->Render();

	scene->PostRender();

	ImGui::Render();

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::GetInstance()->Present();
}

void MainGame::Initialize()
{
	Device::GetInstance();
	Environment::GetInstance();
	Keyboard::GetInstance();
	Time::GetInstance();

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
	Time::Delete();
	Keyboard::Delete();
	Device::Delete();
	Shader::Delete();
	Environment::Delete();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

