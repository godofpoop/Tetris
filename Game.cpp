#include "Game.h"
#include "Window.h"

Game::Game()
{
}
void Game::run()
{
	glfwInit();
	Window win;
	win.createWindow("tetris", 400, 400, 0, 1);
	glewInit();
	init();
	double frame_cap = 1.0 / 60.0;
	input = Input(win.window, 400, 400);
	time = get_time();
	while (win.shouldClose() != 1) {
		bool can_render = false;

		double time_2 = get_time();
		passed = time_2 - time;
		unprocessed += passed;
		frame_time += passed;

		time = time_2;

		while (unprocessed >= frame_cap) {
			delta = (get_time() - lastFrameTime);
			if (delta > 100) delta = 0;
			lastFrameTime = get_time();
			unprocessed -= frame_cap;
			can_render = true;

			update();
			input.update();
			if (frame_time >= 1.0) {

				frame_time = 0;


				std::cout << frames << "\n";
				frames = 0;
			}
		}
		if (can_render) {
			glClearColor(.3f, .3f, .3f, 1);
			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			render();
			win.swapBuffers(0);
			glfwPollEvents();

			frames++;
		}

	}
	glfwDestroyWindow(win.window);
	glfwTerminate();
}

Game::~Game()
{
}
