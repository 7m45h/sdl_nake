#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>

struct window
{
  int width;
  int height;
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Event event;
  bool running;
};

struct window* window_init(char* title, int _w, int _h);
void window_exist(struct window* window);
void window_close(struct window* window);
