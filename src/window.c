#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "inc/apple.h"
#include "inc/direction.h"
#include "inc/nake.h"
#include "inc/tail.h"
#include "inc/window.h"

static const float fps_cap = 10;
static const float frame_delay = 1000 / fps_cap;

static Uint64 time_frameStart = 0;
static Uint64 time_frameEnd   = 0;
static Uint64 time_frameTime  = 0;

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

        case SDLK_q:
        window->running = false;
        break;
      }
      break;

      case SDL_WINDOWEVENT:
      switch (window->event.window.event)
      {
        case SDL_WINDOWEVENT_SIZE_CHANGED:
        window->dim.x = window->event.window.data1;
        window->dim.y = window->event.window.data2;
        apple_relocate(window->apple, &window->dim);
        break;
      }
      break;
    }
  }
}

static void window_update(struct window* window)
{
  nake_update(window->player, window->apple, window->key_pressed, &window->dim);
}

static void window_render(struct window* window)
{
  SDL_SetRenderDrawColor(window->renderer, 29, 29, 29, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(window->renderer);

  apple_render(window->apple, window->renderer);
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

  int img_status = IMG_Init(IMG_INIT_PNG);
  if (img_status == 0)
  {
    printf("[!] %s:%d %s\n", __FILE__, __LINE__, IMG_GetError());
    SDL_Quit();
    return NULL;
  }

  struct window* window = malloc(sizeof(struct window));
  if (window == NULL)
  {
    printf("[!] %s:%d window malloc failed\n", __FILE__, __LINE__);
    IMG_Quit();
    SDL_Quit();
    return NULL;
  }

  window->dim.x = _w;
  window->dim.y = _h;

  window->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _w, _h, SDL_WINDOW_RESIZABLE);
  if (window->window == NULL)
  {
    printf("[!] %s:%d %s\n", __FILE__, __LINE__, SDL_GetError());
    free(window);
    IMG_Quit();
    SDL_Quit();
    return NULL;
  }

  window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (window->renderer == NULL)
  {
    printf("[!] %s:%d %s\n", __FILE__, __LINE__, SDL_GetError());
    SDL_DestroyWindow(window->window);
    free(window);
    IMG_Quit();
    SDL_Quit();
    return NULL;
  }

  window->key_pressed = LEFT;

  window->player = nake_newNake(window->renderer, _w/2, _h/2);
  if (window->player == NULL)
  {
    printf("[!] %s:%d player init failed\n", __FILE__, __LINE__);
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);
    free(window);
    IMG_Quit();
    SDL_Quit();
    return NULL;
  }

  int tail_status = tail_init(window->renderer);
  if (tail_status == 1)
  {
    printf("[!] %s:%d tail init failed\n", __FILE__, __LINE__);
    nake_freeNake(window->player);
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);
    free(window);
    IMG_Quit();
    SDL_Quit();
    return NULL;
  }

  window->apple = apple_newApple(window->renderer, &window->dim);
  if (window->apple == NULL)
  {
    printf("[!] %s:%d apple init failed\n", __FILE__, __LINE__);
    nake_freeNake(window->player);
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);
    free(window);
    IMG_Quit();
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
    time_frameStart = SDL_GetPerformanceCounter();

    window_handleEvents(window);
    window_update(window);
    window_render(window);

    time_frameEnd = SDL_GetPerformanceCounter();
    time_frameTime = (time_frameEnd - time_frameStart) / (SDL_GetPerformanceFrequency() * 1000);

    SDL_Delay(frame_delay - time_frameTime);
  }
}

void window_close(struct window* window)
{
  nake_freeNake(window->player);
  tail_deInit();
  apple_freeApple(window->apple);
  SDL_DestroyRenderer(window->renderer);
  SDL_DestroyWindow(window->window);

  free(window);

  IMG_Quit();
  SDL_Quit();
}
