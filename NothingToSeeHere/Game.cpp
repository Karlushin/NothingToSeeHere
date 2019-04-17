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

	window.Present(pixels);
}

void Game::Shutdown() {
	delete[] pixels;
	window.Shutdown();
}
