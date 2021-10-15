#include <gtest/gtest.h>

#define IDEBUG
#include "stdComputeStats.h"

TEST(stdStats, oneElement){
    std::vector<fln::f32> a{-666.0f};
    auto res=fln::stats::getStats<fln::f32>(a);
    EXPECT_NEAR(res.mean,-666.0,0.001);
    EXPECT_NEAR(res.squareSum,443556.0,0.001);
    EXPECT_NEAR(res.stdDeviation,0.0,0.001);
}


TEST(stdStats, sameElement){
    std::vector<fln::f32> a{23.0f,23.0f,23.0f,23.0f,23.0f,23.0f,23.0f,23.0f};
    auto res=fln::stats::getStats<fln::f32>(a);
    EXPECT_NEAR(res.mean,23.0,0.001);
    EXPECT_NEAR(res.squareSum,4232.0,0.001);
    EXPECT_NEAR(res.stdDeviation,0.0,0.001);
}


TEST(stdStats, setElement_u32){
    std::vector<fln::u32> a{23,23,23,23,23,23,23,23};
    auto res=fln::stats::getStats<fln::u32>(a);
    EXPECT_NEAR(res.mean,23.0,0.001);
    EXPECT_NEAR(res.squareSum,4232.0,0.001);
    EXPECT_NEAR(res.stdDeviation,0.0,0.001);
}


TEST(stdStats, setElements_u32){
    std::vector<fln::f32> a{2300,253,723,823,123,2355,283,4523};
    auto res=fln::stats::getStats<fln::f32>(a);
    EXPECT_NEAR(res.mean,1422.875,0.001);
    EXPECT_NEAR(res.squareSum,32652838.0,0.001);
    EXPECT_NEAR(res.stdDeviation,1434.2355957,0.001);
}
