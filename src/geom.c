#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <stdbool.h>

#include "inc/geom.h"

bool intersects(SDL_Rect* rect_one, SDL_Rect* rect_two)
{
  return 
    !(
      rect_one->x + rect_one->w < rect_two->x ||
      rect_one->x > rect_two->x + rect_two->w ||
      rect_one->y + rect_one->h < rect_two->y ||
      rect_one->y > rect_two->y + rect_two->h
    )
  ;
}
