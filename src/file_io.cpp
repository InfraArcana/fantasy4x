#include "file_io.hpp"

#include <fstream>

#include "io.hpp"

namespace file_io
{

Text_Lines read(const std::string path)
{
    TRACE_FUNC_BEGIN;

    Text_Lines ret;

    std::ifstream ifs(path.c_str());

    std::string line = "";

    while (std::getline(ifs, line))
    {
        ret.push_back(line);
    }

    ifs.close();

    assert(!ret.empty());

    TRACE_FUNC_END;
    return ret;
}

Data_File_Content read_data_file(const std::string path)
{
    TRACE_FUNC_BEGIN;

    Data_File_Content ret;

    Text_Lines lines = read(path);

    assert(!lines.empty());

    Data_File_Section section;

    for (const auto& line : lines)
    {
        if (line.empty())
        {
            if (!section.empty())
            {
                // Add the current section and start a new one
                ret.push_back(section);
                section.resize(0);
            }
        }
        else if (line[0] != '#')
        {
            Text_Lines header_and_data = split_str(line, ":");

            assert(header_and_data.size() == 2);

            Data_File_Element element(header_and_data[0], header_and_data[1]);

            section.push_back(element);
        }
    }

    // Unless there are empty lines after the last section, it will not yet have been added to the
    // file content list - so then we do that here.
    if (!section.empty())
    {
        ret.push_back(section);
    }

    TRACE_FUNC_END;
    return ret;
}

} // file_io
