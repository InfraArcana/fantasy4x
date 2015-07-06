#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>

#include "lib_wrap.hpp"
#include "cmn_data.hpp"

//-----------------------------------------------------------------------------
// Text
//-----------------------------------------------------------------------------
typedef std::vector<std::string> Text_Lines;

struct Char_And_Clr
{
    Char_And_Clr(char ch_, Clr clr_, Clr clr_bg_ = clr_black) :
        ch      (ch_),
        clr     (clr_),
        clr_bg  (clr_bg_) {}

    Char_And_Clr() :
        Char_And_Clr(0, clr_white, clr_white) {}

    char        ch;
    const Clr   clr;
    const Clr   clr_bg;
};

struct Str_And_Clr
{
    std::string str;
    Clr         clr;
};

Text_Lines split_str(std::string str, const std::string& delim);

//-----------------------------------------------------------------------------
// Geometry
//-----------------------------------------------------------------------------
struct Pos
{
    Pos()                           : x(0), y(0) {}
    Pos(const int x, const int y)   : x(x), y(y) {}
    Pos(const Pos& p)               : x(p.x), y(p.y) {}
    Pos(const int v)                : x(v), y(v) {}

    Pos& operator=(const Pos& p)
    {
        x = p.x;
        y = p.y;
        return *this;
    }

    Pos& operator*=(const int  v)   {x *= v;   y *= v;      return *this;}
    Pos& operator*=(const Pos& p)   {x *= p.x; y *= p.y;    return *this;}
    Pos& operator/=(const int  v)   {x /= v;   y /= v;      return *this;}
    Pos& operator/=(const Pos& p)   {x /= p.x; y /= p.y;    return *this;}
    Pos& operator+=(const Pos& p)   {x += p.x; y += p.y;    return *this;}
    Pos& operator-=(const Pos& p)   {x -= p.x; y -= p.y;    return *this;}
    Pos operator+(const Pos& p)     const {return Pos(x + p.x,  y + p.y);}
    Pos operator+(const int v)      const {return Pos(x + v,    y + v);}
    Pos operator-(const Pos& p)     const {return Pos(x - p.x,  y - p.y);}
    Pos operator-(const int v)      const {return Pos(x - v,    y - v);}
    Pos operator/(const int v)      const {return Pos(x / v,    y / v);}
    Pos operator/(const Pos& p)     const {return Pos(x / p.x,  y / p.y);}
    Pos operator*(const int v)      const {return Pos(x * v,    y * v);}
    Pos operator*(const Pos& p)     const {return Pos(x * p.x,  y * p.y);}
    bool operator==(const Pos& p)   const {return x == p.x  && y == p.y;}
    bool operator!=(const Pos& p)   const {return x != p.x  || y != p.y;}
    bool operator!=(const int v)    const {return x != v    || y != v;}
    bool operator>(const Pos& p)    const {return x > p.x   && y > p.y;}
    bool operator>(const int  v)    const {return x > v     && y > v;}
    bool operator<(const Pos& p)    const {return x < p.x   && y < p.y;}
    bool operator<(const int  v)    const {return x < v     && y < v;}
    bool operator>=(const Pos&  p)  const {return x >= p.x  && y >= p.y;}
    bool operator>=(const int   v)  const {return x >= v    && y >= v;}
    bool operator<=(const Pos&  p)  const {return x <= p.x  && y <= p.y;}
    bool operator<=(const int   v)  const {return x <= v    && y <= v;}

    Pos get_signs() const
    {
        return Pos(x == 0 ? 0 : x > 0 ? 1 : -1,
                   y == 0 ? 0 : y > 0 ? 1 : -1);
    }

    Pos get_pos_with_offset(const Pos& d)       const {return Pos(x + d.x, y + d.y);}
    Pos get_pos_with_x_offset(const int dx)     const {return Pos(x + dx, y);}
    Pos get_pos_with_y_offset(const int dy)     const {return Pos(x, y + dy);}

    void set(const Pos& other)                  {x = other.x;   y = other.y;}
    void set(const int new_x, const int new_y)  {x = new_x;     y = new_y;}

    void swap(Pos& p)
    {
        Pos p_temp(p);
        p = *this;
        x = p_temp.x;
        y = p_temp.y;
    }

    int x, y;
};

struct Rect
{
    Rect() : p0(Pos()), p1(Pos()) {}

    Rect(const Pos& p0_, const Pos& p1_) :  p0(p0_), p1(p1_) {}

    Rect(const int x0, const int y0, const int x1, const int y1) :
        p0(Pos(x0, y0)), p1(Pos(x1, y1)) {}

    Rect(const Rect& r) : p0(r.p0), p1(r.p1) {}

    int get_w()             const {return p1.x - p0.x + 1;}
    int get_h()             const {return p1.y - p0.y + 1;}
    Pos get_dims()          const {return {get_w(), get_h()};}
    int get_min_dim()       const {return std::min(get_w(), get_h());}
    int get_max_dim()       const {return std::max(get_w(), get_h());}
    Pos get_center_pos()    const {return ((p1 + p0) / 2);}

    Pos p0;
    Pos p1;
};

//-----------------------------------------------------------------------------
// Random number generation
//-----------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------
// Range
//-----------------------------------------------------------------------------
//struct range {
//  Range() : lower(-1), upper(-1) {}
//
//  Range(const int lower_, const int upper_) :
//    lower(lower_), upper(upper_) {}
//
//  int lower, upper;
//};

//-----------------------------------------------------------------------------
// Direction
//-----------------------------------------------------------------------------
//Useful to iterate over in algorithms, or passing as direction parameter
enum dir
{
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

#endif // CMN_UTILS_HPP
