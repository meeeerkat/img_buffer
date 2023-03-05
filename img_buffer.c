#include "img_buffer/img_buffer.h"
#include <assert.h>
#include <string.h>


void img_buffer__init(img_buffer_t* ib, img_buffer_size_t size) {
  assert(
          size.x % 8 == 0
      &&  size.y % 8 == 0
  );

  ib->size = size;
  ib->buffer_size = (size.x * size.y)/8;
  ib->buffer = malloc(ib->buffer_size);
}

void img_buffer__clear(img_buffer_t* ib) {
  memset(ib->buffer, 0, ib->buffer_size);
}


uint8_t* img_buffer__get_buff(img_buffer_t* ib) {
  return ib->buffer;
}


void img_buffer__set_pixel(img_buffer_t* ib, img_buffer_point_t p, bool color) {
  const size_t page_index = p.y/8;
  const size_t page_size = ib->size.x;
  uint8_t* byte = &ib->buffer[page_index * page_size + p.x];

  const uint8_t mask = 1 << (p.y%8);
  if (color == 0)
    *byte &= ~mask;
  else
    *byte |= mask;
}

void img_buffer__draw_rect(img_buffer_t* ib, img_buffer_point_t topleft, img_buffer_size_t size) {
  assert(
          topleft.x + size.x < ib->size.x
      &&  topleft.y + size.y < ib->size.y
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

  img_buffer_point_t p;
  for (p.x=topleft.x; p.x < topleft.x+size.x; p.x++)
    for (p.y=topleft.y; p.y < topleft.y+size.y; p.y++)
      img_buffer__set_pixel(ib, p, 1);
}
