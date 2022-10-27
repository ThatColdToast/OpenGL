#pragma once

#include <assert.h>
#define ASSERT(x) if (!(x)) __assert("Assert 1", 0, "Assert 2");

// #include <signal.h>

// #ifdef SIGTRAP
// #define ASSERT(x) if (!(x)) raise(SIGTRAP);
// #else
// #define ASSERT(x) if (!(x)) raise(SIGABRT);
// #endif

//#define ASSERT(x) if (!(x)) __debugbreak();
