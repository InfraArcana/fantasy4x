#include "cmn_types.h"

/*bool p_is_eq(const P* const p0, const P* const p1) {
  return p0->x == p1->x &&
         p0->y == p1->y;
}*/

/*void p_signs(const P* const p, P* const signs_ptr) {
  signs_ptr->x = p->x == 0 ? 0 : (p->x > 0 ? 1 : -1);
  signs_ptr->y = p->y == 0 ? 0 : (p->y > 0 ? 1 : -1);
}*/

/*void p_set(P* const p, const P* const new_p) {
  p->x = new_p->x;
  p->y = new_p->y;
}*/

void p_set_xy(P* const p, const int X, const int Y) {
  p->x = X;
  p->y = Y;
}

/*void p_offset(P* const p, const P* const pd) {
  p->x += pd->x;
  p->y += pd->y;
}*/

void p_offset_xy(P* const p, const int DX, int const DY) {
  p->x += DX;
  p->y += DY;
}

/*void p_multipl(P* const p, const int V) {
  p->x *= V;
  p->y *= V;
}*/

void p_multipl_xy(P* const p, const int X_FACTOR, const int Y_FACTOR) {
  p->x *= X_FACTOR;
  p->y *= Y_FACTOR;
}

/*void p_div(P* const p, const int V) {
  p->x /= V;
  p->y /= V;
}*/
