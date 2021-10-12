#include <gtest/gtest.h>

#define IDEBUG
#include "baseDefines.h"
#include "FloatFunctions.h"
#include <cmath>
#include <numeric>

#pragma GCC diagnostic push

TEST(float_functions, log2){
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== TESTING LOG2 ===---" << std::endl;
#endif
    std::vector<fln::f32> numbers ={};
    for (fln::f32 i=-25.0;i<26.0;i+=0.001){
        numbers.push_back(std::pow(10.0,i));
    }
    std::vector<fln::f32> errors ={};
    for (auto& n:numbers){
        fln::object::BitFloat f(n);
        EXPECT_NEAR(std::log2(f.fl()), fln::object::log2(f), 0.1);
        errors.push_back(fln::object::log2(f) - std::log2(f.fl()));
    }
    fln::f32 mean = std::reduce(errors.begin(), errors.end()) / static_cast<fln::f32>(errors.size());
    fln::f32 sq_sum = std::inner_product(errors.begin(), errors.end(), errors.begin(), 0.0);
    fln::f32 stdev = std::sqrt(sq_sum / errors.size() - mean * mean);
    EXPECT_LT(mean, 0.05);
    EXPECT_LT(stdev, 0.05);
#ifdef FLN_VERBOSE_TEST
    std::cout << "average absolute error of internal log 2: " << mean << " standard deviation: " << stdev << std::endl;
    std::cout << "---=== END LOG2 ===---" << std::endl;
#endif
}

TEST(float_functions, exp2){
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== TESTING EXP2 ===---" << std::endl;
#endif
    std::vector<fln::f32> numbers ={};
    for (fln::f32 i=-80.0;i<80.0;i+=0.1){
        numbers.push_back(i);
    }
    std::vector<fln::f32> errors ={};
    for (auto& n:numbers){
        fln::object::BitFloat f(n);
        EXPECT_NEAR(std::exp2(f.fl()), fln::object::exp2(f), 0.1*std::exp2(f.fl()));
        errors.push_back((fln::object::exp2(f) - std::exp2(f.fl()))/std::exp2(f.fl()));
    }
    fln::f32 mean = std::reduce(errors.begin(), errors.end()) / static_cast<fln::f32>(errors.size());
    fln::f32 sq_sum = std::inner_product(errors.begin(), errors.end(), errors.begin(), 0.0);
    fln::f32 stdev = std::sqrt(sq_sum / errors.size() - mean * mean);
    EXPECT_LT(mean, 0.05);
    EXPECT_LT(stdev, 0.05);
#ifdef FLN_VERBOSE_TEST
    std::cout << "average relative error of internal log 2: " << mean << " standard deviation: " << stdev << std::endl;
    std::cout << "---=== END EXP2 ===---" << std::endl;
#endif
}

#pragma GCC diagnostic pop
