/**
 * \author argawaen
 * \date 07/10/2021.
 */

#pragma once

#if defined(__GNUC__) && !defined(__clang__)// gcc/g++ only
#if defined(PROFILING)
#pragma GCC optimize("O3", "omit-frame-pointer", "unroll-loops", "unsafe-math-optimizations", "no-trapping-math")
#elif defined(COVERAGE)
#pragma GCC optimize("O1", "no-omit-frame-pointer", "no-inline", "no-optimize-sibling-calls")
#elif defined(IDEBUG)
#pragma GCC optimize("omit-frame-pointer", "unroll-loops", "unsafe-math-optimizations", "no-trapping-math")
#else
#pragma GCC optimize("O3", "omit-frame-pointer", "inline", "unroll-loops", "unsafe-math-optimizations", "no-trapping-math")
#endif
#ifdef AVX
#pragma GCC target("avx")//Enable AVX
#include <x86intrin.h>   //AVX/SSE Extensions
#endif
#include <bits/stdc++.h>
#else// not gcc/g++
#include <algorithm>
#include <cfloat>
#include <chrono>
#include <climits>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#endif

//--------------------------
// some base using from std
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::string;
//--------------------------

// debuging trap functions
#ifdef IDEBUG
inline void trap() {
#ifdef _MSC_VER
    *(int*)nullptr= 0;
#else
    __builtin_trap();
#endif
}
#define TRAP_CND(C)   \
    {                 \
        if(C) trap(); \
    }
#define TRAP_MSG(C, M)         \
    {                          \
        if(C) {                \
            cerr << M << endl; \
            trap();            \
        }                      \
    }
#else
#define TRAP_CND(C) \
    {               \
        if(C) {}    \
    }
#define TRAP_MSG(C, M) \
    {                  \
        if(C) {}       \
    }
#endif
