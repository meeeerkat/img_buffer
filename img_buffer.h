#ifndef _IMG_BUFFER_H_
#define _IMG_BUFFER_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


typedef struct {
  size_t width, height;
  size_t buffer_size;
  uint8_t* buffer;
} img_buffer_t;

extern void img_buffer__init(img_buffer_t* ib, size_t width, size_t height);
extern void img_buffer__clear(img_buffer_t* ib);

extern uint8_t* img_buffer__get_buff(img_buffer_t* ib);

extern void img_buffer__set_pixel(img_buffer_t* ib, size_t x, size_t y, bool color);

extern void img_buffer__draw_rect(img_buffer_t* ib, size_t topleft_x, size_t topleft_y, size_t size_x, size_t size_y, bool color);

#endif
