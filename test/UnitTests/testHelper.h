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

#ifdef FLN_VERBOSE_TEST
#define CHRONOMETER_DURATION(F, VAR_INIT, F_NAME, TIMEOUT, EXPECTED_NUM)                                                       \
    {                                                                                                                          \
        fln::time::Timer time;                                                                                                 \
        static fln::u64 counter= 0;                                                                                            \
        VAR_INIT;                                                                                                              \
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

#define CHRONOMETER_ITERATION(F, VAR_INIT, F_NAME, EXPECT_MEAN_NANO)                                     \
    {                                                                                                                      \
        fln::time::Timer time;                                                                                             \
        static fln::u64 counter= 0;                                                                                        \
        VAR_INIT;                                                                                                          \
        time.startTimer();                                                                                                 \
        for(; counter < loopNumber; ++counter) {                                                                   \
            F;                                                                                                             \
        }                                                                                                                  \
        time.stopTimer();                                                                                                  \
        if(!std::string(F_NAME).empty()) {                                                                                 \
            std::cout << "function " << (F_NAME) << " time: " << time.currentTimeTakenInMilliSeconds() << "ms";            \
            std::cout << " ||| ns/iter: " << ((fln::f64)time.currentTimeTakenInNanoSeconds().count() / (fln::f64)counter) << std::endl; \
        }                                                                                                                  \
        EXPECT_LT((fln::f64)time.currentTimeTakenInNanoSeconds().count() / (fln::f64)loopNumber, EXPECT_MEAN_NANO);                        \
    }
#else
#define CHRONOMETER_DURATION(F, VAR_INIT, F_NAME, TIMEOUT, EXPECTED_NUM) \
    {                                                                    \
        fln::time::Timer time;                                           \
        static fln::u64 counter= 0;                                      \
        VAR_INIT;                                                        \
        time.startTimer(TIMEOUT);                                        \
        try {                                                            \
            while(true) {                                                \
                F;                                                       \
                ++counter;                                               \
                if(counter % 50) time.timeCheck();                       \
            }                                                            \
        } catch(fln::time::TimeoutException&) {}                         \
        EXPECT_GT(counter, EXPECTED_NUM);                                \
    }

#define CHRONOMETER_ITERATION(F, VAR_INIT, F_NAME, ITERATION_NUMBER, EXPECT_MEAN_NANO)              \
    {                                                                                               \
        fln::time::Timer time;                                                                      \
        static fln::u64 counter= 0;                                                                 \
        VAR_INIT;                                                                                   \
        time.startTimer();                                                                          \
        for(; counter < loopNumber; ++counter) {                                            \
            F;                                                                                      \
        }                                                                                           \
        time.stopTimer();                                                                           \
        EXPECT_LT((fln::f64)time.currentTimeTakenInNanoSeconds().count() / (fln::f64)loopNumber, EXPECT_MEAN_NANO); \
    }
#endif