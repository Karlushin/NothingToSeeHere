#pragma once

#include <Windows.h>
#include <d3d11.h>

class Window {
	HWND hWnd;

	ID3D11Device* dev;
	ID3D11DeviceContext* con;
	IDXGISwapChain* swapChain;
	ID3D11Buffer* backBuffer;
	int width;
	int height;
	void InitializeGraphics();
public:
	void Initialize(int xPos, int yPos, int windowWidth, int windowHeight, const TCHAR* windowName);
	void Shutdown();
	void Present(int* pixels);
	void Resize(int& retWidth, int& retHeight);
};