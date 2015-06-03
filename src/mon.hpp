#ifndef MON_HPP
#define MON_HPP

#include <string>

class Race_Def
{
public:
    Race_Def() :
        name        (),
        name_plural (),
        name_a      () {}

    std::string name;
    std::string name_plural;
    std::string name_a;
};

class Mon
{
public:
    Mon(const Race_Def* race_d, const std::string& name);

    Mon(const Mon&);

    Mon();

    Mon& operator=(const Mon&);

private:
    const Race_Def* race_d_;
    std::string name_;
};

namespace race_data
{

void init();

void cleanup();

} // race_data

#endif // MON_HPP
