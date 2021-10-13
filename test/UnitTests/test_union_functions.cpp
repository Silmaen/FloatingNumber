#include <gtest/gtest.h>

#define IDEBUG
#include "union_Functions.h"
#include <baseFunctions.h>
#include <cmath>
#include <numeric>

using namespace fln::_union;

TEST(union_functions,sign_float) {
    float a= -15.0f, b= 118.0f;
    EXPECT_TRUE(isNegative(a));
    EXPECT_FALSE(isNegative(b));
    EXPECT_FALSE(isNegative(negate(a)));
    EXPECT_TRUE(isNegative(negate(b)));
    EXPECT_FALSE(isNegative(fln::_union::abs(a)));
    EXPECT_FALSE(isNegative(fln::_union::abs(b)));
}
TEST(union_functions,sign_double) {
    double ad=-15.0f,bd= 118.0f;
    EXPECT_TRUE(isNegative(ad));
    EXPECT_FALSE(isNegative(bd));
    EXPECT_FALSE(isNegative(negate(ad)));
    EXPECT_TRUE(isNegative(negate(bd)));
    EXPECT_FALSE(isNegative(fln::_union::abs(ad)));
    EXPECT_FALSE(isNegative(fln::_union::abs(bd)));
}

TEST(union_functions,log2_float) {
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== TESTING BITHACK LOG2 ===---" << std::endl;
#endif
    std::vector<fln::f32> numbers ={};
    for (fln::f32 i=-25.0;i<26.0;i+=0.1){
        numbers.push_back(std::pow(10.0,i));
    }
    std::vector<fln::f32> errors ={};
    for (auto& n:numbers){
        EXPECT_NEAR(std::log2(n), fln::_union::log2(n), 0.1);
        errors.push_back(fln::_union::log2(n) - std::log2(n));
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

TEST(union_functions,log2_double) {
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== TESTING BITHACK LOG2 (double) ===---" << std::endl;
#endif
    std::vector<fln::f64> numbers ={};
    for (fln::f64 i=-25.0;i<26.0;i+=0.001){
        numbers.push_back(std::pow(10.0,i));
    }
    std::vector<fln::f64> errors ={};
    for (auto& n:numbers){
        EXPECT_NEAR(std::log2(n), fln::_union::log2(n), 0.1);
        errors.push_back(fln::_union::log2(n) - std::log2(n));
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

TEST(union_functions,exp2_float) {
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== TESTING BITHACK EXP2 ===---" << std::endl;
#endif
    std::vector<fln::f32> numbers ={};
    for (fln::f32 i=-80.0;i<80.0;i+=0.1){
        numbers.push_back(i);
    }
    std::vector<fln::f32> errors ={};
    for (auto& n:numbers){
        EXPECT_NEAR(std::exp2(n), fln::_union::exp2(n), 0.1*std::exp2(n));
        errors.push_back((fln::_union::exp2(n) - std::exp2(n))/std::exp2(n));
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

TEST(union_functions,exp2_double) {
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== TESTING BITHACK EXP2 (double) ===---" << std::endl;
#endif
    std::vector<fln::f64> numbers ={};
    for (fln::f64 i=-80.0;i<80.0;i+=0.1){
        numbers.push_back(i);
    }
    std::vector<fln::f64> errors ={};
    for (auto& n:numbers){
        EXPECT_NEAR(std::exp2(n), fln::_union::exp2(n), 0.1*std::exp2(n));
        errors.push_back((fln::_union::exp2(n) - std::exp2(n))/std::exp2(n));
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

TEST(union_functions,pow_float) {
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== TESTING BITHACK POW ===---" << std::endl;
#endif
    std::vector<std::pair<fln::f32,fln::f32> > numbers ={};
    for (fln::f32 i=1;i<100.0;i+=7.6345){
        for (fln::f32 j=-5.0;j<5.0;j+=0.4) {
            numbers.emplace_back(i, j);
        }
    }
    std::vector<fln::f32> errors ={};
    for (auto& n:numbers){
        EXPECT_NEAR(std::pow(n.first,n.second), fln::_union::pow(n.first,n.second), fln::ternary::max(0.001,0.5*std::pow(n.first,n.second)));
        errors.push_back((fln::_union::pow(n.first,n.second) - std::pow(n.first,n.second))/std::pow(n.first,n.second));
    }
    fln::f32 mean = std::reduce(errors.begin(), errors.end()) / static_cast<fln::f32>(errors.size());
    fln::f32 sq_sum = std::inner_product(errors.begin(), errors.end(), errors.begin(), 0.0);
    fln::f32 stdev = std::sqrt(sq_sum / errors.size() - mean * mean);
    EXPECT_LT(mean, 0.05);
    EXPECT_LT(stdev, 0.13);
#ifdef FLN_VERBOSE_TEST
    std::cout << "average relative error of bithack pow: " << mean << " standard deviation: " << stdev << std::endl;
    std::cout << "---=== END BITHACK POW ===---" << std::endl;
#endif
}

TEST(union_functions,pow_double) {
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== TESTING BITHACK POW (double) ===---" << std::endl;
#endif
    std::vector<std::pair<fln::f64,fln::f64> > numbers ={};
    for (fln::f64 i=1;i<100.0;i+=7.6345){
        for (fln::f64 j=-5.0;j<5.0;j+=0.4) {
            numbers.emplace_back(i, j);
        }
    }
    std::vector<fln::f64> errors ={};
    for (auto& n:numbers){
        EXPECT_NEAR(std::pow(n.first,n.second), fln::_union::pow(n.first,n.second), fln::ternary::max(0.001,0.5*std::pow(n.first,n.second)));
        errors.push_back((fln::_union::pow(n.first,n.second) - std::pow(n.first,n.second))/std::pow(n.first,n.second));
    }
    fln::f64 mean = std::reduce(errors.begin(), errors.end()) / static_cast<fln::f64>(errors.size());
    fln::f64 sq_sum = std::inner_product(errors.begin(), errors.end(), errors.begin(), 0.0);
    fln::f64 stdev = std::sqrt(sq_sum / errors.size() - mean * mean);
    EXPECT_LT(mean, 0.05);
    EXPECT_LT(stdev, 0.15);
#ifdef FLN_VERBOSE_TEST
    std::cout << "average relative error of bithack pow (double): " << mean << " standard deviation: " << stdev << std::endl;
    std::cout << "---=== END BITHACK POW (double) ===---" << std::endl;
#endif
}


TEST(union_functions,sqrt_float) {
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== TESTING BITHACK SQRT ===---" << std::endl;
#endif
    std::vector<fln::f32> numbers ={};
    for (fln::f32 i=0.0;i<80.0;i+=0.1){
        numbers.push_back(i);
    }
    std::vector<fln::f32> errors ={};
    for (auto& n:numbers){
        EXPECT_NEAR(std::sqrt(n), fln::_union::sqrt(n), fln::ternary::max(0.0001,0.1*std::sqrt(n)));
        errors.push_back((fln::_union::sqrt(n) - std::sqrt(n))/fln::ternary::max(0.0001,(fln::f64)std::sqrt(n)));
    }
    fln::f32 mean = std::reduce(errors.begin(), errors.end()) / static_cast<fln::f32>(errors.size());
    fln::f32 sq_sum = std::inner_product(errors.begin(), errors.end(), errors.begin(), 0.0);
    fln::f32 stdev = std::sqrt(sq_sum / errors.size() - mean * mean);
    EXPECT_LT(mean, 0.05);
    EXPECT_LT(stdev, 0.05);
#ifdef FLN_VERBOSE_TEST
    std::cout << "average relative error of bithack sqrt: " << mean << " standard deviation: " << stdev << std::endl;
    std::cout << "---=== END BITHACK SQRT ===---" << std::endl;
#endif
}

TEST(union_functions,sqrt_double) {
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== TESTING BITHACK SQRT (double) ===---" << std::endl;
#endif
    std::vector<fln::f64> numbers ={};
    for (fln::f64 i=0.0;i<80.0;i+=0.1){
        numbers.push_back(i);
    }
    std::vector<fln::f64> errors ={};
    for (auto& n:numbers){
        EXPECT_NEAR(std::sqrt(n), fln::_union::sqrt(n), fln::ternary::max(0.0001,0.1*std::sqrt(n)));
        errors.push_back((fln::_union::sqrt(n) - std::sqrt(n))/fln::ternary::max(0.0001,(fln::f64)std::sqrt(n)));
    }
    fln::f64 mean = std::reduce(errors.begin(), errors.end()) / static_cast<fln::f64>(errors.size());
    fln::f64 sq_sum = std::inner_product(errors.begin(), errors.end(), errors.begin(), 0.0);
    fln::f64 stdev = std::sqrt(sq_sum / errors.size() - mean * mean);
    EXPECT_LT(mean, 0.05);
    EXPECT_LT(stdev, 0.05);
#ifdef FLN_VERBOSE_TEST
    std::cout << "average relative error of bithack sqrt (double): " << mean << " standard deviation: " << stdev << std::endl;
    std::cout << "---=== END BITHACK SQRT (double) ===---" << std::endl;
#endif
}

TEST(union_functions,sqrt_pow_float) {
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== TESTING BITHACK SQRT_POW ===---" << std::endl;
#endif
    std::vector<fln::f32> numbers ={};
    for (fln::f32 i=0.0;i<80.0;i+=0.1){
        numbers.push_back(i);
    }
    std::vector<fln::f32> errors ={};
    for (auto& n:numbers){
        EXPECT_NEAR(std::sqrt(n), fln::_union::sqrt_pow(n), fln::ternary::max(0.0001,0.1*std::sqrt(n)));
        errors.push_back((fln::_union::sqrt_pow(n) - std::sqrt(n))/fln::ternary::max(0.0001,(fln::f64)std::sqrt(n)));
    }
    fln::f32 mean = std::reduce(errors.begin(), errors.end()) / static_cast<fln::f32>(errors.size());
    fln::f32 sq_sum = std::inner_product(errors.begin(), errors.end(), errors.begin(), 0.0);
    fln::f32 stdev = std::sqrt(sq_sum / errors.size() - mean * mean);
    EXPECT_LT(mean, 0.05);
    EXPECT_LT(stdev, 0.05);
#ifdef FLN_VERBOSE_TEST
    std::cout << "average relative error of bithack sqrt_pow: " << mean << " standard deviation: " << stdev << std::endl;
    std::cout << "---=== END BITHACK SQRT_POW ===---" << std::endl;
#endif
}

TEST(union_functions,sqrt_pow_double) {
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== TESTING BITHACK SQRT_POW (double) ===---" << std::endl;
#endif
    std::vector<fln::f64> numbers ={};
    for (fln::f64 i=0.0;i<80.0;i+=0.1){
        numbers.push_back(i);
    }
    std::vector<fln::f64> errors ={};
    for (auto& n:numbers){
        EXPECT_NEAR(std::sqrt(n), fln::_union::sqrt_pow(n), fln::ternary::max(0.0001,0.1*std::sqrt(n)));
        errors.push_back((fln::_union::sqrt_pow(n) - std::sqrt(n))/fln::ternary::max(0.0001,(fln::f64)std::sqrt(n)));
    }
    fln::f64 mean = std::reduce(errors.begin(), errors.end()) / static_cast<fln::f64>(errors.size());
    fln::f64 sq_sum = std::inner_product(errors.begin(), errors.end(), errors.begin(), 0.0);
    fln::f64 stdev = std::sqrt(sq_sum / errors.size() - mean * mean);
    EXPECT_LT(mean, 0.05);
    EXPECT_LT(stdev, 0.05);
#ifdef FLN_VERBOSE_TEST
    std::cout << "average relative error of bithack sqrt_pow(double): " << mean << " standard deviation: " << stdev << std::endl;
    std::cout << "---=== END BITHACK SQRT_POW(double) ===---" << std::endl;
#endif
}

TEST(union_functions,sqrt_b) {
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== TESTING BITHACK SQRT_B ===---" << std::endl;
#endif
    std::vector<fln::f32> numbers ={};
    for (fln::f32 i=0.0;i<80.0;i+=0.1){
        numbers.push_back(i);
    }
    std::vector<fln::f32> errors ={};
    for (auto& n:numbers){
        EXPECT_NEAR(std::sqrt(n), fln::_union::sqrt_b(n), fln::ternary::max(0.0001,0.1*std::sqrt(n)));
        errors.push_back((fln::_union::sqrt_b(n) - std::sqrt(n))/fln::ternary::max(0.0001,(fln::f64)std::sqrt(n)));
    }
    fln::f32 mean = std::reduce(errors.begin(), errors.end()) / static_cast<fln::f32>(errors.size());
    fln::f32 sq_sum = std::inner_product(errors.begin(), errors.end(), errors.begin(), 0.0);
    fln::f32 stdev = std::sqrt(sq_sum / errors.size() - mean * mean);
    EXPECT_LT(mean, 0.05);
    EXPECT_LT(stdev, 0.05);
#ifdef FLN_VERBOSE_TEST
    std::cout << "average relative error of bithack sqrt_b: " << mean << " standard deviation: " << stdev << std::endl;
    std::cout << "---=== END BITHACK SQRT_B ===---" << std::endl;
#endif
}

#pragma GCC diagnostic pop
