#ifndef WORLD_HPP
#define WORLD_HPP

#include <memory>

#include "utils.hpp"

class Map_Ent
{
public:
    Map_Ent(const Pos& p, const Char_And_Clr& render_data) :
        p_              (p),
        render_data_    (render_data) {}

    virtual ~Map_Ent() {}

    const Pos& get_pos()
    {
        return p_;
    }

    const Char_And_Clr& get_render_data() const
    {
        return render_data_;
    }

protected:
    Pos p_;
    Char_And_Clr render_data_;
};

typedef std::unique_ptr<Map_Ent> Map_Ent_Ptr;

class Castle : public Map_Ent
{
public:
    Castle(const Pos& p) :
        Map_Ent(p, Char_And_Clr('O', clr_white)) {}
};

class Army : public Map_Ent
{
public:
    Army(const Pos& p) :
        Map_Ent(p, Char_And_Clr('H', clr_red_lgt)) {}
};

namespace world
{

extern Map_Ent_Ptr              terrain[MAP_W][MAP_H];
extern std::vector<Map_Ent_Ptr> mobs;

void init();

void cleanup();

} // world

#endif // MAP_HPP
