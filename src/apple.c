#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "inc/apple.h"

struct apple* apple_newApple(int _ww, int _wh)
{
  struct apple* apple = malloc(sizeof(struct apple));
  if (apple == NULL)
  {
    printf("[!] %s:%d apple malloc failed\n", __FILE__, __LINE__);
    return NULL;
  }

  apple->position.x = rand() % _ww;
  apple->position.y = rand() % _wh;
  apple->is_eaten = false;

  return apple;
}

void apple_update(struct apple* apple, int _ww, int _wh)
{
  if (apple->is_eaten)
  {
    apple->position.x = rand() % _ww;
    apple->position.y = rand() % _wh;
    apple->is_eaten = false;
  }
}

void apple_render(struct apple* apple, SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, 190, 80, 70, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawPoint(renderer, apple->position.x, apple->position.y);
}

void apple_freeApple(struct apple* apple)
{
  free(apple);
}