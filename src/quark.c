#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengles2.h>
#include <stdlib.h>

#include "quark.h"
#include "sdl.h"

quark_t quark;

void quit(void);
void render_tmp(void);
void run(void);
void setup(void);

void quit(void)
{
	LOG_INFO("quitting quark...");
	sdl_quit();
}

void render_tmp(void)
{
	glViewport(0, 0, quark.win_w, quark.win_h);

	glClearColor(0.0, 0.0, 0.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_SCISSOR_TEST);
	int bar_h = 32;
	glScissor(0, quark.win_h - bar_h, quark.win_w, bar_h);
	glClearColor(0.25, 0.25, 0.30, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);

	SDL_GL_SwapWindow(quark.win);
}

void run(void)
{
	quark.running = true;
	LOG_INFO("starting quark...");

	SDL_Event ev;

	while (quark.running) {
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT)
				quark.running = false;

			if (ev.type == SDL_WINDOWEVENT_RESIZED) {
				quark.win_w = ev.window.data1;
				quark.win_h = ev.window.data2;
			}
		}

		render_tmp();
		SDL_Delay(10);
	}
}

void setup(void)
{
	sdl_init();
	quark.win = sdl_create_window("quark", 800, 600);
	if (!quark.win) {
		LOG_ERROR("failed to create quark window");
		exit(EXIT_FAILURE);
	}
	else {
		LOG_PASS("created SDL window");
	}
	quark.win_w = 800;
	quark.win_h = 600;

	/* create OpenGL context */
	quark.gl = SDL_GL_CreateContext(quark.win);
	if (!quark.gl) {
		LOG_ERROR("failed to create GL context");
		exit(EXIT_FAILURE);
	}
	else {
		LOG_PASS("created OpenGL ES context");
	}
}

int main(int argc, char** argv)
{
	(void) argc;
	(void) argv;

	setup();
	run();
	quit();

	return EXIT_SUCCESS;
}
