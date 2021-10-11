#include <gtest/gtest.h>

#define IDEBUG
#include "baseDefines.h"
#include "FloatType.h"
#include "trickFunctions.h"
#include "testHelper.h"
#include <cmath>
#include <numeric>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

TEST(FloatType, bases) {
    fln::object::explicitFloat f;
    f= -1789.523f;
//    std::cout << sizeof(f) << std::endl;
//    std::cout << f.asFloat() << " " << f.asUInt() << std::endl;
//    std::cout << f.bits() << std::endl;
//    std::cout << f.sign() << " " << f.exponentRawBits() << " " << f.mantissaRawBits() << std::endl;
    EXPECT_TRUE(f.sign());
    EXPECT_STREQ(f.mantissaRawBits().c_str(), "10111111011000010111100");
    EXPECT_STREQ(f.exponentRawBits().c_str(), "10001001");
    f= 1.0f;
//    std::cout << f.asFloat() << " " << f.asUInt() << " " << fln::ScaleUp32 << std::endl;
//    std::cout << f.bits() << std::endl;
//    std::cout << f.sign() << " " << f.exponentRawBits() << " " << f.mantissaRawBits() << std::endl;
    EXPECT_FALSE(f.sign());
    EXPECT_STREQ(f.mantissaRawBits().c_str(), "00000000000000000000000");
    EXPECT_STREQ(f.exponentRawBits().c_str(), "01111111");
    f= 512.0f;
//    std::cout << f.asFloat() << " " << f.asUInt() << " " << fln::ScaleUp32 << std::endl;
//    std::cout << f.bits() << std::endl;
//    std::cout << f.sign() << " " << f.exponentRawBits() << " " << f.mantissaRawBits() << std::endl;
    EXPECT_FALSE(f.sign());
    EXPECT_STREQ(f.mantissaRawBits().c_str(), "00000000000000000000000");
    EXPECT_STREQ(f.exponentRawBits().c_str(), "10001000");
}

TEST(FloatType, log2){
    std::cout << "---=== TESTING LOG2 ===---" << std::endl;
    std::vector<fln::f32> numbers ={};
    for (fln::f32 i=-25.0;i<26.0;i+=0.001){
        numbers.push_back(std::pow(10.0,i));
    }
    std::vector<fln::f32> errors ={};
    for (auto& n:numbers){
        fln::object::explicitFloat f(n);
        //std::cout << n << "\t" << std::log2(f.asFloat()) << "\t" << f.log2() << "\t" << (f.log2()-std::log2(f.asFloat())) << std::endl;
        EXPECT_NEAR(std::log2(f.asFloat()), fln::object::log2(f), 0.1);
        errors.push_back(fln::object::log2(f) - std::log2(f.asFloat()));
    }
    fln::f32 mean = std::reduce(errors.begin(), errors.end()) / static_cast<fln::f32>(errors.size());
    fln::f32 sq_sum = std::inner_product(errors.begin(), errors.end(), errors.begin(), 0.0);
    fln::f32 stdev = std::sqrt(sq_sum / errors.size() - mean * mean);

    std::cout << "average absolute error of internal log 2: " << mean << " standard deviation: " << stdev << std::endl;

    // performance
    std::cout << "log2 performance review" << std::endl;
    CHRONOMETER_DURATION(,,"",1,1); // warmup
    CHRONOMETER_ITERATION(std::log2(150.0f),,                                                "std::log2         ",100000,50)
    CHRONOMETER_ITERATION(fln::object::log2(f),fln::object::explicitFloat f(150.0f) ,"fln::object::log2 ",100000,10)
    CHRONOMETER_ITERATION(fln::object::log2a(f),fln::object::explicitFloat f(150.0f),"fln::object::log2a",100000,10)
    CHRONOMETER_ITERATION(fln::bithack::log2(150.0f),                                        ,"fln::bithack::log2",100000,10)

    std::cout << "---=== END LOG2 ===---" << std::endl;
}

TEST(FloatType, exp2){
    std::cout << "---=== TESTING EXP2 ===---" << std::endl;
    std::vector<fln::f32> numbers ={};
    for (fln::f32 i=-80.0;i<80.0;i+=0.1){
        numbers.push_back(i);
    }
    std::vector<fln::f32> errors ={};
    for (auto& n:numbers){
        fln::object::explicitFloat f(n);
        //std::cout << n << "\t" << std::exp2(f.asFloat()) << "\t" << f.exp2() << "\t" << (f.exp2() - std::exp2(f.asFloat()))/std::exp2(f.asFloat()) << std::endl;
        EXPECT_NEAR(std::exp2(f.asFloat()), fln::object::exp2(f), 0.1*std::exp2(f.asFloat()));
        errors.push_back((fln::object::exp2(f) - std::exp2(f.asFloat()))/std::exp2(f.asFloat()));
    }
    fln::f32 mean = std::reduce(errors.begin(), errors.end()) / static_cast<fln::f32>(errors.size());
    fln::f32 sq_sum = std::inner_product(errors.begin(), errors.end(), errors.begin(), 0.0);
    fln::f32 stdev = std::sqrt(sq_sum / errors.size() - mean * mean);

    std::cout << "average absolute error of internal log 2: " << mean << " standard deviation: " << stdev << std::endl;

    // performance
    std::cout << "log2 performance review" << std::endl;
    CHRONOMETER_DURATION(,,"",1,1); // warmup
    CHRONOMETER_ITERATION(std::exp2(150.0f),                                                ,"std::exp2         ",100000,300)
    CHRONOMETER_ITERATION(fln::object::exp2(f),fln::object::explicitFloat f(150.0f),"fln::object::exp2 ",100000,10)
    CHRONOMETER_ITERATION(fln::bithack::exp2(150.0f),                                       ,"fln::bithack::exp2",100000,10)

    std::cout << "---=== END EXP2 ===---" << std::endl;
}

#pragma GCC diagnostic pop
