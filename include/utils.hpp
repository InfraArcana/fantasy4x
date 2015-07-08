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
struct P
{
    P()                             : x(0), y(0) {}
    P(const int x, const int y)     : x(x), y(y) {}
    P(const P& p)                   : x(p.x), y(p.y) {}
    P(const int v)                  : x(v), y(v) {}

    P& operator=(const P& p)
    {
        x = p.x;
        y = p.y;
        return *this;
    }

    P& operator*=(const int  v)     {x *= v;   y *= v;      return *this;}
    P& operator*=(const P& p)       {x *= p.x; y *= p.y;    return *this;}
    P& operator/=(const int  v)     {x /= v;   y /= v;      return *this;}
    P& operator/=(const P& p)       {x /= p.x; y /= p.y;    return *this;}
    P& operator+=(const P& p)       {x += p.x; y += p.y;    return *this;}
    P& operator-=(const P& p)       {x -= p.x; y -= p.y;    return *this;}
    P operator+(const P& p)         const {return P(x + p.x,  y + p.y);}
    P operator+(const int v)        const {return P(x + v,    y + v);}
    P operator-(const P& p)         const {return P(x - p.x,  y - p.y);}
    P operator-(const int v)        const {return P(x - v,    y - v);}
    P operator/(const int v)        const {return P(x / v,    y / v);}
    P operator/(const P& p)         const {return P(x / p.x,  y / p.y);}
    P operator*(const int v)        const {return P(x * v,    y * v);}
    P operator*(const P& p)         const {return P(x * p.x,  y * p.y);}
    bool operator==(const P& p)     const {return x == p.x  && y == p.y;}
    bool operator!=(const P& p)     const {return x != p.x  || y != p.y;}
    bool operator!=(const int v)    const {return x != v    || y != v;}
    bool operator>(const P& p)      const {return x > p.x   && y > p.y;}
    bool operator>(const int v)     const {return x > v     && y > v;}
    bool operator<(const P& p)      const {return x < p.x   && y < p.y;}
    bool operator<(const int v)     const {return x < v     && y < v;}
    bool operator>=(const P& p)     const {return x >= p.x  && y >= p.y;}
    bool operator>=(const int v)    const {return x >= v    && y >= v;}
    bool operator<=(const P& p)     const {return x <= p.x  && y <= p.y;}
    bool operator<=(const int v)    const {return x <= v    && y <= v;}

    P signs() const
    {
        return P(x == 0 ? 0 : x > 0 ? 1 : -1,
                 y == 0 ? 0 : y > 0 ? 1 : -1);
    }

    P pos_with_offset(const P& d)       const {return P(x + d.x, y + d.y);}
    P pos_with_x_offset(const int dx)   const {return P(x + dx, y);}
    P pos_with_y_offset(const int dy)   const {return P(x, y + dy);}

    void set(const P& other)                    {x = other.x;   y = other.y;}
    void set(const int new_x, const int new_y)  {x = new_x;     y = new_y;}

    void swap(P& p)
    {
        P p_temp(p);
        p = *this;
        x = p_temp.x;
        y = p_temp.y;
    }

    int x, y;
};

struct Rect
{
    Rect() : p0(P()), p1(P()) {}

    Rect(const P& p0_, const P& p1_) :
        p0(p0_),
        p1(p1_) {}

    Rect(const int x0, const int y0, const int x1, const int y1) :
        p0(P(x0, y0)),
        p1(P(x1, y1)) {}

    Rect(const Rect& r) : p0(r.p0), p1(r.p1) {}

    int w()             const {return p1.x - p0.x + 1;}
    int h()             const {return p1.y - p0.y + 1;}
    P dims()            const {return {w(), h()};}
    int min_dim()       const {return std::min(w(), h());}
    int max_dim()       const {return std::max(w(), h());}
    P center_pos()      const {return ((p1 + p0) / 2);}

    P p0;
    P p1;
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
