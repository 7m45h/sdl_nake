#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdio.h>
#include <stdlib.h>

#include "inc/apple.h"

static const char appe_texture_path[] = "./assets/apple_texture_16.png";
static const int apple_texture_dim    = 16;
static const int apple_texture_offset = 8;

struct apple* apple_newApple(SDL_Renderer* renderer, SDL_Point* window_dim)
{
  struct apple* apple = malloc(sizeof(struct apple));
  if (apple == NULL)
  {
    printf("[!] %s:%d apple malloc failed\n", __FILE__, __LINE__);
    return NULL;
  }

  apple->position.x = rand() % window_dim->x;
  apple->position.y = rand() % window_dim->y;
  apple->src_rect.x = 0;
  apple->src_rect.y = 0;
  apple->src_rect.w = apple_texture_dim;
  apple->src_rect.h = apple_texture_dim;
  apple->dst_rect.x = apple->position.x - apple_texture_offset;
  apple->dst_rect.y = apple->position.y - apple_texture_offset;
  apple->dst_rect.w = apple_texture_dim;
  apple->dst_rect.h = apple_texture_dim;
  apple->texture = IMG_LoadTexture(renderer, appe_texture_path);
  if (apple->texture == NULL)
  {
    printf("[!] %s:%d %s\n", __FILE__, __LINE__, IMG_GetError());
    free(apple);
    return NULL;
  }

  return apple;
}

void apple_relocate(struct apple* apple, SDL_Point* window_dim)
{
  apple->position.x = (apple->position.x + window_dim->x) % window_dim->x;
  apple->position.y = (apple->position.y + window_dim->y) % window_dim->y;
  apple->dst_rect.x = apple->position.x - apple_texture_offset;
  apple->dst_rect.y = apple->position.y - apple_texture_offset;
}

void apple_respawn(struct apple* apple, SDL_Point* window_dim)
{
  apple->position.x = rand() % window_dim->x;
  apple->position.y = rand() % window_dim->y;
  apple->dst_rect.x = apple->position.x - apple_texture_offset;
  apple->dst_rect.y = apple->position.y - apple_texture_offset;
}

void apple_render(struct apple* apple, SDL_Renderer* renderer)
{
  SDL_RenderCopy(renderer, apple->texture, &apple->src_rect, &apple->dst_rect);
}

void apple_freeApple(struct apple* apple)
{
  SDL_DestroyTexture(apple->texture);
  free(apple);
}
