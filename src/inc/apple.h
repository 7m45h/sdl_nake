#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

struct apple
{
  SDL_Point position;
};

struct apple* apple_newApple(SDL_Point* window_dim);
void apple_relocate(struct apple* apple, SDL_Point* window_dim);
void apple_respawn(struct apple* apple, SDL_Point* window_dim);
void apple_render(struct apple* apple, SDL_Renderer* renderer);
void apple_freeApple(struct apple* apple);
