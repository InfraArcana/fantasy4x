#include "mon.hpp"

#include <assert.h>
#include <string>
#include <map>
#include <vector>

#include "io.hpp"

//-----------------------------------------------------------------------------
// Monster
//-----------------------------------------------------------------------------
Mon::Mon(const Race_Def* race_d, const std::string& name) :
    race_d_     (race_d),
    name_       (name) {}

Mon::Mon(const Mon& other) :
    Mon(other.race_d_, other.name_) {}

Mon::Mon() :
    Mon(nullptr, "") {}

Mon& Mon::operator=(const Mon& rhs)
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

enum class Race_Data_Header_Id
{
    name,
};

std::vector<Race_Def> race_defs_;

} // namespace

void init()
{
    TRACE_FUNC_BEGIN;

//    cleanup();
//
//    std::map<std::string, Race_Data_Header_Id> header_string_to_id;
//
//    header_string_to_id["NAME"] = Race_Data_Header_Id::name;
//
//    Data_File_Content file_content = file_io::read_data_file("data/races.dat");
//
//    for (const Data_File_Section& data_section : file_content)
//    {
//        Race_Def race_def;
//
//        for (const Data_File_Element& data_element : data_section)
//        {
//            const Race_Data_Header_Id header = header_string_to_id.at(data_element.header);
//
//            switch (header)
//            {
//            case Race_Data_Header_Id::name:
//            {
//                Text_Lines data = split_str(data_element.data, "|");
//
//                assert(data.size() == 2); // Base name & plural name
//
//                race_def.name           = data[0];
//                race_def.name_plural    = data[1];
//                break;
//            }
//            }
//        }
//
//        race_defs_.push_back(race_def);
//    }

    TRACE_FUNC_END;
}

void cleanup()
{
    TRACE_FUNC_BEGIN;

    race_defs_.resize(0);

    TRACE_FUNC_END;
}

} // race_data
