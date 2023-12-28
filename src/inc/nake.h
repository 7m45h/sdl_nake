#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include "direction.h"

struct nake
{
  SDL_Point position;
  enum direction direction;
};

struct nake* nake_newNake(int _x, int _y);
void nake_update(struct nake* nake, enum direction key_pressed);
void nake_render(struct nake* nake, SDL_Renderer* renderer);
void nake_freeNake(struct nake* nake);
