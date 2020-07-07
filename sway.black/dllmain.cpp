// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
#include <cstdio>
#include "MinHook.h"
#include "menu.h"
#include "keys.h"
#include "valve_sdk/sdk.hpp"
#include "hooks.h"
#include "helpers/vfunc_hook.hpp"

bool keys::open = true;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

typedef HRESULT(__stdcall* f_EndScene)(IDirect3DDevice9* pDevice);
f_EndScene oEndScene;

typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
WNDPROC oWndProc;
bool unload = false;

HRESULT __stdcall hkEndScene(IDirect3DDevice9* pDevice)
{
    static bool init = true;
    if (init)
    {
        menu::LoadTex(pDevice);

        init = false;
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

        ImGui_ImplWin32_Init(FindWindowA(NULL, "Counter-Strike: Global Offensive"));
        ImGui_ImplDX9_Init(pDevice);
    }

    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    menu::Frame();

    ImGui::EndFrame();
    ImGui::Render();

    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

    return oEndScene(pDevice);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
    if (uMsg == WM_KEYUP)
    {
        switch (wParam)
        {
        case VK_F8:
            unload = true;
            break;
        case VK_INSERT:
            std::cout << "joe : " << keys::open << std::endl;
            keys::open = !keys::open;
            break;
        }
    }

    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

DWORD WINAPI StartCheat(LPVOID param)
{
    HWND  window = FindWindowA(NULL, (char*)"Counter-Strike: Global Offensive");

    oWndProc = (WNDPROC)SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR)WndProc);

    IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);

    if (!pD3D)
        return false;

    D3DPRESENT_PARAMETERS d3dpp{ 0 };
    d3dpp.hDeviceWindow = window, d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD, d3dpp.Windowed = TRUE;

    IDirect3DDevice9* Device = nullptr;
    if (FAILED(pD3D->CreateDevice(0, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &Device)))
    {
        pD3D->Release();
        return false;
    }

    void** pVTable = *reinterpret_cast<void***>(Device);

    if (Device)
        Device->Release(), Device = nullptr;

    if (MH_Initialize() != MH_OK)
        printf("Error initializing MinHook.");
    
    if (MH_CreateHook(pVTable[42], hkEndScene, (void**)&oEndScene) != MH_OK || MH_EnableHook(pVTable[42]) != MH_OK)
        printf("Error while hooking.");

    while (!GetModuleHandleA("serverbrowser.dll"))
        Sleep(200);

    Interfaces::Initialize(); // Init offsets
    NetvarSys::Get().Initialize(); // Init netvars

    hooks::HookCSGO(); // Hook csgo related stuff

    while (!unload)
        Sleep(5);

    hooks::UnHook();

    MH_RemoveHook(MH_ALL_HOOKS);
    MH_Uninitialize();

    FreeConsole();

    (WNDPROC)SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR)oWndProc);

    FreeLibraryAndExitThread((HMODULE)param, -1);
    return true;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        AllocConsole();
        freopen("CONIN$", "r", stdin);
        freopen("CONOUT$", "w", stdout);
        CreateThread(0, 0, StartCheat, hModule, 0, 0);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

