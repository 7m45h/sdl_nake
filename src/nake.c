#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "inc/direction.h"
#include "inc/nake.h"
#include "inc/tail.h"

#define NAKE_SPEED 1

struct nake* nake_newNake(int _x, int _y)
{
  srand(time(NULL));

  struct nake* nake = malloc(sizeof(struct nake));

  if (nake == NULL)
  {
    printf("[!] %s:%d nake malloc failed\n", __FILE__, __LINE__);
    return NULL;
  }

  nake->position.x = _x;
  nake->position.y = _y;
  nake->direction = LEFT;
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

  if (nake->position.x == apple->position.x && nake->position.y == apple->position.y)
  {
    apple->is_eaten = true;
    nake->tail = tail_appendTail(nake->tail, nake->position.x, nake->position.y);
  }

  nake->position.x = (nake->position.x + window_dim->x) % window_dim->x;
  nake->position.y = (nake->position.y + window_dim->y) % window_dim->y;
}

void nake_render(struct nake* nake, SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, 171, 178, 191, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawPoint(renderer, nake->position.x, nake->position.y);
  tail_render(nake->tail, renderer);
}

void nake_freeNake(struct nake* nake)
{
  tail_freeTail(nake->tail);
  free(nake);
}
