#include <baseFunctions.h>
#include <gtest/gtest.h>

#define IDEBUG
#include "FloatFunctions.h"
#include "DoubleFunctions.h"
#include "baseDefines.h"
#include "bithack_Functions.h"
#include "testHelper.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

TEST(algo_benchmark, abs){
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== BENCHMARK ABS ===---" << std::endl;
    // performance
    std::cout << "abs performance review " << configName << std::endl;
#endif
    CHRONOMETER_DURATION(,,"",1,1); // warmup
    CHRONOMETER_ITERATION(std::abs(-150.0),,                                              "std::abs         (dbl)",5)
    CHRONOMETER_ITERATION(fln::object::abs(f),fln::object::BitDouble f(-150.0)  ,"fln::object::abs (dbl)",10)
    CHRONOMETER_ITERATION(fln::bithack::abs(-150.0),                                     ,"fln::bithack::abs(dbl)",10)
    CHRONOMETER_ITERATION(fln::ternary::abs(-150.0),                                     ,"fln::ternary::abs(dbl)",10)
    CHRONOMETER_ITERATION(std::abs(-150.f),,                                            "std::abs              ",30)
    CHRONOMETER_ITERATION(fln::object::abs(f),fln::object::BitFloat f(-150.0f) ,"fln::object::abs      ",10)
    CHRONOMETER_ITERATION(fln::bithack::abs(150.0f),                                   ,"fln::bithack::abs     ",10)
    CHRONOMETER_ITERATION(fln::ternary::abs(-150.0f),                                     ,"fln::ternary::abs     ",10)

#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== END ABS ===---" << std::endl;
#endif
}
TEST(algo_benchmark, log2){
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== BENCHMARK LOG2 ===---" << std::endl;
    // performance
    std::cout << "log2 performance review " << configName << std::endl;
#endif
    CHRONOMETER_DURATION(,,"",1,1); // warmup
    CHRONOMETER_ITERATION(std::log2(150.0),,                                              "std::log2         (dbl)",5)
    CHRONOMETER_ITERATION(fln::object::log2(f),fln::object::BitDouble f(150.0)  ,"fln::object::log2 (dbl)",10)
    CHRONOMETER_ITERATION(fln::object::log2a(f),fln::object::BitDouble f(150.0) ,"fln::object::log2a(dbl)",10)
    CHRONOMETER_ITERATION(fln::bithack::log2(150.0),                                     ,"fln::bithack::log2(dbl)",10)
    CHRONOMETER_ITERATION(std::log2(150.0f),,                                            "std::log2              ",30)
    CHRONOMETER_ITERATION(fln::object::log2(f),fln::object::BitFloat f(150.0f) ,"fln::object::log2      ",10)
    CHRONOMETER_ITERATION(fln::object::log2a(f),fln::object::BitFloat f(150.0f),"fln::object::log2a     ",10)
    CHRONOMETER_ITERATION(fln::bithack::log2(150.0f),                                   ,"fln::bithack::log2     ",10)
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== END LOG2 ===---" << std::endl;
#endif
}

TEST(algo_benchmark, exp2){
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== BENCHMARK EXP2 ===---" << std::endl;
    std::cout << "exp2 performance review " << configName << std::endl;
#endif
    CHRONOMETER_DURATION(,,"",1,1); // warmup
    CHRONOMETER_ITERATION(std::exp2(150.0),                                            ,"std::exp2         (dbl)",5)
    CHRONOMETER_ITERATION(fln::object::exp2(f),fln::object::BitDouble f(150.0),"fln::object::exp2 (dbl)",15)
    CHRONOMETER_ITERATION(fln::bithack::exp2(150.0),                                   ,"fln::bithack::exp2(dbl)",10)
    CHRONOMETER_ITERATION(std::exp2(150.0f),                                           ,"std::exp2              ",300)
    CHRONOMETER_ITERATION(fln::object::exp2(f),fln::object::BitFloat f(150.0f),"fln::object::exp2      ",15)
    CHRONOMETER_ITERATION(fln::bithack::exp2(150.0f),                                  ,"fln::bithack::exp2     ",10)
 #ifdef FLN_VERBOSE_TEST
    std::cout << "---=== END EXP2 ===---" << std::endl;
#endif
}

TEST(algo_benchmark, pow){
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== BENCHMARK POW ===---" << std::endl;
    std::cout << "pow performance review " << configName << std::endl;
#endif
    CHRONOMETER_DURATION(,,"",1,1); // warmup
    CHRONOMETER_ITERATION(std::pow(150.0,1.25),                                            ,"std::pow         (dbl)",5)
    CHRONOMETER_ITERATION(fln::object::pow(f,p),fln::object::BitDouble f(150.0);fln::object::BitDouble p(1.25),"fln::object::pow (dbl)",15)
    CHRONOMETER_ITERATION(fln::bithack::pow(150.0,1.25),                                   ,"fln::bithack::pow(dbl)",10)
    CHRONOMETER_ITERATION(std::pow(150.0f,1.25f),                                           ,"std::pow              ",300)
    CHRONOMETER_ITERATION(fln::object::pow(f,p),fln::object::BitFloat f(150.0f);fln::object::BitFloat p(1.25f),"fln::object::pow      ",15)
    CHRONOMETER_ITERATION(fln::bithack::pow(150.0f,1.25f),                                  ,"fln::bithack::pow     ",10)
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== END POW ===---" << std::endl;
#endif
}

#pragma GCC diagnostic pop
