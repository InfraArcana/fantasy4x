#ifndef CMN_UTILS_H
#define CMN_UTILS_H

#include "cmn_data.h"
#include "colors.h"

#define NR_ELEMS(a) (sizeof(a) / sizeof(a[0]))

/*--------------------------------------------------------- STRING HANDLING */
char* to_str(char* dest, size_t size, const int V);

char* str_app(char* dest, size_t size, const char* app);

/*void str_set(str_buffer_t* str_buffer_ptr, const char* str);*/

/*--------------------------------------------------------- POSITION */
typedef struct {int x, y;} P;

/*bool p_is_eq(const P* const p0, const P* const p1);*/

/*void p_signs(const P* const p, P* const signs_ptr);*/

/*void p_set(P* const p, const P* const new_p);*/

void p_set_xy(P* const p, const int X, const int Y);

/*void p_offset(P* const p, const P* const pd);*/

void p_offset_xy(P* const p, const int DX, int const DY);

/*void p_multipl(P* const p, const int V);*/

void p_multipl_xy(P* const p, const int X_FACTOR, const int Y_FACTOR);

/*void p_div(P* const p, const int V);*/

/*--------------------------------------------------------- RECTANGLE */
typedef struct {P p0; P p1;} Rect;

/*void rect_set(Rect* const r, const P* const p0, const P* const p1);*/

/*void rect_set_xy(Rect* r, const int X0, const int Y0, const int X1, const int Y1);*/

/*--------------------------------------------------------- GLYPH AND COLOR */
typedef struct {char glyph; Clr clr; Clr clrBg;} GlyphAndClr;

/*--------------------------------------------------------- STRING AND COLOR */
typedef struct {char* str; Clr clr;} StrAndClr;

/*--------------------------------------------------------- DICE PARAMATER */
/*
typedef struct {
public:
  DiceParam() : rolls(1), sides(100), plus(0) {}

  DiceParam(const int ROLLS, const int SIDES, const int PLUS = 0) :
    rolls(ROLLS), sides(SIDES), plus(PLUS) {}

  DiceParam(const DiceParam& other) :
    rolls(other.rolls), sides(other.sides), plus(other.plus) {}

  DiceParam& operator=(const DiceParam& other) {
    rolls = other.rolls;
    sides = other.sides;
    plus  = other.plus;
    return *this;
  }

  inline int getHighest() const {return (rolls * sides) + plus;}

  int rolls, sides, plus;
} DiceParam;
*/

/*--------------------------------------------------------- RANGE */
/*
typedef struct {
  Range() : lower(-1), upper(-1) {}

  Range(const int LOWER, const int UPPER) :
    lower(LOWER), upper(UPPER) {}

  int lower, upper;
} Range;
*/

/* Useful to e.g. iterate over all directions, or passing as direction parameter */
enum Dir {
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

#endif
