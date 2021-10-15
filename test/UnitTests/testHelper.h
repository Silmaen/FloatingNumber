/**
 * \author Silmaen
 * \date 07/10/2021
 */
#pragma once
#include "Timing.h"
#include <gtest/gtest.h>

// standard loop number
#if defined(FLN_DEBUG)
constexpr fln::u64 loopNumber= 1000000;
#elif defined(FLN_SMALL)
constexpr fln::u64 loopNumber= 10000000;
#else
constexpr fln::u64 loopNumber= 10000000;
#endif

static fln::f64 timeCorrection;

#define CHRONOMETER_RESET_CORRECTION() \
    {                                  \
        timeCorrection= 0;             \
    }

#define CHRONOMETER_ESTIMATE_CORRECTION(F)                                                            \
    {                                                                                                 \
        fln::time::Timer time;                                                                        \
        fln::u64 counter= 0;                                                                          \
        time.startTimer();                                                                            \
        for(; counter < loopNumber; ++counter) {                                                      \
            F;                                                                                        \
        }                                                                                             \
        time.stopTimer();                                                                             \
        timeCorrection= ((fln::f64)time.currentTimeTakenInNanoSeconds().count() / (fln::f64)counter); \
    }

#ifdef FLN_VERBOSE_TEST
#define CHRONOMETER_DURATION(F, F_NAME, TIMEOUT, EXPECTED_NUM)                                                                 \
    {                                                                                                                          \
        fln::time::Timer time;                                                                                                 \
        static fln::u64 counter= 0;                                                                                            \
        time.startTimer(TIMEOUT);                                                                                              \
        try {                                                                                                                  \
            while(true) {                                                                                                      \
                F;                                                                                                             \
                ++counter;                                                                                                     \
                if(counter % 50) time.timeCheck();                                                                             \
            }                                                                                                                  \
        } catch(fln::time::TimeoutException&) {                                                                                \
            if(!std::string(F_NAME).empty()) {                                                                                 \
                std::cout << "function " << (F_NAME) << " number: " << counter;                                                \
                std::cout << " ||| ns/iter: " << (time.currentTimeTakenInNanoSeconds().count() / (float)counter) << std::endl; \
            }                                                                                                                  \
        }                                                                                                                      \
        EXPECT_GT(counter, EXPECTED_NUM);                                                                                      \
    }

#define CHRONOMETER_ITERATION(F, F_NAME, EXPECT_MEAN_NANO)                                                                 \
    {                                                                                                                      \
        fln::time::Timer time;                                                                                             \
        fln::u64 counter= 0;                                                                                               \
        time.startTimer();                                                                                                 \
        for(; counter < loopNumber; ++counter) {                                                                           \
            F;                                                                                                             \
        }                                                                                                                  \
        time.stopTimer();                                                                                                  \
        fln::f64 timing= ((fln::f64)time.currentTimeTakenInNanoSeconds().count() / (fln::f64)counter) - timeCorrection;    \
        fln::f64 timer = (fln::f64)time.currentTimeTakenInMilliSeconds() - (fln::f64)counter * timeCorrection * 0.0000001; \
        if(!std::string(F_NAME).empty()) {                                                                                 \
            std::cout << "function " << (F_NAME) << " time: " << timer << "ms ||| ns/iter: " << timing << std::endl;       \
        }                                                                                                                  \
        EXPECT_LT(timing, EXPECT_MEAN_NANO);                                                                               \
    }
#else
#define CHRONOMETER_DURATION(F, F_NAME, TIMEOUT, EXPECTED_NUM) \
    {                                                          \
        fln::time::Timer time;                                 \
        static fln::u64 counter= 0;                            \
        time.startTimer(TIMEOUT);                              \
        try {                                                  \
            while(true) {                                      \
                F;                                             \
                ++counter;                                     \
                if(counter % 50) time.timeCheck();             \
            }                                                  \
        } catch(fln::time::TimeoutException&) {}               \
        EXPECT_GT(counter, EXPECTED_NUM);                      \
    }

#define CHRONOMETER_ITERATION(F, F_NAME, EXPECT_MEAN_NANO)                                                              \
    {                                                                                                                   \
        fln::time::Timer time;                                                                                          \
        static fln::u64 counter= 0;                                                                                     \
        time.startTimer();                                                                                              \
        for(; counter < loopNumber; ++counter) {                                                                        \
            F;                                                                                                          \
        }                                                                                                               \
        time.stopTimer();                                                                                               \
        fln::f64 timing= ((fln::f64)time.currentTimeTakenInNanoSeconds().count() / (fln::f64)counter) - timeCorrection; \
        EXPECT_LT(timing, EXPECT_MEAN_NANO);                                                                            \
    }
#endif