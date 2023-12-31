#pragma once

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>

#include "apple.h"
#include "nake.h"
#include "window.h"

void slm_save(SDL_Point* window_dim, struct apple* apple, struct nake* nake);
void slm_load(SDL_Point* window_dim, struct apple* apple, struct nake* nake);
