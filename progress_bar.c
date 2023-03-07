#include "img_buffer/progress_bar.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>



void img_buffer_progress_bar__init(img_buffer_progress_bar_t* bar, size_t x, size_t y, size_t width, size_t height, bool color) {
  bar->x = x;
  bar->y = y;
  bar->width = width;
  bar->height = height;
  bar->color = color;
  bar->current_dx = 0;
}


void img_buffer_progress_bar__update(img_buffer_t* ib, img_buffer_progress_bar_t* bar, size_t progress_dx) {
  assert(progress_dx < bar->width);

  if (progress_dx < bar->current_dx)
    img_buffer__draw_rect(ib, bar->x+progress_dx, bar->y, bar->current_dx-progress_dx, bar->height, !bar->color);
  else
    img_buffer__draw_rect(ib, bar->x+bar->current_dx, bar->y, progress_dx-bar->current_dx, bar->height, bar->color);

  bar->current_dx = progress_dx;
}


void img_buffer_progress_bar__update_percent(img_buffer_t* ib, img_buffer_progress_bar_t* bar, uint8_t progress_percent) {
  assert(progress_percent <= 100);
  img_buffer_progress_bar__update(ib, bar, (progress_percent*bar->width) / 100);
}

void img_buffer_progress_bar__reset(img_buffer_t* ib, img_buffer_progress_bar_t* bar) {
  img_buffer_progress_bar__update(ib, bar, 0);
}
