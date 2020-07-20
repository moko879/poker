#pragma once

#include <cassert>
#include <iostream>

#ifndef NDEBUG

extern "C" void __gcov_flush();

#define CHECK(condition)                                                     \
{ /*LCOV_EXCL_START*/                                                        \
    if(!(condition))                                                         \
    {                                                                        \
        std::cerr << "Assertion failed at " << __FILE__ << ":" << __LINE__;  \
        std::cerr << " inside " << __FUNCTION__ << std::endl;                \
        std::cerr << "Condition: " << #condition;                            \
        __gcov_flush();                                                      \
        abort();                                                             \
    }/*LCOV_EXCL_STOP*/                                                      \
}

#else

#define CHECK(condition) (condition)

#endif