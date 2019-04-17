#include "Window.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

const TCHAR* className = TEXT("NothingToSeeHere");

void Window::Initialize(int xPos, int yPos, int windowWidth, int windowHeight, const TCHAR* windowName) {
	HINSTANCE hInstance = GetModuleHandle(0);

	WNDCLASS wndClass;
	ZeroMemory(&wndClass, sizeof(WNDCLASS));
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = className;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);

	RegisterClass(&wndClass);

	RECT rect;
	rect.left = xPos;
	rect.top = yPos;
	rect.right = rect.left + windowWidth;
	rect.bottom = rect.top + windowHeight;
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;
	static const DWORD style = WS_OVERLAPPEDWINDOW;
	AdjustWindowRect(&rect, style, FALSE);
	hWnd = CreateWindow(className, windowName, style,
		rect.left, rect.top, width, height,
		0, 0, hInstance, 0);

	UnregisterClass(className, 0);

	InitializeGraphics();

	ShowWindow(hWnd, 10);

}

void Window::InitializeGraphics() {
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.Windowed = true;

	HRESULT result = D3D11CreateDeviceAndSwapChain(0, D3D_DRIVER_TYPE_HARDWARE, 0, 0, 0,
		0, D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &dev, 0, &con);

	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
}

void Window::Shutdown() {
	backBuffer->Release();
	swapChain->Release();
	con->Release();
	dev->Release();
}

void Window::Present(int* pixels) {
	con->UpdateSubresource(backBuffer, 0, 0, pixels, sizeof(int)*width, 1);
	swapChain->Present(1, 0);
}

void Window::Resize(int& retWidth, int& retHeight) {
	RECT rect;
	GetWindowRect(hWnd, &rect);
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;
	retWidth = width;
	retHeight = height;
	backBuffer->Release();
	swapChain->ResizeBuffers(2, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
}