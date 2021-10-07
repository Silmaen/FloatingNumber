#include <gtest/gtest.h>

//#define IDEBUG
#include <baseFunctions.h>
#include "trickFunctions.h"
#include "testHelper.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

TEST(cg_trick,abs_measure){
    {
        float a=9.f;
        float b=-9.f;
        float tol = 0.00001f;
        EXPECT_NEAR(fln::abs(a),a,tol);
        EXPECT_NEAR(fln::abs(b),a,tol);
        EXPECT_NEAR(std::abs(a),a,tol);
        EXPECT_NEAR(std::abs(b),a,tol);
        EXPECT_NEAR((a<0)?-a:a,a,tol);
        EXPECT_NEAR((b<0)?-b:b,a,tol);
        EXPECT_NEAR((a<0)?fln::negate(a):a,a,tol);
        EXPECT_NEAR((b<0)?fln::negate(b):b,a,tol);
        EXPECT_NEAR(fln::fastAbs(a),a,tol);
        EXPECT_NEAR(fln::fastAbs(b),a,tol);
    }

    std::cout << "---=== Profiling abs function ===---" << std::endl;
    CHRONOMETER_DURATION(,,"",1,1); // warmup
    CHRONOMETER_DURATION(c=fln::abs(a),fln::f32 c; fln::f32 a=-1,           "myabs         ", 500, 1000000)
    CHRONOMETER_DURATION(c=std::abs(a),fln::f32 c; fln::f32 a=-1,           "std::abs      ", 500, 1000000)
    CHRONOMETER_DURATION(c=(a<0)?-a:a,fln::f32 c; fln::f32 a=-1,            "ternary       ", 500, 1000000)
    CHRONOMETER_DURATION(c=(a<0)?fln::negate(a):a,fln::f32 c; fln::f32 a=-1,"ternary negate", 500, 1000000)
    CHRONOMETER_DURATION(c=fln::fastAbs(a),fln::f32 c; fln::f32 a=-1,       "fastAbs       ", 500, 1000000)
    std::cout << "---=== Profiling abs functions 5M loops ===---" << std::endl;
    CHRONOMETER_ITERATION(c=fln::abs(a),fln::f32 c; fln::f32 a=-1,           "myabs         ", 5000000, 50.0)
    CHRONOMETER_ITERATION(c=std::abs(a),fln::f32 c; fln::f32 a=-1,           "std::abs      ", 5000000, 50.0)
    CHRONOMETER_ITERATION(c=(a<0)?-a:a,fln::f32 c; fln::f32 a=-1,            "ternary       ", 5000000, 50.0)
    CHRONOMETER_ITERATION(c=(a<0)?fln::negate(a):a,fln::f32 c; fln::f32 a=-1,"ternary negate", 5000000, 50.0)
    CHRONOMETER_ITERATION(c=fln::fastAbs(a),fln::f32 c; fln::f32 a=-1,       "fastAbs       ", 5000000, 50.0)
}

TEST(cg_trick,sqrt_measure){
    {
        float a=9.f;
        float val=3.f;
        float tol = val * 0.05f;
        EXPECT_NEAR(fln::fastSqrt(a),val,tol);
        EXPECT_NEAR(fln::fasterSqrt(a),val,tol);
        EXPECT_NEAR(fln::fasterSqrt2(a),val,tol);
        EXPECT_NEAR(fln::fastersqrt(a),val,tol);
        EXPECT_NEAR(std::sqrt(a),val,tol);
        a=10000.f;
        val=100.f;
        tol = val * 0.05f;
        EXPECT_NEAR(fln::fastSqrt(a),val,tol);
        EXPECT_NEAR(fln::fasterSqrt(a),val,tol);
        EXPECT_NEAR(fln::fasterSqrt2(a),val,tol);
        EXPECT_NEAR(fln::fastersqrt(a),val,tol);
        EXPECT_NEAR(std::sqrt(a),val,tol);
        a=1.f;
        val=1.f;
        tol = val * 0.05f;
        EXPECT_NEAR(fln::fastSqrt(a),val,tol);
        EXPECT_NEAR(fln::fasterSqrt(a),val,tol);
        EXPECT_NEAR(fln::fasterSqrt2(a),val,tol);
        EXPECT_NEAR(fln::fastersqrt(a),val,tol);
        EXPECT_NEAR(std::sqrt(a),val,tol);
    }

    std::cout << "---=== Profiling sqrt functions 500ms executions ===---" << std::endl;
    CHRONOMETER_DURATION(,,"",1,1); // warmup
    CHRONOMETER_DURATION(c=fln::fasterSqrt(a),fln::f32 c; fln::f32 a=9,  "fasterSqrt    ", 500, 1000000)
    CHRONOMETER_DURATION(c=fln::fasterSqrt2(a),fln::f32 c; fln::f32 a=9, "fasterSqrt2   ", 500, 1000000)
    CHRONOMETER_DURATION(c=fln::fastersqrt(a),fln::f32 c; fln::f32 a=9,  "fastersqrt    ", 500, 1000000)
    CHRONOMETER_DURATION(c=std::sqrt(a),fln::f32 c; fln::f32 a=9,        "std::sqrt     ", 500, 1000000)
    CHRONOMETER_DURATION(c=fln::fastSqrt(a),fln::f32 c; fln::f32 a=9,    "fastSqrt      ", 500, 1000000)
    std::cout << "---=== Profiling sqrt functions 5M loops ===---" << std::endl;
    CHRONOMETER_ITERATION(c=fln::fasterSqrt(a),fln::f32 c; fln::f32 a=9,  "fasterSqrt    ", 5000000, 50.0)
    CHRONOMETER_ITERATION(c=fln::fasterSqrt2(a),fln::f32 c; fln::f32 a=9, "fasterSqrt2   ", 5000000, 50.0)
    CHRONOMETER_ITERATION(c=fln::fastersqrt(a),fln::f32 c; fln::f32 a=9,  "fastersqrt    ", 5000000, 50.0)
    CHRONOMETER_ITERATION(c=std::sqrt(a),fln::f32 c; fln::f32 a=9,        "std::sqrt     ", 5000000, 50.0)
    CHRONOMETER_ITERATION(c=fln::fastSqrt(a),fln::f32 c; fln::f32 a=9,    "fastSqrt      ", 5000000, 50.0)
}


#pragma GCC diagnostic pop
