#include <baseFunctions.h>
#include <gtest/gtest.h>
#include <union_Functions.h>
#include "rng.h"

#define IDEBUG
#include "DoubleFunctions.h"
#include "FloatFunctions.h"
#include "baseDefines.h"
#include "bithack_Functions.h"
#include "testHelper.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
#pragma GCC diagnostic ignored "-Wunused-value"

TEST(algo_benchmark_rand, abs) {
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== BENCHMARK ABS ===---" << std::endl;
    // performance
    std::cout << "abs performance review " << configName << std::endl;
#endif
    fln::rand::RandomGenerator rng;
    CHRONOMETER_DURATION(, "", 1, 1);// warmup
    CHRONOMETER_ESTIMATE_CORRECTION(rng.getRandomF64(-1e15,1e15))
    CHRONOMETER_ITERATION(std::abs(rng.getRandomF64(-1e15,1e15))          , "std::abs         (dbl)", 5)
    CHRONOMETER_ITERATION(fln::object::abs(fln::object::BitDouble(rng.getRandomF64(-1e15,1e15)))      , "fln::object::abs (dbl)", 10)
    CHRONOMETER_ITERATION(fln::bithack::abs(rng.getRandomF64(-1e15,1e15)) , "fln::bithack::abs(dbl)", 10)
    CHRONOMETER_ITERATION(fln::_union::abs(rng.getRandomF64(-1e15,1e15))  , "fln::_union::abs (dbl)", 10)
    CHRONOMETER_ITERATION(fln::ternary::abs(rng.getRandomF64(-1e15,1e15)) , "fln::ternary::abs(dbl)", 10)
    CHRONOMETER_ITERATION(std::abs(rng.getRandomF32(-1e15,1e15))          , "std::abs              ", 30)
    CHRONOMETER_ITERATION(fln::object::abs(fln::object::BitFloat(rng.getRandomF32(-1e15,1e15)))       , "fln::object::abs      ", 10)
    CHRONOMETER_ITERATION(fln::bithack::abs(rng.getRandomF32(-1e15,1e15)) , "fln::bithack::abs     ", 10)
    CHRONOMETER_ITERATION(fln::_union::abs(rng.getRandomF32(-1e15,1e15))  , "fln::_union::abs      ", 10)
    CHRONOMETER_ITERATION(fln::ternary::abs(rng.getRandomF32(-1e15,1e15)), "fln::ternary::abs     ", 10)

#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== END ABS ===---" << std::endl;
#endif
}
TEST(algo_benchmark_rand, log2) {
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== BENCHMARK LOG2 ===---" << std::endl;
    // performance
    std::cout << "log2 performance review " << configName << std::endl;
#endif
    fln::rand::RandomGenerator rng;
    CHRONOMETER_DURATION(, "", 1, 1);// warmup
    CHRONOMETER_ESTIMATE_CORRECTION(rng.getRandomF64(0,1e15))
    CHRONOMETER_ITERATION(std::log2(rng.getRandomF64(0,1e15))          , "std::log2         (dbl)", 5)
    CHRONOMETER_ITERATION(fln::object::log2(fln::object::BitDouble(rng.getRandomF64(0,1e15)))     , "fln::object::log2 (dbl)", 10)
    CHRONOMETER_ITERATION(fln::object::log2a(fln::object::BitDouble(rng.getRandomF64(0,1e15)))    , "fln::object::log2a(dbl)", 10)
    CHRONOMETER_ITERATION(fln::bithack::log2(rng.getRandomF64(0,1e15)) , "fln::bithack::log2(dbl)", 10)
    CHRONOMETER_ITERATION(fln::_union::log2(rng.getRandomF64(0,1e15))  , "fln::_union::log2 (dbl)", 10)
    CHRONOMETER_ITERATION(std::log2f(rng.getRandomF32(0,1e15))        , "std::log2              ", 30)
    CHRONOMETER_ITERATION(fln::object::log2(fln::object::BitFloat(rng.getRandomF32(0,1e15)))      , "fln::object::log2      ", 10)
    CHRONOMETER_ITERATION(fln::object::log2a(fln::object::BitFloat(rng.getRandomF32(0,1e15)))     , "fln::object::log2a     ", 10)
    CHRONOMETER_ITERATION(fln::bithack::log2(rng.getRandomF32(0,1e15)), "fln::bithack::log2     ", 10)
    CHRONOMETER_ITERATION(fln::_union::log2(rng.getRandomF32(0,1e15)) , "fln::_union::log2      ", 10)
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== END LOG2 ===---" << std::endl;
#endif
}

TEST(algo_benchmark_rand, exp2) {
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== BENCHMARK EXP2 ===---" << std::endl;
    std::cout << "exp2 performance review " << configName << std::endl;
#endif
    fln::rand::RandomGenerator rng;
    CHRONOMETER_DURATION(, "", 1, 1);// warmup
    CHRONOMETER_ITERATION(std::exp2(rng.getRandomF64(1,1e15))          , "std::exp2         (dbl)", 5)
    CHRONOMETER_ITERATION(fln::object::exp2(fln::object::BitDouble(rng.getRandomF64(1,1e15)))     , "fln::object::exp2 (dbl)", 15)
    CHRONOMETER_ITERATION(fln::bithack::exp2(rng.getRandomF64(1,1e15)) , "fln::bithack::exp2(dbl)", 10)
    CHRONOMETER_ITERATION(fln::_union::exp2(rng.getRandomF64(1,1e15))  , "fln::_union::exp2 (dbl)", 10)
    CHRONOMETER_ITERATION(std::exp2f(rng.getRandomF32(1,1e15))        , "std::exp2              ", 300)
    CHRONOMETER_ITERATION(fln::object::exp2(fln::object::BitFloat(rng.getRandomF32(1,1e15)))      , "fln::object::exp2      ", 15)
    CHRONOMETER_ITERATION(fln::bithack::exp2(rng.getRandomF32(1,1e15)), "fln::bithack::exp2     ", 10)
    CHRONOMETER_ITERATION(fln::_union::exp2(rng.getRandomF32(1,1e15)) , "fln::_union::exp2      ", 10)
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== END EXP2 ===---" << std::endl;
#endif
}

TEST(algo_benchmark_rand, pow) {
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== BENCHMARK POW ===---" << std::endl;
    std::cout << "pow performance review " << configName << std::endl;
#endif
    fln::object::BitFloat f(150.0f);
    fln::object::BitFloat p(1.25f);
    fln::object::BitDouble fd(150.0);
    fln::object::BitDouble pd(1.25);
    CHRONOMETER_DURATION(, "", 1            , 1);// warmup
    CHRONOMETER_ITERATION(std::pow(150.0, 1.25)           , "std::pow         (dbl)", 5)
    CHRONOMETER_ITERATION(fln::object::pow(fd, pd)        , "fln::object::pow (dbl)", 15)
    CHRONOMETER_ITERATION(fln::bithack::pow(150.0, 1.25)  , "fln::bithack::pow(dbl)", 10)
    CHRONOMETER_ITERATION(fln::_union::pow(150.0, 1.25)   , "fln::_union::pow (dbl)", 10)
    CHRONOMETER_ITERATION(std::pow(150.0f, 1.25f)         , "std::pow              ", 300)
    CHRONOMETER_ITERATION(fln::object::pow(f, p)          , "fln::object::pow      ", 15)
    CHRONOMETER_ITERATION(fln::bithack::pow(150.0f, 1.25f), "fln::bithack::pow     ", 10)
    CHRONOMETER_ITERATION(fln::_union::pow(150.0f, 1.25f) , "fln::_union::pow      ", 10)
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== END POW ===---" << std::endl;
#endif
}

TEST(algo_benchmark_rand, sqrt) {
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== BENCHMARK SQRT ===---" << std::endl;
    std::cout << "sqrt performance review " << configName << std::endl;
#endif
    fln::object::BitDouble fd(150.0);
    fln::object::BitFloat f(150.0f);
    CHRONOMETER_DURATION(, "", 1, 1);// warmup
    CHRONOMETER_ITERATION(std::sqrt(150.0)               , "std::sqrt              (dbl)", 5)
    CHRONOMETER_ITERATION(fln::bithack::sqrt(150.0 )     , "fln::bithack::sqrt     (dbl)", 10)
    CHRONOMETER_ITERATION(fln::bithack::sqrt_pow(150.0 ) , "fln::bithack::sqrt_pow (dbl)", 10)
    CHRONOMETER_ITERATION(fln::bithack::sqrt_b(150.0 )   , "fln::bithack::sqrt_b   (dbl)", 10)
    CHRONOMETER_ITERATION(fln::_union::sqrt(150.0 )      , "fln::_union::sqrt      (dbl)", 10)
    CHRONOMETER_ITERATION(fln::_union::sqrt_pow(150.0 )  , "fln::_union::sqrt_pow  (dbl)", 10)
    CHRONOMETER_ITERATION(fln::_union::sqrt_b(150.0 )    , "fln::_union::sqrt_b    (dbl)", 10)
    CHRONOMETER_ITERATION(std::sqrt(150.0f)              , "std::sqrt                   ", 300)
    CHRONOMETER_ITERATION(fln::bithack::sqrt(150.0f)     , "fln::bithack::sqrt          ", 10)
    CHRONOMETER_ITERATION(fln::bithack::sqrt_pow(150.0f) , "fln::bithack::sqrt_pow      ", 10)
    CHRONOMETER_ITERATION(fln::bithack::sqrt_b(150.0f)   , "fln::bithack::sqrt_b        ", 10)
    CHRONOMETER_ITERATION(fln::_union::sqrt(150.0f)      , "fln::_union::sqrt           ", 10)
    CHRONOMETER_ITERATION(fln::_union::sqrt_pow(150.0f)  , "fln::_union::sqrt_pow       ", 10)
    CHRONOMETER_ITERATION(fln::_union::sqrt_b(150.0f)    , "fln::_union::sqrt_b         ", 10)
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== END SQRT ===---" << std::endl;
#endif
}


TEST(algo_benchmark_rand, inverse_sqrt) {
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== BENCHMARK INVERSE SQRT ===---" << std::endl;
    std::cout << "invrse sqrt performance review " << configName << std::endl;
#endif
    fln::object::BitDouble fd(150.0);
    fln::object::BitFloat f(150.0f);
    CHRONOMETER_DURATION(, "", 1, 1);// warmup
    CHRONOMETER_ITERATION(1.0/std::sqrt(150.0)              , "1.0/std::sqrt            (dbl)", 5)
    CHRONOMETER_ITERATION(1.0/fln::bithack::sqrt(150.0 )    , "1.0/fln::bithack::sqrt   (dbl)", 10)
    CHRONOMETER_ITERATION(1.0/fln::_union::sqrt(150.0 )     , "1.0/fln::_union::sqrt    (dbl)", 10)
    CHRONOMETER_ITERATION(1.0f/std::sqrt(150.0f)            , "1.0f/std::sqrt                ", 300)
    CHRONOMETER_ITERATION(1.0f/fln::bithack::sqrt(150.0f)   , "1.0f/fln::bithack::sqrt       ", 10)
    CHRONOMETER_ITERATION(fln::bithack::rsqrt_quake(150.0f) , "fln::bithack::rsqrt_quake     ", 10)
    CHRONOMETER_ITERATION(1.0f/fln::_union::sqrt(150.0f)    , "1.0f/fln::_union::sqrt        ", 10)
    CHRONOMETER_ITERATION(fln::_union::rsqrt_quake(150.0f)  , "fln::_union::rsqrt_quake      ", 10)
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== END INVERSE SQRT ===---" << std::endl;
#endif
}


#pragma GCC diagnostic pop
