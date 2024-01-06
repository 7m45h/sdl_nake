#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <stdbool.h>

bool intersects(SDL_Rect* rect_one, SDL_Rect* rect_two);
