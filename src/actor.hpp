#ifndef ACTOR_H
#define ACTOR_H

#include <string>

class Race_Data_T
{
public:
    Race_Data_T() :
        name        (),
        name_plural (),
        name_a      () {}

    std::string name;
    std::string name_plural;
    std::string name_a;
};

class Actor
{
public:
    Actor(const Race_Data_T* race_d, const std::string& name);

    Actor(const Actor&);

    Actor();

    Actor& operator=(const Actor&);

private:
    const Race_Data_T* race_d_;
    std::string name_;
};

namespace race_data
{

void init();

void cleanup();

} // race_data

#endif // ACTOR_H
