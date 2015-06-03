#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>

#include "cmn_data.hpp"
#include "colors.hpp"

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
    Pos(const int X, const int Y)   : x(X), y(Y) {}
    Pos(const Pos& p)               : x(p.x), y(p.y) {}
    Pos(const int V)                : x(V), y(V) {}

    Pos& operator=(const Pos& p)
    {
        x = p.x;
        y = p.y;
        return *this;
    }

    Pos& operator*=(const int  V)   {x *= V;   y *= V;      return *this;}
    Pos& operator*=(const Pos& p)   {x *= p.x; y *= p.y;    return *this;}
    Pos& operator/=(const int  V)   {x /= V;   y /= V;      return *this;}
    Pos& operator/=(const Pos& p)   {x /= p.x; y /= p.y;    return *this;}
    Pos& operator+=(const Pos& p)   {x += p.x; y += p.y;    return *this;}
    Pos& operator-=(const Pos& p)   {x -= p.x; y -= p.y;    return *this;}
    Pos operator+(const Pos& p)     const {return Pos(x + p.x,  y + p.y);}
    Pos operator+(const int V)      const {return Pos(x + V,    y + V);}
    Pos operator-(const Pos& p)     const {return Pos(x - p.x,  y - p.y);}
    Pos operator-(const int V)      const {return Pos(x - V,    y - V);}
    Pos operator/(const int V)      const {return Pos(x / V,    y / V);}
    Pos operator/(const Pos& p)     const {return Pos(x / p.x,  y / p.y);}
    Pos operator*(const int V)      const {return Pos(x * V,    y * V);}
    Pos operator*(const Pos& p)     const {return Pos(x * p.x,  y * p.y);}
    bool operator==(const Pos& p)   const {return x == p.x  && y == p.y;}
    bool operator!=(const Pos& p)   const {return x != p.x  || y != p.y;}
    bool operator!=(const int V)    const {return x != V    || y != V;}
    bool operator>(const Pos& p)    const {return x > p.x   && y > p.y;}
    bool operator>(const int  V)    const {return x > V     && y > V;}
    bool operator<(const Pos& p)    const {return x < p.x   && y < p.y;}
    bool operator<(const int  V)    const {return x < V     && y < V;}
    bool operator>=(const Pos&  p)  const {return x >= p.x  && y >= p.y;}
    bool operator>=(const int   V)  const {return x >= V    && y >= V;}
    bool operator<=(const Pos&  p)  const {return x <= p.x  && y <= p.y;}
    bool operator<=(const int   V)  const {return x <= V    && y <= V;}

    Pos get_signs() const
    {
        return Pos(x == 0 ? 0 : x > 0 ? 1 : -1,
                   y == 0 ? 0 : y > 0 ? 1 : -1);
    }

    Pos get_pos_with_offset(const Pos& d)       const {return Pos(x + d.x, y + d.y);}
    Pos get_pos_with_x_offset(const int DX)     const {return Pos(x + DX, y);}
    Pos get_pos_with_y_offset(const int DY)     const {return Pos(x, y + DY);}

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

    Rect(const int X0, const int Y0, const int X1, const int Y1) :
        p0(Pos(X0, Y0)), p1(Pos(X1, Y1)) {}

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
