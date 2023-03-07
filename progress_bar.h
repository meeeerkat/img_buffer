#ifndef _IMG_BUFFER_PROGRESS_BAR_H_
#define _IMG_BUFFER_PROGRESS_BAR_H_

#include "img_buffer/img_buffer.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


typedef struct {
  size_t x, y;
  size_t width, height;
  bool color;
  size_t current_dx;
} img_buffer_progress_bar_t;

extern void img_buffer_progress_bar__init(img_buffer_progress_bar_t* bar, size_t x, size_t y, size_t width, size_t height, bool color);
extern void img_buffer_progress_bar__update(img_buffer_t* ib, img_buffer_progress_bar_t* bar, size_t progress_x);

// Helpers
extern void img_buffer_progress_bar__update_percent(img_buffer_t* ib, img_buffer_progress_bar_t* bar, uint8_t progress_percent);
extern void img_buffer_progress_bar__reset(img_buffer_t* ib, img_buffer_progress_bar_t* bar);

#endif
