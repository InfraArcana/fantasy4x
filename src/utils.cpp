#include "utils.hpp"

//-----------------------------------------------------------------------------
// Text
//-----------------------------------------------------------------------------
Text_Lines split_str(std::string str, const std::string& delim)
{
    assert(!str.empty());

    Text_Lines ret;

    while (true)
    {
        const size_t IDX = str.find(delim);

        if (IDX == std::string::npos)
        {
            // Add the remaining string
            ret.push_back(str);
            break;
        }

        const std::string token = str.substr(0, IDX);

        ret.push_back(token);

        str.erase(0, IDX + delim.length());
    }

    return ret;
}
