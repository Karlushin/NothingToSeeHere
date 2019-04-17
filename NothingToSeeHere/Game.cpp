#include "Game.h"

void Game::Resize() {
	delete[] pixels;
	window.Resize(width, height);
	pixels = new int[width*height];
}

void Game::Initialize() {
	width = 800;
	height = width*9/16;
	window.Initialize(100, 100, width, height, TEXT("newWindow"));

	pixels = new int[width*height];
}

void Game::Update() {
	for (int y = 0; y != height; ++y) {
		for (int x = 0; x != width; ++x) {
			pixels[x + y * width] = 0x0000FF00;
		}
	}
	window.Present(pixels);
}

void Game::Shutdown() {
	delete[] pixels;
	window.Shutdown();
}
