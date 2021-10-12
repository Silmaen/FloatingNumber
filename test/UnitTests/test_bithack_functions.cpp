#include <gtest/gtest.h>

#define IDEBUG
#include "bithack_Functions.h"
#include "testHelper.h"
#include <baseFunctions.h>
#include <cmath>
#include <numeric>

using namespace fln::bithack;

TEST(bithack_functions,sign_float) {
    float a= -15.0f, b= 118.0f;
    EXPECT_TRUE(isNegative(a));
    EXPECT_FALSE(isNegative(b));
    EXPECT_FALSE(isNegative(negate(a)));
    EXPECT_TRUE(isNegative(negate(b)));
    EXPECT_FALSE(isNegative(fln::bithack::abs(a)));
    EXPECT_FALSE(isNegative(fln::bithack::abs(b)));
}
TEST(bithack_functions,sign_double) {
    double ad=-15.0f,bd= 118.0f;
    EXPECT_TRUE(isNegative(ad));
    EXPECT_FALSE(isNegative(bd));
    EXPECT_FALSE(isNegative(negate(ad)));
    EXPECT_TRUE(isNegative(negate(bd)));
    EXPECT_FALSE(isNegative(fln::bithack::abs(ad)));
    EXPECT_FALSE(isNegative(fln::bithack::abs(bd)));
}

TEST(bithack_functions,log2_float) {
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== TESTING BITHACK LOG2 ===---" << std::endl;
#endif
    std::vector<fln::f32> numbers ={};
    for (fln::f32 i=-25.0;i<26.0;i+=0.1){
        numbers.push_back(std::pow(10.0,i));
    }
    std::vector<fln::f32> errors ={};
    for (auto& n:numbers){
        EXPECT_NEAR(std::log2(n), fln::bithack::log2(n), 0.1);
        errors.push_back(fln::bithack::log2(n) - std::log2(n));
    }
    fln::f32 mean = std::reduce(errors.begin(), errors.end()) / static_cast<fln::f32>(errors.size());
    fln::f32 sq_sum = std::inner_product(errors.begin(), errors.end(), errors.begin(), 0.0);
    fln::f32 stdev = std::sqrt(sq_sum / errors.size() - mean * mean);
    EXPECT_LT(mean, 0.05);
    EXPECT_LT(stdev, 0.05);
#ifdef FLN_VERBOSE_TEST
    std::cout << "average absolute error of bithack log 2: " << mean << " standard deviation: " << stdev << std::endl;
    std::cout << "---=== END BITHACK LOG2 ===---" << std::endl;
#endif
}

TEST(bithack_functions,log2_double) {
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== TESTING BITHACK LOG2 (double) ===---" << std::endl;
#endif
    std::vector<fln::f64> numbers ={};
    for (fln::f64 i=-25.0;i<26.0;i+=0.001){
        numbers.push_back(std::pow(10.0,i));
    }
    std::vector<fln::f64> errors ={};
    for (auto& n:numbers){
        EXPECT_NEAR(std::log2(n), fln::bithack::log2(n), 0.1);
        errors.push_back(fln::bithack::log2(n) - std::log2(n));
    }
    fln::f64 mean = std::reduce(errors.begin(), errors.end()) / static_cast<fln::f64>(errors.size());
    fln::f64 sq_sum = std::inner_product(errors.begin(), errors.end(), errors.begin(), 0.0);
    fln::f64 stdev = std::sqrt(sq_sum / errors.size() - mean * mean);
    EXPECT_LT(mean, 0.05);
    EXPECT_LT(stdev, 0.05);
#ifdef FLN_VERBOSE_TEST
    std::cout << "average absolute error of bithack log 2 (double): " << mean << " standard deviation: " << stdev << std::endl;
    std::cout << "---=== END BITHACK LOG2 (double) ===---" << std::endl;
#endif
}

TEST(bithack_functions,exp2_float) {
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== TESTING BITHACK EXP2 ===---" << std::endl;
#endif
    std::vector<fln::f32> numbers ={};
    for (fln::f32 i=-80.0;i<80.0;i+=0.1){
        numbers.push_back(i);
    }
    std::vector<fln::f32> errors ={};
    for (auto& n:numbers){
        EXPECT_NEAR(std::exp2(n), fln::bithack::exp2(n), 0.1*std::exp2(n));
        errors.push_back((fln::bithack::exp2(n) - std::exp2(n))/std::exp2(n));
    }
    fln::f32 mean = std::reduce(errors.begin(), errors.end()) / static_cast<fln::f32>(errors.size());
    fln::f32 sq_sum = std::inner_product(errors.begin(), errors.end(), errors.begin(), 0.0);
    fln::f32 stdev = std::sqrt(sq_sum / errors.size() - mean * mean);
    EXPECT_LT(mean, 0.05);
    EXPECT_LT(stdev, 0.05);
#ifdef FLN_VERBOSE_TEST
    std::cout << "average relative error of bithack log 2: " << mean << " standard deviation: " << stdev << std::endl;
    std::cout << "---=== END BITHACK EXP2 ===---" << std::endl;
#endif
}

TEST(bithack_functions,exp2_double) {
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== TESTING BITHACK EXP2 (double) ===---" << std::endl;
#endif
    std::vector<fln::f64> numbers ={};
    for (fln::f64 i=-80.0;i<80.0;i+=0.1){
        numbers.push_back(i);
    }
    std::vector<fln::f64> errors ={};
    for (auto& n:numbers){
        EXPECT_NEAR(std::exp2(n), fln::bithack::exp2(n), 0.1*std::exp2(n));
        errors.push_back((fln::bithack::exp2(n) - std::exp2(n))/std::exp2(n));
    }
    fln::f64 mean = std::reduce(errors.begin(), errors.end()) / static_cast<fln::f64>(errors.size());
    fln::f64 sq_sum = std::inner_product(errors.begin(), errors.end(), errors.begin(), 0.0);
    fln::f64 stdev = std::sqrt(sq_sum / errors.size() - mean * mean);
    EXPECT_LT(mean, 0.05);
    EXPECT_LT(stdev, 0.05);
#ifdef FLN_VERBOSE_TEST
    std::cout << "average relative error of bithack log 2 (double): " << mean << " standard deviation: " << stdev << std::endl;
    std::cout << "---=== END BITHACK EXP2 (double) ===---" << std::endl;
#endif
}

#pragma GCC diagnostic pop
