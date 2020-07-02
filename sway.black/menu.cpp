#include "menu.h"
#include "imgui/imgui.h"
#include "keys.h"
#include "imgui/imgui_internal.h"
#include <d3d9.h>
#include <d3dx9tex.h>
#include "textures.h"

int menu::tab = 0;
IDirect3DTexture9* menu::aim = 0;
IDirect3DTexture9* menu::visual = 0;
IDirect3DTexture9* menu::skins = 0;
IDirect3DTexture9* menu::misc = 0;
IDirect3DTexture9* menu::config = 0;
IDirect3DTexture9* menu::lua = 0;

void menu::Frame()
{
	ImGuiIO io = ImGui::GetIO();
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 0.0f;
	style.Colors[ImGuiCol_WindowBg] = ImColor(42, 42, 42, 255);
	style.WindowPadding = ImVec2(0, 0);

	ImGui::Begin("sway.black", &keys::open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
	ImGui::SetWindowSize("sway.black", ImVec2(835, 600));
	ImVec2 pos = ImGui::GetWindowPos();
	ImVec2 size = ImGui::GetWindowSize();

	ImGui::GetWindowDrawList()->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + 80),
		ImColor(79, 79, 79, 255));
	ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(pos.x, pos.y + 80), ImVec2(pos.x + size.x, pos.y + 82),
		ImColor(138, 138, 138, 255));
	
	ImGui::GetWindowDrawList()->AddText(ImVec2(pos.x + 35, pos.y + 20), ImColor(255, 255, 255, 255), "sway.black");
	
	bool hovered, held;
	if (ImGui::ButtonBehavior(ImRect(pos.x + 200, pos.y, pos.x + 305, pos.y + 85), ImGui::GetID("aim"), &hovered, &held))
		tab = 0;
	if (ImGui::ButtonBehavior(ImRect(pos.x + 305, pos.y, pos.x + 410, pos.y + 85), ImGui::GetID("visuals"), &hovered, &held))
		tab = 1;
	if (ImGui::ButtonBehavior(ImRect(pos.x + 410, pos.y, pos.x + 515, pos.y + 85), ImGui::GetID("skins"), &hovered, &held))
		tab = 2;
	if (ImGui::ButtonBehavior(ImRect(pos.x + 515, pos.y, pos.x + 620, pos.y + 85), ImGui::GetID("misc"), &hovered, &held))
		tab = 3;
	if (ImGui::ButtonBehavior(ImRect(pos.x + 620, pos.y, pos.x + 725, pos.y + 85), ImGui::GetID("config"), &hovered, &held))
		tab = 4;
	if (ImGui::ButtonBehavior(ImRect(pos.x + 725, pos.y, pos.x + 830, pos.y + 85), ImGui::GetID("lua"), &hovered, &held))
		tab = 5;

	switch (tab)
	{
	case 0:
		tabs::aim();
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(pos.x + 200, pos.y), ImVec2(pos.x + 305, pos.y + 88), ImColor(42, 42, 42));
		break;
	case 1:
		tabs::visual();
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(pos.x + 305, pos.y), ImVec2(pos.x + 410, pos.y + 88), ImColor(42, 42, 42));
		break;
	case 2:
		tabs::skins();
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(pos.x + 410, pos.y), ImVec2(pos.x + 515, pos.y + 88), ImColor(42, 42, 42));
		break;
	case 3:
		tabs::misc();
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(pos.x + 515, pos.y), ImVec2(pos.x + 620, pos.y + 88), ImColor(42, 42, 42));
		break;
	case 4:
		tabs::config();
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(pos.x + 620, pos.y), ImVec2(pos.x + 725, pos.y + 88), ImColor(42, 42, 42));
		break;
	case 5:
		tabs::lua();
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(pos.x + 725, pos.y), ImVec2(pos.x + 830, pos.y + 88), ImColor(42, 42, 42));
		break;
	}

	ImGui::GetWindowDrawList()->AddImage(aim, ImVec2(pos.x + 220, pos.y + 10), ImVec2(pos.x + 285, pos.y + 75));
	ImGui::GetWindowDrawList()->AddImage(visual, ImVec2(pos.x + 325, pos.y + 10), ImVec2(pos.x + 390, pos.y + 75));
	ImGui::GetWindowDrawList()->AddImage(skins, ImVec2(pos.x + 410, pos.y), ImVec2(pos.x + 515, pos.y + 85));
	ImGui::GetWindowDrawList()->AddImage(misc, ImVec2(pos.x + 515, pos.y), ImVec2(pos.x + 620, pos.y + 85));
	ImGui::GetWindowDrawList()->AddImage(config, ImVec2(pos.x + 620, pos.y), ImVec2(pos.x + 725, pos.y + 85));
	ImGui::GetWindowDrawList()->AddImage(lua, ImVec2(pos.x + 725, pos.y), ImVec2(pos.x + 830, pos.y + 85));


	ImGui::End();
}

namespace menu::tabs
{
	void aim()
	{

	}

	void visual()
	{

	}

	void skins()
	{

	}
	
	void misc()
	{

	}
	
	void config()
	{

	}
	
	void lua()
	{

	}
}

void menu::LoadTex(IDirect3DDevice9* device)
{
	D3DXCreateTextureFromFileInMemory(device, tex::aim_png, tex::aim_png_size, &menu::aim);
	D3DXCreateTextureFromFileInMemory(device, tex::visuals_png, tex::visuals_png_size, &menu::visual);
	D3DXCreateTextureFromFileInMemory(device, tex::skins_png, tex::skins_png_size, &menu::skins);
	D3DXCreateTextureFromFileInMemory(device, tex::misc_png, tex::misc_png_size, &menu::misc);
	D3DXCreateTextureFromFileInMemory(device, tex::config_png, tex::config_png_size, &menu::config);
	D3DXCreateTextureFromFileInMemory(device, tex::lua_png, tex::lua_png_size, &menu::lua);
}