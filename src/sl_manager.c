#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <stdio.h>
#include <stdlib.h>

#include "inc/apple.h"
#include "inc/nake.h"
#include "inc/sl_manager.h"
#include "inc/tail.h"

#define SAVE_FILE_PATH "./sdl_nake.save"

void slm_save(SDL_Point* window_dim, struct apple* apple, struct nake* nake)
{
  FILE* save_file = fopen(SAVE_FILE_PATH, "w");
  if (save_file == NULL)
  {
    printf("[!] %s:%d fopen failed\n", __FILE__, __LINE__);
    printf("[!] %s:%d save failed\n", __FILE__, __LINE__);
    return;
  }

  fwrite(&window_dim, sizeof(SDL_Point), 1, save_file);
  fwrite(&apple->position, sizeof(SDL_Point), 1, save_file);
  fwrite(&nake->position, sizeof(SDL_Point), 1, save_file);

  struct tail* crnt_tail = nake->tail;
  while (crnt_tail != NULL)
  {
    fwrite(&crnt_tail->position, sizeof(SDL_Point), 1, save_file);
    crnt_tail = crnt_tail->next_tail;
  }

  fclose(save_file);
  printf("[!] %s:%d save completed\n", __FILE__, __LINE__);
}

void slm_load(SDL_Point* window_dim, struct apple* apple, struct nake* nake)
{
  FILE* save_file = fopen(SAVE_FILE_PATH, "r");
  if (save_file == NULL)
  {
    printf("[!] %s:%d fopen failed\n", __FILE__, __LINE__);
    printf("[!] %s:%d load failed\n", __FILE__, __LINE__);
    return;
  }

  fread(&window_dim, sizeof(SDL_Point), 1, save_file);
  fread(&apple->position, sizeof(SDL_Point), 1, save_file);
  fread(&nake->position, sizeof(SDL_Point), 1, save_file);

  tail_freeTail(nake->tail);
  SDL_Point save_data = {0, 0};
  while (fread(&save_data, sizeof(SDL_Point), 1, save_file))
  {
    nake->tail = tail_appendTail(nake->tail, save_data.x, save_data.y);
  }

  fclose(save_file);
  printf("[!] %s:%d load completed\n", __FILE__, __LINE__);
}
