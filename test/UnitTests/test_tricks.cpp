#include <gtest/gtest.h>

//#define IDEBUG
#include <baseFunctions.h>
#include "trickFunctions.h"
#include "testHelper.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

TEST(cg_trick,abs_measure){
    std::cout << "---=== Profiling abs function ===---" << std::endl;
    CHRONO(,,"",1,1); // warmup
    CHRONO(c=fln::abs(a),fln::f32 c; fln::f32 a=-1,           "myabs         ", 500, 1000000)
    CHRONO(c=std::abs(a),fln::f32 c; fln::f32 a=-1,           "std::abs      ", 500, 1000000)
    CHRONO(c=(a<0)?-a:a,fln::f32 c; fln::f32 a=-1,            "ternary       ", 500, 1000000)
    CHRONO(c=(a<0)?fln::negate(a):a,fln::f32 c; fln::f32 a=-1,"ternary negate", 500, 1000000)
    CHRONO(c=fln::fastAbs(a),fln::f32 c; fln::f32 a=-1,       "fastAbs       ", 500, 1000000)
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

    std::cout << "---=== Profiling sqrt functions ===---" << std::endl;
    CHRONO(,,"",1,1); // warmup
    CHRONO(c=fln::fasterSqrt(a),fln::f32 c; fln::f32 a=9,  "fasterSqrt    ", 500, 1000000)
    CHRONO(c=fln::fasterSqrt2(a),fln::f32 c; fln::f32 a=9, "fasterSqrt2   ", 500, 1000000)
    CHRONO(c=fln::fastersqrt(a),fln::f32 c; fln::f32 a=9,  "fastersqrt    ", 500, 1000000)
    CHRONO(c=std::sqrt(a),fln::f32 c; fln::f32 a=9,        "std::sqrt     ", 500, 1000000)
    CHRONO(c=fln::fastSqrt(a),fln::f32 c; fln::f32 a=9,    "fastSqrt      ", 500, 1000000)
}


#pragma GCC diagnostic pop
