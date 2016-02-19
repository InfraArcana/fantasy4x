#ifndef SCRIPT_H
#define SCRIPT_H

#include <string>

namespace script
{

void init();

void cleanup();

// NOTE: "script" must be the path to a lua file, relative to the script directory
void load(const std::string script);

int get_int(const std::string name);

std::string get_str(const std::string name);

} // script

#endif // SCRIPT_H
