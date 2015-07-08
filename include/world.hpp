#ifndef WORLD_HPP
#define WORLD_HPP

#include <memory>

#include "utils.hpp"

class Map_Ent
{
public:
    Map_Ent(const P& p, const Char_And_Clr& render_data) :
        p_              (p),
        render_data_    (render_data) {}

    virtual ~Map_Ent() {}

    const P& pos()
    {
        return p_;
    }

    void set_pos(const P& p)
    {
        p_ = p;
    }

    const Char_And_Clr& render_data() const
    {
        return render_data_;
    }

protected:
    P p_;
    Char_And_Clr render_data_;
};

typedef std::unique_ptr<Map_Ent> Map_Ent_Ptr;

class Castle : public Map_Ent
{
public:
    Castle(const P& p) :
        Map_Ent(p, Char_And_Clr('O', clr_white)) {}
};

class Army : public Map_Ent
{
public:
    Army(const P& p) :
        Map_Ent(p, Char_And_Clr('H', clr_red)) {}
};

namespace world
{

extern Map_Ent_Ptr              terrain[map_w][map_h];
extern std::vector<Map_Ent_Ptr> mobs;

void init();

void cleanup();

void process();

} // world

#endif // MAP_HPP
