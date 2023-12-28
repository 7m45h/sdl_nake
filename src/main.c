#include <stdio.h>

#include "inc/window.h"

int main(void)
{
  struct window* window = window_init("sdl_nake", 640, 360);
  if (window == NULL)
  {
    printf("[!] %s:%d window init failed", __FILE__, __LINE__);
    return 1;
  }

  window_exist(window);
  window_close(window);

  return 0;
}
