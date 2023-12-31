#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>

#include "apple.h"
#include "direction.h"
#include "nake.h"

struct window
{
  SDL_Point dim;
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Event event;
  enum direction key_pressed;
  struct nake* player;
  struct apple* apple;
  bool running;
};

struct window* window_init(char* title, int _w, int _h);
void window_exist(struct window* window);
void window_close(struct window* window);
