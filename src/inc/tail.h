#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

struct tail
{
  struct tail* next_tail;
  SDL_Point position;
};

struct tail* tail_appendTail(struct tail* tail, int _x, int _y);
void tail_update(struct tail* tail, int _x, int _y);
void tail_render(struct tail* tail, SDL_Renderer* renderer);
void tail_freeTail(struct tail* tail);
