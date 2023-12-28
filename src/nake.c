#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <stdio.h>
#include <stdlib.h>

#include "inc/direction.h"
#include "inc/nake.h"

#define NAKE_SPEED 1

struct nake* nake_newNake(int _x, int _y)
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

  return nake;
}

void nake_update(struct nake* nake, enum direction key_pressed, int _ww, int _wh)
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

  switch (nake->direction)
  {
    case UP:
    nake->position.y -= NAKE_SPEED;
    break;

    case DOWN:
    nake->position.y += NAKE_SPEED;
    break;

    case LEFT:
    nake->position.x -= NAKE_SPEED;
    break;

    case RIGHT:
    nake->position.x += NAKE_SPEED;
    break;
  }

  nake->position.x = (nake->position.x + _ww) % _ww;
  nake->position.y = (nake->position.y + _wh) % _wh;
}

void nake_render(struct nake* nake, SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, 171, 178, 191, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawPoint(renderer, nake->position.x, nake->position.y);
}

void nake_freeNake(struct nake* nake)
{
  free(nake);
}
