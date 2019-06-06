#pragma once
#define GLEW_STATIC
#include "GL/glew.h"
#include <chrono>
#include <ctime>
#include <iostream>
#include "Input.h"

class Game
{
public:
	Game();
	void run();
	virtual void update() = 0;
	virtual void init() = 0;
	virtual void render() = 0;
	~Game();
private:
	double get_time() {
		return (double)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count() / (double)1000000000L;
	}
	double unprocessed = 0;
	double frame_time = 0;
	int frames = 0;
	double passed = 0;
	double lastFrameTime = 0;
	double time = static_cast<double>(std::clock());
protected:
	double delta = 0;
	Input input;
};

