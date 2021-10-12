#include <gtest/gtest.h>

#define IDEBUG
#include "DoubleFunctions.h"
#include "baseDefines.h"
#include "baseFunctions.h"
#include <cmath>
#include <numeric>

#pragma GCC diagnostic push

TEST(double_functions, log2){
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== TESTING OBJECT LOG2 (double) ===---" << std::endl;
#endif
    std::vector<fln::f64> numbers ={};
    for (fln::f64 i=-25.0;i<26.0;i+=0.001){
        numbers.push_back(std::pow(10.0,i));
    }
    std::vector<fln::f64> errors ={};
    for (auto& n:numbers){
        fln::object::BitDouble f(n);
        EXPECT_NEAR(std::log2(f.fl()), fln::object::log2(f), 0.1);
        errors.push_back(fln::object::log2(f) - std::log2(f.fl()));
    }
    fln::f64 mean = std::reduce(errors.begin(), errors.end()) / static_cast<fln::f64>(errors.size());
    fln::f64 sq_sum = std::inner_product(errors.begin(), errors.end(), errors.begin(), 0.0);
    fln::f64 stdev = std::sqrt(sq_sum / errors.size() - mean * mean);
    EXPECT_LT(mean, 0.05);
    EXPECT_LT(stdev, 0.05);
#ifdef FLN_VERBOSE_TEST
    std::cout << "average absolute error of object log 2 (double): " << mean << " standard deviation: " << stdev << std::endl;
    std::cout << "---=== END OBJECT LOG2 (double) ===---" << std::endl;
#endif
}

TEST(double_functions, exp2){
#ifdef FLN_VERBOSE_TEST
    std::cout << "---=== TESTING OBJECT EXP2 (double) ===---" << std::endl;
#endif
    std::vector<fln::f64> numbers ={};
    for (fln::f64 i=-80.0;i<80.0;i+=0.1){
        numbers.push_back(i);
    }
    std::vector<fln::f64> errors ={};
    for (auto& n:numbers){
        fln::object::BitDouble f(n);
        EXPECT_NEAR(std::exp2(f.fl()), fln::object::exp2(f), 0.1*std::exp2(f.fl()));
        errors.push_back((fln::object::exp2(f) - std::exp2(f.fl()))/std::exp2(f.fl()));
    }
    fln::f64 mean = std::reduce(errors.begin(), errors.end()) / static_cast<fln::f64>(errors.size());
    fln::f64 sq_sum = std::inner_product(errors.begin(), errors.end(), errors.begin(), 0.0);
    fln::f64 stdev = std::sqrt(sq_sum / errors.size() - mean * mean);
    EXPECT_LT(mean, 0.05);
    EXPECT_LT(stdev, 0.05);
#ifdef FLN_VERBOSE_TEST
    std::cout << "average relative error of object log 2 (double): " << mean << " standard deviation: " << stdev << std::endl;
    std::cout << "---=== END OBJECT EXP2 (double) ===---" << std::endl;
#endif
}
TEST(double_functions,pow) {
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
        fln::object::BitDouble f(n.first);
        fln::object::BitDouble p(n.second);
        EXPECT_NEAR(std::pow(n.first,n.second), fln::object::pow(f,p), fln::ternary::max(0.001,0.5*std::pow(n.first,n.second)));
        errors.push_back((fln::object::pow(f,p) - std::pow(n.first,n.second))/std::pow(n.first,n.second));
    }
    fln::f64 mean = std::reduce(errors.begin(), errors.end()) / static_cast<fln::f64>(errors.size());
    fln::f64 sq_sum = std::inner_product(errors.begin(), errors.end(), errors.begin(), 0.0);
    fln::f64 stdev = std::sqrt(sq_sum / errors.size() - mean * mean);
    EXPECT_LT(mean, 0.05);
    EXPECT_LT(stdev, 0.13);
#ifdef FLN_VERBOSE_TEST
    std::cout << "average relative error of bithack pow (double): " << mean << " standard deviation: " << stdev << std::endl;
    std::cout << "---=== END BITHACK POW (double) ===---" << std::endl;
#endif
}

#pragma GCC diagnostic pop
