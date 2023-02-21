#pragma once

#include <wrl.h>
#include <d3d.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <chrono>
#include <vector>

#include "GameComponent.h"
#include "DisplayWin32.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

class Game
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
        DisplayWin32 display;
        ID3D11RasterizerState* rastState;
    
        Game(
            LPCWSTR name,
            int clientWidth,
            int clientHeight,
            std::vector<GameComponent*> components);
        void exit();
        void run();
    
    private:
        bool isExitRequested = false;
        std::vector<GameComponent*> components;
    
        void initialize();
        void destroyResources();
        void createBackBuffer();
        void prepareFrame();
        void messageHandler();
        void update(float deltaTime);
        float updateInterval(int& frameCount);
        void endFrame();
        void draw();

};