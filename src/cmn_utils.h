#ifndef CMN_UTILS_H
#define CMN_UTILS_H

#include "cmn_data.h"
#include "colors.h"

#define NR_ELEMS(a) (sizeof(a) / sizeof(a[0]))

//--------------------------------------------------------- MIN/MAX
int min(int a, int b);

int max(int a, int b);

//--------------------------------------------------------- STRING HANDLING
void str_fill_nul(char* dest, size_t size);

char* to_str(char* dest, size_t size, int v);

void str_alloc(char** dest, const char* str);

char* str_app(char* dest, size_t size, const char* app);

//--------------------------------------------------------- POSITION
struct pos {int x, y;};

//bool p_is_eq(const struct pos* p0, const struct pos* p1);

//void p_signs(const struct pos* p, pos* const signs_ptr);

//void p_set(struct pos* p, const struct pos* new_p);

void p_set_xy(struct pos* p, int x, int y);

//void p_offset(struct pos* const p, const struct pos* const pd);

void p_offset_xy(struct pos* p, const int DX, int const DY);

//void p_multipl(struct pos* const p, const int V);

void p_multipl_xy(struct pos* p, const int X_FACTOR, const int Y_FACTOR);

//void p_div(struct pos* const p, const int V);

//--------------------------------------------------------- RECTANGLE
struct rect {struct pos p0; struct pos p1;};

//void rect_set(Rect* r, const struct pos* p0, const struct pos* p1);

//void rect_set_xy(Rect* r, int x0, int y0, int x1, int y1);

//--------------------------------------------------------- CHAR AND COLOR
struct char_and_clr {
  char        ch;
  const Clr*  clr;
  const Clr*  clr_bg;
};

//--------------------------------------------------------- STRING AND COLOR
struct str_and_clr {
  char* str;
  Clr   clr;
};

//--------------------------------------------------------- DICE PARAMATER
//struct dice_param {
//public:
//  DiceParam() : rolls(1), sides(100), plus(0) {}
//
//  DiceParam(int rolls_, int sides_, int plus_ = 0) :
//    rolls(rolls_), sides(sides_), plus(plus_) {}
//
//  DiceParam(const DiceParam& other) :
//    rolls(other.rolls), sides(other.sides), plus(other.plus) {}
//
//  DiceParam& operator=(const DiceParam& other) {
//    rolls = other.rolls;
//    sides = other.sides;
//    plus  = other.plus;
//    return *this;
//  }
//
//  inline int getHighest() const {return (rolls * sides) + plus;}
//
//  int rolls, sides, plus;
//};

//--------------------------------------------------------- RANGE
//struct range {
//  Range() : lower(-1), upper(-1) {}
//
//  Range(const int lower_, const int upper_) :
//    lower(lower_), upper(upper_) {}
//
//  int lower, upper;
//};

//Useful to iterate over in algorithms, or passing as direction parameter
enum dir {
  DOWN_LEFT   = 1,
  DOWN        = 2,
  DOWN_RIGHT  = 3,
  LEFT        = 4,
  CENTER      = 5,
  RIGHT       = 6,
  UP_LEFT     = 7,
  UP          = 8,
  UP_RIGHT    = 9,
  DIR_END     = 10
};

#endif // CMN_UTILS_H
