#include "img_buffer/img_buffer.h"
#include <assert.h>
#include <string.h>


void img_buffer__init(img_buffer_t* ib, size_t width, size_t height) {
  assert(
          width % 8 == 0
      &&  height % 8 == 0
  );

  ib->width = width;
  ib->height = height;
  ib->buffer_size = (width * height)/8;
  ib->buffer = malloc(ib->buffer_size);
}

void img_buffer__clear(img_buffer_t* ib) {
  memset(ib->buffer, 0, ib->buffer_size);
}


uint8_t* img_buffer__get_buff(img_buffer_t* ib) {
  return ib->buffer;
}


void img_buffer__set_pixel(img_buffer_t* ib, size_t x, size_t y, bool color) {
  const size_t page_index = y/8;
  const size_t page_size = ib->width;
  uint8_t* byte = &ib->buffer[page_index * page_size + x];

  const uint8_t mask = 1 << (y%8);
  if (color == 0)
    *byte &= ~mask;
  else
    *byte |= mask;
}

void img_buffer__draw_rect(img_buffer_t* ib, size_t topleft_x, size_t topleft_y, size_t width, size_t height, bool color) {
  assert(
          topleft_x + width < ib->width
      &&  topleft_y + height < ib->height
  );

#if 0
  for (size_t x=topleft.x; x < (topleft.x+size.x); x++) {
    uint8_t* addr = ib->buffer + (y*ib->size.x + topleft.x)/8;
    uint8_t mod = topleft.x & 7;
    *addr |= PIXELS_START[mod];
    addr++;
    uint8_t* end_addr = addr + topleft.x
    memset(addr, 0xFF, topleft.x
  }
#endif

  for (size_t x=topleft_x; x < topleft_x+width; x++)
    for (size_t y=topleft_y; y < topleft_y+height; y++)
      img_buffer__set_pixel(ib, x, y, color);
}
