#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdio.h>
#include <stdlib.h>

#include "inc/tail.h"

static struct tail* crnt_tail = NULL;
static SDL_Point old_position = {0, 0};
static SDL_Point new_position = {0, 0};

static struct tail* tail_newTail(int _x, int _y)
{
  struct tail* tail = malloc(sizeof(struct tail));
  if (tail == NULL)
  {
    printf("[!] %s:%d tail malloc failed\n", __FILE__, __LINE__);
    return NULL;
  }

  tail->next_tail = NULL;
  tail->position.x = _x;
  tail->position.y = _y;

  return tail;
}

struct tail* tail_appendTail(struct tail* tail, int _x, int _y)
{
  struct tail* new_tail = tail_newTail(_x, _y);
  if (new_tail == NULL)
  {
    printf("[!] %s:%d new tail failed", __FILE__, __LINE__);
    return NULL;
  }

  if (tail == NULL)
  {
    tail = new_tail;
    return tail;
  }

  new_tail->next_tail = tail;

  return new_tail;
}

void tail_update(struct tail* tail, int _x, int _y)
{
  crnt_tail = tail;
  new_position.x = _x;
  new_position.y = _y;

  while (crnt_tail != NULL)
  {
    old_position.x = crnt_tail->position.x;
    old_position.y = crnt_tail->position.y;

    crnt_tail->position.x = new_position.x;
    crnt_tail->position.y = new_position.y;

    new_position.x = old_position.x;
    new_position.y = old_position.y;

    crnt_tail = crnt_tail->next_tail;
  }

  old_position.x = 0;
  old_position.y = 0;
  new_position.x = 0;
  new_position.y = 0;
}

void tail_render(struct tail* tail, SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, 171, 178, 191, SDL_ALPHA_OPAQUE);

  crnt_tail = tail;
  while (crnt_tail != NULL)
  {
    SDL_RenderDrawPoint(renderer, crnt_tail->position.x, crnt_tail->position.y);
    crnt_tail = crnt_tail->next_tail;
  }
}

void tail_freeTail(struct tail* tail)
{
  struct tail* tmp_tail_holder = NULL;
  crnt_tail = tail;

  while (crnt_tail != NULL)
  {
    tmp_tail_holder = crnt_tail->next_tail;
    free(crnt_tail);
    crnt_tail = tmp_tail_holder;
  }
}
