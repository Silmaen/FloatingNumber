#include <gtest/gtest.h>

#define IDEBUG
#include "baseDefines.h"
#include "FloatFunctions.h"
#include "trickFunctions.h"
#include "testHelper.h"


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

TEST(algo_benchmark, log2){
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== BENCHMARK LOG2 ===---" << std::endl;
    // performance
    std::cout << "log2 performance review" << std::endl;
#endif
    CHRONOMETER_DURATION(,,"",1,1); // warmup
    CHRONOMETER_ITERATION(std::log2(150.0f),,                                                "std::log2         ",100000,50)
    CHRONOMETER_ITERATION(fln::object::log2(f),fln::object::BitFloat f(150.0f) ,"fln::object::log2 ",100000,10)
    CHRONOMETER_ITERATION(fln::object::log2a(f),fln::object::BitFloat f(150.0f),"fln::object::log2a",100000,10)
    CHRONOMETER_ITERATION(fln::bithack::log2(150.0f),                                        ,"fln::bithack::log2",100000,10)
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== END LOG2 ===---" << std::endl;
#endif
}

TEST(algo_benchmark, exp2){
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== BENCHMARK EXP2 ===---" << std::endl;
    std::cout << "log2 performance review" << std::endl;
#endif
    CHRONOMETER_DURATION(,,"",1,1); // warmup
    CHRONOMETER_ITERATION(std::exp2(150.0f),                                                ,"std::exp2         ",100000,300)
    CHRONOMETER_ITERATION(fln::object::exp2(f),fln::object::BitFloat f(150.0f),"fln::object::exp2 ",100000,10)
    CHRONOMETER_ITERATION(fln::bithack::exp2(150.0f),                                       ,"fln::bithack::exp2",100000,10)
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== END EXP2 ===---" << std::endl;
#endif
}

#pragma GCC diagnostic pop
