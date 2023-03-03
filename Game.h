#pragma once

#include <wrl.h>
#include <d3d.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <chrono>
#include <vector>

#include "GameComponent.h"
#include "WindowContainer.h"
#include "CollisionBox.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "DirectXTK.lib")

class Game : WindowContainer
{
    public:
        ID3D11Texture2D* backBuffer;
        ID3D11DeviceContext* context;
        Microsoft::WRL::ComPtr<ID3D11Device> device;
        ID3D11RenderTargetView* renderView;
        std::chrono::time_point<std::chrono::steady_clock> prevTime;
        std::chrono::steady_clock::time_point startTime;
        IDXGISwapChain* swapChain;
        float totalTime;
        ID3D11RasterizerState* rastState;

        void initialize(
            LPCWSTR name,
            int clientWidth,
            int clientHeight,
            std::vector<GameComponent*> components);
        void exit();
        void run();
        DisplayWin32 getDisplay();
        CollisionType checkWindowCollision(CollisionBox* collisionBox);
        std::vector<GameComponent*> getComponentsByType(std::string type);
        void addComponent(GameComponent* newComponent);
    
    private:
        bool isExitRequested = false;
        std::vector<GameComponent*> componentsToAdd;
        std::vector<GameComponent*> components;
    
        void destroyResources();
        void createBackBuffer();
        void prepareFrame();
        void messageHandler();
        void update(float deltaTime);
        float updateInterval(int& frameCount);
        void endFrame();
        void draw();

};