/**
 * \author Silmaen
 * \date 07/10/2021.
 */
#pragma once

#if defined(__GNUC__)
#if !defined(__clang__)// gcc/g++ only
#ifdef AVX
#pragma GCC target("avx")//Enable AVX
#include <x86intrin.h>   //AVX/SSE Extensions
#endif
#endif
#include <bits/stdc++.h>
#else// not gcc/g++ of clang
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

// standard loop number
#if defined(FLN_DEBUG)
static const std::string configName= "Debug";
#elif defined(FLN_SMALL)
static const std::string configName= "Small";
#else
static const std::string configName= "Release";
#endif
