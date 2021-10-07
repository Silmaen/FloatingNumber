/**
 * \author Silmaen
 * \created 07/10/2021
 */
#pragma once
#include "Timing.h"
#include <gtest/gtest.h>

#define CHRONOMETER_DURATION(F, VAR_INIT, F_NAME, TIMEOUT, EXPECTED_NUM)                                                       \
    {                                                                                                                          \
        fln::Timer time;                                                                                                       \
        static fln::u64 counter= 0;                                                                                            \
        VAR_INIT;                                                                                                              \
        time.startTimer(TIMEOUT);                                                                                              \
        try {                                                                                                                  \
            while(true) {                                                                                                      \
                F;                                                                                                             \
                ++counter;                                                                                                     \
                if(counter % 50) time.timeCheck();                                                                             \
            }                                                                                                                  \
        } catch(fln::TimeoutException&) {                                                                                      \
            if(!std::string(F_NAME).empty()) {                                                                                 \
                std::cout << "function " << (F_NAME) << " number: " << counter;                                                \
                std::cout << " ||| ns/iter: " << (time.currentTimeTakenInNanoSeconds().count() / (float)counter) << std::endl; \
            }                                                                                                                  \
        }                                                                                                                      \
        EXPECT_GT(counter, EXPECTED_NUM);                                                                                      \
    }

#define CHRONOMETER_ITERATION(F, VAR_INIT, F_NAME, ITERATION_NUMBER, EXPECT_MEAN_NANO)                                     \
    {                                                                                                                      \
        fln::Timer time;                                                                                                   \
        static fln::u64 counter= 0;                                                                                        \
        VAR_INIT;                                                                                                          \
        time.startTimer();                                                                                                 \
        for(; counter < (ITERATION_NUMBER); ++counter) {                                                                   \
            F;                                                                                                             \
        }                                                                                                                  \
        time.stopTimer();                                                                                                  \
        if(!std::string(F_NAME).empty()) {                                                                                 \
            std::cout << "function " << (F_NAME) << " time: " << time.currentTimeTakenInMilliSeconds() << "ms";            \
            std::cout << " ||| ns/iter: " << (time.currentTimeTakenInNanoSeconds().count() / (float)counter) << std::endl; \
        }                                                                                                                  \
        EXPECT_LT(time.currentTimeTakenInNanoSeconds().count() / (float)counter, EXPECT_MEAN_NANO);                        \
    }
