#pragma once

#define ASSERT(x) if (!(x)) assert(0);

// #include <signal.h>

// #ifdef SIGTRAP
// #define ASSERT(x) if (!(x)) raise(SIGTRAP);
// #else
// #define ASSERT(x) if (!(x)) raise(SIGABRT);
// #endif

//#define ASSERT(x) if (!(x)) __debugbreak();
