#pragma once

#include <assert.h>
#define ASSERT(x) if (!(x)) assert("Assert 1");

// #include <signal.h>

// #ifdef SIGTRAP
// #define ASSERT(x) if (!(x)) raise(SIGTRAP);
// #else
// #define ASSERT(x) if (!(x)) raise(SIGABRT);
// #endif

//#define ASSERT(x) if (!(x)) __debugbreak();
