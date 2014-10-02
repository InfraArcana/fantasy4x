#ifndef TRACE_H
#define TRACE_H

#include "target_mode.h"

#include <stdio.h>

//--------------------------------------------------------------------
// OPTIONS
//--------------------------------------------------------------------
//  Lvl of TRACE output in debug mode
//  0 : Disabled
//  1 : Standard
//  2 : Verbose

#define TRACE_LVL 1
//--------------------------------------------------------------------

typedef enum {false, true} bool;

#ifdef NDEBUG

#define TRACE(args)
#define TRACE_VERBOSE(args)
#define TRACE_FUNC_BEGIN
#define TRACE_FUNC_BEGIN_VERBOSE
#define TRACE_FUNC_END
#define TRACE_FUNC_END_VERBOSE

#else

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

//Print specific trace message
#define TRACE(msg) if (TRACE_LVL > 0) \
  printf("\n%s, line %d, %s():\n%s\n", \
         __FILE__, __LINE__, __func__, msg)

//Print trace message if verbose mode is enabled
#define TRACE_VERBOSE(msg) if (TRACE_LVL > 1) TRACE(msg)

//Print trace message for function start
#define TRACE_FUNC_BEGIN if (TRACE_LVL > 0) \
  printf("\n%s, line %d, %s()...\n", \
         __FILE__, __LINE__, __func__)

//Print trace message for function start if verbose mode is enabled
#define TRACE_FUNC_BEGIN_VERBOSE if (TRACE_LVL > 1) TRACE_FUNC_BEGIN

//Print trace message for function end
#define TRACE_FUNC_END if (TRACE_LVL > 0) \
  printf("\n%s, line %d, %s() [DONE]\n", \
         __FILE__, __LINE__, __func__)

//Print trace message for function end if verbose mode is enabled
#define TRACE_FUNC_END_VERBOSE if (TRACE_LVL > 1) TRACE_FUNC_END

#endif //NDEBUG

#endif // TRACE_H
