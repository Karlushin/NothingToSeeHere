#pragma once

#include "Window/Window.h"

class Game{
	Window window;
	int width;
	int height;
	int* pixels;
public:
	void Resize();
	void Initialize();
	void Update();
	void Shutdown();

};