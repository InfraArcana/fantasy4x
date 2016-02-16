#include "utils.hpp"

#include <cassert>

//-----------------------------------------------------------------------------
// Text
//-----------------------------------------------------------------------------
Text_Lines split_str(std::string str, const std::string& delim)
{
    assert(!str.empty());

    Text_Lines ret;

    while (true)
    {
        const size_t idx = str.find(delim);

        if (idx == std::string::npos)
        {
            // Add the remaining string
            ret.push_back(str);
            break;
        }

        const std::string token = str.substr(0, idx);

        ret.push_back(token);

        str.erase(0, idx + delim.length());
    }

    return ret;
}
