#include "img_buffer/progress_bar.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <inttypes.h>



void img_buffer_progress_bar__init(img_buffer_progress_bar_t* bar, size_t x, size_t y, size_t width, size_t height, bool color) {
  bar->x = x;
  bar->y = y;
  bar->width = width;
  bar->height = height;
  bar->color = color;
  bar->display_value = false;
  bar->current_dx = 0;
}



void _update_displayed_value(img_buffer_t* ib, img_buffer_progress_bar_t* bar) {
  if (bar->display_value) {
    char value_string[5];
    uint8_t percent = (uint8_t) round(((float)(bar->current_dx*100)) / (bar->width-1));
    if (percent == 100)
      sprintf(value_string, "%" PRIu8 "%%", percent);
    else
      sprintf(value_string, " %" PRIu8 "%%", percent);
    img_buffer__draw_string(ib, bar->value_display_x, bar->value_display_y, bar->color, value_string, 4);
  }
}

void img_buffer_progress_bar__setup_external_value_display(img_buffer_t* ib, img_buffer_progress_bar_t* bar, size_t x, size_t y) {
  assert(
          x+4*8 < ib->width
      &&  y+8   < ib->height
  );

  bar->display_value = true;
  bar->value_display_x = x;
  bar->value_display_y = y;

  _update_displayed_value(ib, bar);
}


void img_buffer_progress_bar__update(img_buffer_t* ib, img_buffer_progress_bar_t* bar, size_t progress_dx) {
  assert(progress_dx < bar->width);

  if (progress_dx < bar->current_dx)
    img_buffer__draw_rect(ib, bar->x+progress_dx, bar->y, bar->current_dx-progress_dx, bar->height, !bar->color);
  else
    img_buffer__draw_rect(ib, bar->x+bar->current_dx, bar->y, progress_dx-bar->current_dx, bar->height, bar->color);

  bar->current_dx = progress_dx;

  _update_displayed_value(ib, bar);
}


void img_buffer_progress_bar__update_percent(img_buffer_t* ib, img_buffer_progress_bar_t* bar, uint8_t progress_percent) {
  assert(progress_percent <= 100);
  img_buffer_progress_bar__update(ib, bar, (uint8_t) round(((float)(progress_percent*bar->width)) / 100));
}

void img_buffer_progress_bar__reset(img_buffer_t* ib, img_buffer_progress_bar_t* bar) {
  img_buffer_progress_bar__update(ib, bar, 0);
}


void img_buffer_progress_bar__clear(img_buffer_t* ib, img_buffer_progress_bar_t* bar) {
  img_buffer__draw_rect(ib, bar->x, bar->y, bar->current_dx, bar->height, !bar->color);
  if (bar->display_value)
    img_buffer__draw_rect(ib, bar->value_display_x, bar->value_display_y, 8*4, 8, !bar->color);

  bar->current_dx = 0;
  bar->display_value = false;
}
