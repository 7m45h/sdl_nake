#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdio.h>
#include <stdlib.h>

#include "inc/tail.h"

static const char tail_texture_path[] = "./assets/nake_texture_16.png";
static const int tail_texture_dim     = 16;
static const int tail_texture_offset  = 8;

static SDL_Texture* tail_texture = NULL;
static SDL_Rect tail_src_rect = {0, 0, tail_texture_dim, tail_texture_dim};

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
  tail->dst_rect.x = _x - tail_texture_offset;
  tail->dst_rect.y = _y - tail_texture_offset;
  tail->dst_rect.w = tail_texture_dim;
  tail->dst_rect.h = tail_texture_dim;

  return tail;
}

int tail_init(SDL_Renderer* renderer)
{
  tail_texture = IMG_LoadTexture(renderer, tail_texture_path);
  if (tail_texture == NULL) {
    printf("[!] %s:%d %s\n", __FILE__, __LINE__, IMG_GetError());
    return 1;
  }

  return 0;
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
    crnt_tail->dst_rect.x = new_position.x - tail_texture_offset;
    crnt_tail->dst_rect.y = new_position.y - tail_texture_offset;

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
  crnt_tail = tail;
  while (crnt_tail != NULL)
  {
    SDL_RenderCopy(renderer, tail_texture, &tail_src_rect, &crnt_tail->dst_rect);
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

void tail_deInit(void)
{
  SDL_DestroyTexture(tail_texture);
}
