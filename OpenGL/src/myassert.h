#pragma once

#include <signal.h>

#ifdef SIGTRAP
#define ASSERT(x) if (!(x)) raise(SIGTRAP);
#else
#define ASSERT(x) if (!(x)) raise(SIGABRT);
#endif

//#define ASSERT(x) if (!(x)) __debugbreak();