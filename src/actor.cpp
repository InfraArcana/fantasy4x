#include "actor.hpp"

#include <assert.h>
#include <string>

#include "base.hpp"
#include "cmn_utils.hpp"
#include "file_io.hpp"

//-----------------------------------------------------------------------------
// Actor
//-----------------------------------------------------------------------------
Actor::Actor(const Race_Data_T* race_d, const std::string& name) :
    race_d_     (race_d),
    name_       (name) {}

Actor::Actor(const Actor& other) :
    Actor(other.race_d_, other.name_) {}

Actor::Actor() :
    Actor(nullptr, "") {}

Actor& Actor::operator=(const Actor& rhs)
{
    race_d_ = rhs.race_d_;
    name_   = rhs.name_;

    return *this;
}

//-----------------------------------------------------------------------------
// Race data
//-----------------------------------------------------------------------------
namespace race_data
{

namespace
{

std::vector<Race_Data_T> race_data_list_;

} // namespace

void init()
{
    TRACE_FUNC_BEGIN;

    cleanup();

    Data_File_Content file_content = file_io::read_data_file("data/races.dat");

    for (const Data_File_Section& data_section : file_content)
    {
        Race_Data_T race;

        for (const Data_File_Element& data_element : data_section)
        {
            Text_Lines data = split_str(data_element.data, "|");

            assert(data.size() == 2); // Base name & plural name

            race.name           = data[0];
            race.name_plural    = data[1];
        }

        race_data_list_.push_back(race);
    }

    TRACE_FUNC_END;
}

void cleanup()
{
    TRACE_FUNC_BEGIN;

    race_data_list_.resize(0);

    TRACE_FUNC_END;
}

} // race_data
