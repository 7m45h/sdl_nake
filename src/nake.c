#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "inc/apple.h"
#include "inc/direction.h"
#include "inc/geom.h"
#include "inc/nake.h"
#include "inc/tail.h"

static const char nake_texture_path[] = "./assets/nake_texture_16.png";
static const int nake_texture_dim     = 16;
static const int nake_texture_offset  = 8;
static const int nake_speed           = 20;

struct nake* nake_newNake(SDL_Renderer* renderer, int _x, int _y)
{
  struct nake* nake = malloc(sizeof(struct nake));

  if (nake == NULL)
  {
    printf("[!] %s:%d nake malloc failed\n", __FILE__, __LINE__);
    return NULL;
  }

  nake->position.x = _x;
  nake->position.y = _y;
  nake->direction = LEFT;
  nake->src_rect.x = 0;
  nake->src_rect.y = 0;
  nake->src_rect.w = nake_texture_dim;
  nake->src_rect.h = nake_texture_dim;
  nake->dst_rect.x = _x;
  nake->dst_rect.y = _y;
  nake->dst_rect.w = nake_texture_dim;
  nake->dst_rect.h = nake_texture_dim;

  nake->texture = IMG_LoadTexture(renderer, nake_texture_path);
  if (nake->texture == NULL)
  {
    printf("[!] %s:%d %s\n", __FILE__, __LINE__, IMG_GetError());
    free(nake);
    return NULL;
  }

  nake->tail = NULL;

  return nake;
}

void nake_update(struct nake* nake, struct apple* apple, enum direction key_pressed, SDL_Point* window_dim)
{
  switch (key_pressed)
  {
    case UP:
    if (nake->direction != DOWN)
    {
      nake->direction = UP;
    }
    break;

    case DOWN:
    if (nake->direction != UP)
    {
      nake->direction = DOWN;
    }
    break;

    case LEFT:
    if (nake->direction != RIGHT)
    {
      nake->direction = LEFT;
    }
    break;

    case RIGHT:
    if (nake->direction != LEFT)
    {
      nake->direction = RIGHT;
    }
    break;
  }

  tail_update(nake->tail, nake->position.x, nake->position.y);

  switch (nake->direction)
  {
    case UP:
    nake->position.y -= nake_speed;
    break;

    case DOWN:
    nake->position.y += nake_speed;
    break;

    case LEFT:
    nake->position.x -= nake_speed;
    break;

    case RIGHT:
    nake->position.x += nake_speed;
    break;
  }

  nake->position.x = (nake->position.x + window_dim->x) % window_dim->x;
  nake->position.y = (nake->position.y + window_dim->y) % window_dim->y;
  nake->dst_rect.x = nake->position.x - nake_texture_offset;
  nake->dst_rect.y = nake->position.y - nake_texture_offset;

  if (intersects(&nake->dst_rect, &apple->dst_rect))
  {
    apple_respawn(apple, window_dim);
    nake->tail = tail_appendTail(nake->tail, nake->position.x, nake->position.y);
  }
}

void nake_render(struct nake* nake, SDL_Renderer* renderer)
{
  SDL_RenderCopy(renderer, nake->texture, &nake->src_rect, &nake->dst_rect);
  tail_render(nake->tail, renderer);
}

void nake_freeNake(struct nake* nake)
{
  SDL_DestroyTexture(nake->texture);
  tail_freeTail(nake->tail);
  free(nake);
}
