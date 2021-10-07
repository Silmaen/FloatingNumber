/**
 * \author Silmaen
 * \created 07/10/2021
 */
#pragma once
#include <gtest/gtest.h>
#include "Timing.h"

namespace bln{

#define CHRONO(F,VAR_INIT,F_NAME,TIMEOUT, EXPECT_NUM){ \
    fln::Timer time;\
    static fln::u64 counter=0;\
    VAR_INIT;\
    time.startTimer(TIMEOUT);\
    try{\
        while(true){\
            F;\
            ++counter;\
            if (counter%50)time.timeCheck();\
        }\
    }catch(fln::TimeoutException&){\
        if (!std::string(F_NAME).empty()){             \
        std::cout<<"function "<<(F_NAME)<<" number: "<<counter<<" time: " <<time ; \
        std::cout<<" nano/iter "<<(time.currentTimeTakenInNanoSeconds().count()/(float)counter)<<std::endl; \
        }\
    }\
    EXPECT_GT(counter,EXPECT_NUM);                     \
}

}
