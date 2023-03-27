#include <iostream>

#include "Game.h"

void Game::initialize(
	LPCWSTR name,
	int clientWidth,
	int clientHeight,
	std::vector<GameComponent*> components)
{
	this->components = components;
	this->display.initialize(this, name, clientWidth, clientHeight);
	this->mouse.initialize(&this->display);
	this->camera = new Camera();
	camera->AspectRatio = static_cast<float>(this->display.clientWidth) / static_cast<float>(this->display.clientHeight);

	D3D_FEATURE_LEVEL featureLevel[] = { D3D_FEATURE_LEVEL_11_1 };

	DXGI_SWAP_CHAIN_DESC swapDesc = {};
	swapDesc.BufferCount = 2;
	swapDesc.BufferDesc.Width = display.clientWidth;
	swapDesc.BufferDesc.Height = display.clientHeight;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = display.hWnd;
	swapDesc.Windowed = true;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;

	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_BGRA_SUPPORT,
		featureLevel,
		1,
		D3D11_SDK_VERSION,
		&swapDesc,
		&swapChain,
		&device,
		nullptr,
		&context);

	createBackBuffer();

	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width = this->display.clientWidth;
	depthStencilDesc.Height = this->display.clientHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	device->CreateTexture2D(&depthStencilDesc, nullptr, &depthStencilBuffer);
	device->CreateDepthStencilView(depthStencilBuffer, nullptr, &depthStencilView);

	for (auto& component : components)
	{
		component->initialize(this);
	}

}

void Game::createBackBuffer()
{
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	device->CreateRenderTargetView(backBuffer, nullptr, &renderView);
}

void Game::run()
{
	startTime = std::chrono::steady_clock::now();
	prevTime = startTime;
	int frameCount = 0;

	while (!isExitRequested) {
		messageHandler();
		prepareFrame();
		float deltaTime = updateInterval(frameCount);
		update(deltaTime);
		draw();
		endFrame();
		updateComponents();
	}
}

DisplayWin32 Game::getDisplay()
{
	return this->display;
}

Keyboard Game::getKeyboard()
{
	return this->keyboard;
}

Mouse Game::getMouse()
{
	return this->mouse;
}

void Game::messageHandler()
{
	MSG msg = {};
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// If windows signals to end the application then exit out.
	if (msg.message == WM_QUIT) {
		isExitRequested = true;
	}
}

void Game::prepareFrame()
{
	context->ClearState();

	D3D11_VIEWPORT viewport = {};
	viewport.Width = static_cast<float>(display.clientWidth);
	viewport.Height = static_cast<float>(display.clientHeight);
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1.0f;

	context->RSSetViewports(1, &viewport);

	context->OMSetRenderTargets(1, &renderView, depthStencilView);

	float color[] = { 0, 0, 0, 0 };
	context->ClearRenderTargetView(renderView, color);
	context->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void Game::exit()
{
	this->isExitRequested = true;
}

void Game::destroyResources()
{
	for (auto& component : components)
	{
		component->destroyResources();
	}

	context->Release();
	backBuffer->Release();
	renderView->Release();
	swapChain->Release();
	device->Release();
	depthStencilView->Release();
	depthStencilBuffer->Release();
}

void Game::draw()
{
	for (auto& component : components)
	{
		component->draw();
	}
}

void Game::updateComponents()
{
	if (componentsToAdd.empty()) {
		return;
	}

	for (auto& component : componentsToAdd)
	{
		component->initialize(this);
		components.insert(components.begin(), component);
	}
	componentsToAdd.clear();
}

void Game::update(float deltaTime) {

	camera->UpdateMatrix();
	for (auto& component : components)
	{
		component->update(deltaTime);
	}
}

float Game::updateInterval(int& frameCount) {
	auto	curTime = std::chrono::steady_clock::now();
	float	deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(curTime - prevTime).count() / 1000000.0f;
	prevTime = curTime;

	totalTime += deltaTime;
	frameCount++;

	if (totalTime > 1.0f) {
		float fps = frameCount / totalTime;

		totalTime -= 1.0f;

		WCHAR text[256];
		swprintf_s(text, TEXT("FPS: %f"), fps);
		SetWindowText(display.hWnd, text);

		frameCount = 0;
	}

	return deltaTime;
}

void Game::endFrame()
{
	context->OMSetRenderTargets(0, nullptr, nullptr);

	swapChain->Present(1, /*DXGI_PRESENT_DO_NOT_WAIT*/ 0);
}

std::vector<GameComponent*> Game::getComponentsByType(std::string type) {
	std::vector<GameComponent*> result;
	for (auto& component : components)
	{
		if (component->getType() == type) {
			result.push_back(component);
		}
	}

	return result;
}

void Game::addComponent(GameComponent* component)
{
	componentsToAdd.push_back(component);
}

void Game::removeComponent(GameComponent* component)
{
	auto it = std::find(components.begin(), components.end(), component);
	int index = 0;
	if (it != components.end())
	{
		index = it - components.begin();
	}
	else {
		index = -1;
	}

	if (index >= 0) {
		components.erase(components.begin() + index);
		component->destroyResources();
	}
}
