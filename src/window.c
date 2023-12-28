#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "inc/direction.h"
#include "inc/nake.h"
#include "inc/window.h"

static const int fps_cap = 1;
static const int frame_delay = 1000 / fps_cap;

static Uint32 time_frameStart = 0;
static Uint32 time_frameEnd   = 0;
static Uint32 time_frameTime  = 0;

static void window_handleEvents(struct window* window)
{
  while (SDL_PollEvent(&window->event))
  {
    switch (window->event.type)
    {
      case SDL_QUIT:
      window->running = false;
      break;

      case SDL_KEYDOWN:
      switch (window->event.key.keysym.sym)
      {
        case SDLK_q:
        window->running = false;
        break;

        case SDLK_UP:
        window->key_pressed = UP;
        break;

        case SDLK_DOWN:
        window->key_pressed = DOWN;
        break;

        case SDLK_LEFT:
        window->key_pressed = LEFT;
        break;

        case SDLK_RIGHT:
        window->key_pressed = RIGHT;
        break;
      }
      break;
    }
  }
}

static void window_update(struct window* window)
{
  nake_update(window->player, window->key_pressed);
}

static void window_render(struct window* window)
{
  SDL_SetRenderDrawColor(window->renderer, 29, 29, 29, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(window->renderer);

  nake_render(window->player, window->renderer);

  SDL_RenderPresent(window->renderer);
}

struct window* window_init(char* title, int _w, int _h)
{
  int sdl_status = SDL_Init(SDL_INIT_VIDEO);
  if (sdl_status != 0)
  {
    printf("[!] %s:%d %s\n", __FILE__, __LINE__, SDL_GetError());
    return NULL;
  }

  struct window* window = malloc(sizeof(struct window));
  if (window == NULL)
  {
    printf("[!] %s:%d window malloc failed\n", __FILE__, __LINE__);
    SDL_Quit();
    return NULL;
  }

  window->width = _w;
  window->height = _h;

  window->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _w, _h, 0);
  if (window->window == NULL)
  {
    printf("[!] %s:%d %s\n", __FILE__, __LINE__, SDL_GetError());
    free(window);
    SDL_Quit();
    return NULL;
  }

  window->renderer = SDL_CreateRenderer(window->window, -1, 0);
  if (window->renderer == NULL)
  {
    printf("[!] %s:%d %s\n", __FILE__, __LINE__, SDL_GetError());
    SDL_DestroyWindow(window->window);
    free(window);
    SDL_Quit();
    return NULL;
  }

  window->key_pressed = LEFT;

  window->player = nake_newNake(_w/2, _h/2);
  if (window->player == NULL)
  {
    printf("[!] %s:%d player init failed\n", __FILE__, __LINE__);
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);
    free(window);
    SDL_Quit();
    return NULL;
  }

  window->running = false;

  return window;
}

void window_exist(struct window* window)
{
  window->running = true;

  while (window->running)
  {
    time_frameStart = SDL_GetTicks();

    window_handleEvents(window);
    window_update(window);
    window_render(window);

    time_frameEnd = SDL_GetTicks();
    time_frameTime = time_frameStart - time_frameEnd;

    if (time_frameTime < frame_delay)
    {
      SDL_Delay(frame_delay - time_frameTime);
    }
  }
}

void window_close(struct window* window)
{
  nake_freeNake(window->player);
  SDL_DestroyRenderer(window->renderer);
  SDL_DestroyWindow(window->window);

  free(window);

  SDL_Quit();
}
