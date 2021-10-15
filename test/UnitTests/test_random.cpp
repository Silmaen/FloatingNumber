#include <gtest/gtest.h>

#define IDEBUG
#include "rng.h"
#include "stdComputeStats.h"

using namespace fln::rand;

TEST(random, unsigned16){
    RandomGenerator rng(1234);
    fln::u64 mi = 10000;
    fln::u64 ma = 20000;
    std::vector<fln::f64> vals;
    for(fln::u32 a=0;a<1000000;++a) {
        fln::u16 b = rng.getRandomU16(mi, ma);
        vals.push_back(b);
        EXPECT_GE(b, mi);
        EXPECT_LE(b, ma);

    }
    auto res = fln::stats::getStats<fln::f64>(vals, true);
    EXPECT_NEAR(res.mean, 0.5*(mi+ma), 0.0005*(mi+ma));
    EXPECT_NEAR(res.stdDeviation, std::sqrt(fln::f64(ma-mi)*fln::f64(ma-mi)/fln::f64(12)),0.0005*(ma-mi));
}

TEST(random, unsigned32){
    RandomGenerator rng(1234);
    fln::u64 mi = 10000000;
    fln::u64 ma = 20000000;
    std::vector<fln::f64> vals;
    for(fln::u32 a=0;a<1000000;++a) {
        fln::u32 b = rng.getRandomU32(mi, ma);
        vals.push_back(b);
        EXPECT_GE(b, mi);
        EXPECT_LE(b, ma);
    }
    auto res = fln::stats::getStats<fln::f64>(vals, true);
    EXPECT_NEAR(res.mean, 0.5*(mi+ma), 0.0005*(mi+ma));
    EXPECT_NEAR(res.stdDeviation, std::sqrt(fln::f64(ma-mi)*fln::f64(ma-mi)/fln::f64(12)),0.0005*(ma-mi));
}

TEST(random, unsigned64){
    RandomGenerator rng(1234);
    std::vector<fln::f64> vals;
    fln::u64 mi = 10000000000000;
    fln::u64 ma = 20000000000000;
    for(fln::u32 a=0;a<1000000;++a) {
        fln::u64 b = rng.getRandomU64(mi, ma);
        vals.push_back(b);
        EXPECT_GE(b, mi);
        EXPECT_LE(b, ma);
    }
    auto res = fln::stats::getStats<fln::f64>(vals, true);
    EXPECT_NEAR(res.mean, 0.5*(mi+ma), 0.0005*(mi+ma));
    EXPECT_NEAR(res.stdDeviation, std::sqrt(fln::f64(ma-mi)*fln::f64(ma-mi)/fln::f64(12)),0.0005*(ma-mi));
}

TEST(random, float32){
    RandomGenerator rng(1234);
    std::vector<fln::f64> vals;
    fln::f32 mi = 10000000000;
    fln::f32 ma = 20000000000;
    for(fln::u32 a=0;a<1000000;++a) {
        fln::f32 b = rng.getRandomU64(mi, ma);
        vals.push_back(b);
        EXPECT_GE(b, mi);
        EXPECT_LE(b, ma);
    }
    auto res = fln::stats::getStats<fln::f64>(vals, true);
    EXPECT_NEAR(res.mean, 0.5*(mi+ma), 0.0005*(mi+ma));
    EXPECT_NEAR(res.stdDeviation, std::sqrt(fln::f64(ma-mi)*fln::f64(ma-mi)/fln::f64(12)),0.0005*(ma-mi));
}


TEST(random, float64){
    RandomGenerator rng(1234);
    std::vector<fln::f64> vals;
    fln::f64 mi = 10000000000000;
    fln::f64 ma = 20000000000000;
    for(fln::u32 a=0;a<1000000;++a) {
        fln::f64 b = rng.getRandomU64(mi, ma);
        vals.push_back(b);
        EXPECT_GE(b, mi);
        EXPECT_LE(b, ma);
    }
    auto res = fln::stats::getStats<fln::f64>(vals, true);
    EXPECT_NEAR(res.mean, 0.5*(mi+ma), 0.0005*(mi+ma));
    EXPECT_NEAR(res.stdDeviation, std::sqrt(fln::f64(ma-mi)*fln::f64(ma-mi)/fln::f64(12)),0.0005*(ma-mi));
}
