#include "cmn_utils.h"

#include <stdio.h>
#include <string.h>

//--------------------------------------------------------- MIN/MAX
int min(int a, int b) {
  return a < b ? a : b;
}

int max(int a, int b) {
  return a > b ? a : b;
}

//--------------------------------------------------------- STRING HANDLING
char* to_str(char* dest, size_t size, int v) {
  if(size > 0) {sprintf(dest, "%d", v);}
  return dest;
}

char* str_app(char* dest, size_t size, const char* app) {
  if(size > 0) {
    //Move to first null terminator
    while(*dest != '\0') {
      ++dest;
    }

    while(*app != '\0') {
      *dest = *app;
      ++dest;
      ++app;
    }
    *dest = '\0';
  }
  return dest;
}

//--------------------------------------------------------- POSITION
//bool p_is_eq(const struct p* p0, const struct p* p1) {
//  return p0->x == p1->x &&
//         p0->y == p1->y;
//}

//void p_signs(const struct p* p, struct p* signs_ptr) {
//  signs_ptr->x = p->x == 0 ? 0 : (p->x > 0 ? 1 : -1);
//  signs_ptr->y = p->y == 0 ? 0 : (p->y > 0 ? 1 : -1);
//}

//void p_set(struct pos* p, const struct p* new_p) {
//  p->x = new_p->x;
//  p->y = new_p->y;
//}

void p_set_xy(struct pos* p, int x, int y) {
  p->x = x;
  p->y = y;
}

//void p_offset(struct pos* p, const struct p* pd) {
//  p->x += pd->x;
//  p->y += pd->y;
//}

void p_offset_xy(struct pos* p, int dx, int dy) {
  p->x += dx;
  p->y += dy;
}

//void p_multipl(struct pos* p, int v) {
//  p->x *= v;
//  p->y *= v;
//}

void p_multipl_xy(struct pos* p, int x_factor, int y_factor) {
  p->x *= x_factor;
  p->y *= y_factor;
}

//void p_div(struct p* p, int v) {
//  p->x /= v;
//  p->y /= v;
//}
