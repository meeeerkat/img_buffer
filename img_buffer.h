#ifndef _IMG_BUFFER_H_
#define _IMG_BUFFER_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


typedef struct {
  size_t x;
  size_t y;
} img_buffer_point_t, img_buffer_size_t;

typedef struct {
  img_buffer_size_t size;
  size_t buffer_size;
  uint8_t* buffer;
} img_buffer_t;

extern void img_buffer__init(img_buffer_t* ib, img_buffer_size_t size);
extern void img_buffer__clear(img_buffer_t* ib);

extern uint8_t* img_buffer__get_buff(img_buffer_t* ib);

extern void img_buffer__set_pixel(img_buffer_t* ib, img_buffer_point_t p, bool color);
extern void img_buffer__draw_rect(img_buffer_t* ib, img_buffer_point_t topleft, img_buffer_size_t size);

#endif
