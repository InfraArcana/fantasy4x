#ifndef FILE_IO_H
#define FILE_IO_H

#include <string>
#include <vector>

#include "cmn_utils.hpp"

//-----------------------------------------------------------------------------
// Data file structure:
// The Data File Content contains one or more Data File Sections, which in turn
// contains one or more Data File Elements. Each element has one header field,
// and one data field. The header is used for specifying the type of data
// (e.g. "NAME")
//
// In Data Files, sections are separated by empty lines.
//
// Format of a data text file element:
// HEADER:data
//
// The structure of the data string depends on the data user. A typical
// structure is several values delimited by pipes ("|"), i.e.:
//
// data1|data2|data3
//
// It is the data user's responsibility to handle this string.
//-----------------------------------------------------------------------------

struct Data_File_Element
{
    Data_File_Element(const std::string header_, const std::string data_) :
        header  (header_),
        data    (data_) {}

    Data_File_Element() :
        Data_File_Element("", "") {}

    std::string header;
    std::string data;
};

typedef std::vector<Data_File_Element> Data_File_Section;
typedef std::vector<Data_File_Section> Data_File_Content;

namespace file_io
{

Text_Lines read(const std::string path);

Data_File_Content read_data_file(const std::string path);

} // file_io

#endif // FILE_HANDLING_H
