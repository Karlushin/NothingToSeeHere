#include "../Game.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

Game game;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, int cmdShow) {
	game.Initialize();

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		game.Update();
	}

	game.Shutdown();
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		game.Resize();
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}