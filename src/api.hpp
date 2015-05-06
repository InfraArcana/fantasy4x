#ifndef API_H
#define API_H

#include <SDL.h>

namespace api
{

void init();

void cleanup();

void sleep(Uint32 duration);

} // api

#endif // API_H
