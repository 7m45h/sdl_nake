#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include "apple.h"
#include "direction.h"
#include "tail.h"

struct nake
{
  SDL_Point position;
  enum direction direction;
  struct tail* tail;
};

struct nake* nake_newNake(int _x, int _y);
void nake_update(struct nake* nake, struct apple* apple, enum direction key_pressed, SDL_Point* window_dim);
void nake_render(struct nake* nake, SDL_Renderer* renderer);
void nake_freeNake(struct nake* nake);
