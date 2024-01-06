#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "inc/window.h"

int main(void)
{
  srand(time(NULL));

  struct window* window = window_init("sdl_nake", 640, 360);
  if (window == NULL)
  {
    printf("[!] %s:%d window init failed\n", __FILE__, __LINE__);
    return 1;
  }

  window_exist(window);
  window_close(window);

  return 0;
}
