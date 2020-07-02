#pragma once
#include <d3d9.h>

namespace menu
{
	extern IDirect3DTexture9* aim;
	extern IDirect3DTexture9* visual;
	extern IDirect3DTexture9* skins;
	extern IDirect3DTexture9* misc;
	extern IDirect3DTexture9* config;
	extern IDirect3DTexture9* lua;

	void LoadTex(IDirect3DDevice9* device);
	void Frame();
	extern int tab;

	namespace tabs
	{
		void aim();
		void visual();
		void skins();
		void misc();
		void config();
		void lua();
	}
}