#pragma once

#include <stdbool.h>

#include <SDL2/SDL.h>

SDL_Window* sdl_create_window(const char* title, int w, int h);
bool sdl_init(void);
void sdl_quit(void);
