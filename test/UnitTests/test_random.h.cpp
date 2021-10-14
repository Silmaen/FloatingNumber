#include <gtest/gtest.h>

#define IDEBUG
#include "rng.h"

using namespace fln::rand;

TEST(random, unsigned16){
    RandomGenerator rng(1234);
    fln::u64 mi = 10000;
    fln::u64 ma = 20000;
    std::vector<fln::u16> vals;
    for(fln::u32 a=0;a<10000;++a) {
        fln::u16 b = rng.getRandomU16(mi, ma);
        vals.push_back(b);
        EXPECT_GE(b, mi);
        EXPECT_LE(b, ma);

    }
    fln::f64 mean = static_cast<fln::f64>(std::reduce(vals.begin(), vals.end())) / static_cast<fln::f64>(vals.size());
    std::cout << mean << " " << std::reduce(vals.begin(), vals.end()) << " / " << static_cast<fln::f64>(vals.size()) << std::endl;
    fln::f64 sq_sum = std::inner_product(vals.begin(), vals.end(), vals.begin(), 0.0);
    fln::f64 stdev = std::sqrt(sq_sum / vals.size() - mean * mean);
    EXPECT_NEAR(mean, 0.5*(mi+ma), 100);
    EXPECT_LT(stdev, 0.05);
}

TEST(random, unsigned32){
    RandomGenerator rng(1234);
    fln::u64 mi = 10000000;
    fln::u64 ma = 10000000;
    std::vector<fln::u32> vals;
    for(fln::u32 a=0;a<10000;++a) {
        fln::u32 b = rng.getRandomU32(mi, ma);
        vals.push_back(b);
        EXPECT_GE(b, mi);
        EXPECT_LE(b, ma);
    }
    fln::f64 mean = static_cast<fln::f64>(std::reduce(vals.begin(), vals.end())) / static_cast<fln::f64>(vals.size());
    fln::f64 sq_sum = std::inner_product(vals.begin(), vals.end(), vals.begin(), 0.0);
    fln::f64 stdev = std::sqrt(sq_sum / vals.size() - mean * mean);
    EXPECT_NEAR(mean, 0.5*(mi+ma), 100);
    EXPECT_LT(stdev, 0.05);
}

TEST(random, unsigned64){
    RandomGenerator rng(1234);
    std::vector<fln::u64> vals;
    fln::u64 mi = 10000000000000;
    fln::u64 ma = 10000000000000;
    for(fln::u32 a=0;a<10000;++a) {
        fln::u64 b = rng.getRandomU64(mi, ma);
        std::cout << b << std::endl;
        vals.push_back(b);
        EXPECT_GE(b, mi);
        EXPECT_LE(b, ma);
    }
    fln::f64 mean = std::reduce(vals.begin(), vals.end()) / static_cast<fln::f64>(vals.size());
    fln::f64 sq_sum = std::inner_product(vals.begin(), vals.end(), vals.begin(), 0.0);
    fln::f64 stdev = std::sqrt(sq_sum / vals.size() - mean * mean);
    EXPECT_NEAR(mean, 0.5*(mi+ma), 100);
    EXPECT_LT(stdev, 0.05);
}
