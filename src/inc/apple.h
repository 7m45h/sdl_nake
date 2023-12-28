#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdbool.h>

struct apple
{
  SDL_Point position;
  bool is_eaten;
};

struct apple* apple_newApple(int _ww, int _wh);
void apple_update(struct apple* apple, int _ww, int _wh);
void apple_render(struct apple* apple, SDL_Renderer* renderer);
void apple_freeApple(struct apple* apple);