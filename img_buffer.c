#include "img_buffer/img_buffer.h"
#include "img_buffer/font8x8_basic.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>


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


void img_buffer__draw_char(img_buffer_t* ib, size_t topleft_x, size_t topleft_y, bool color, char c) {
  assert(
          c < 128
      &&  topleft_x+8 < ib->width
      &&  topleft_y+8 < ib->height
  );

  char* bitmap = font8x8_basic[(uint8_t)c];

  for (size_t x=0; x < 8; x++) {
    for (size_t y=0; y < 8; y++) {
      const bool is_in_char = (bitmap[y] >> x) & 1;
      img_buffer__set_pixel(ib, topleft_x+x, topleft_y+y, is_in_char ? color : !color);
    }
  }
}


void img_buffer__draw_string(img_buffer_t* ib, size_t topleft_x, size_t topleft_y, bool color, char* s, size_t s_size) {
  for (size_t i=0; i < s_size; i++)
    img_buffer__draw_char(ib, topleft_x+i*8, topleft_y, color, s[i]);
}
