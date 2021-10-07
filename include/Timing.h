/**
 *
 *  \created 31/12/2018
 *  \author: Silmaen
 */

#pragma once
#include "baseDefines.h"
#include "baseType.h"

namespace fln {

struct TimeoutException: public std::exception {
    TimeoutException(): exception() {}
};

struct Timer {
    inline void startTimer(double durationInMilliseconds) {
        m_startTime= std::chrono::high_resolution_clock::now();
        m_timeOut= std::chrono::nanoseconds((long long)(durationInMilliseconds * 1000000));
        m_started= true;
    }
    inline void timeCheck() const {
        if(!m_started) return;
        std::chrono::nanoseconds timeSpent= std::chrono::high_resolution_clock::now() - m_startTime;
        if(timeSpent > m_timeOut) { throw TimeoutException(); }
    }
    [[nodiscard]] std::chrono::nanoseconds currentTimeTakenInNanoSeconds() const { return (std::chrono::high_resolution_clock::now() - m_startTime); }
    std::chrono::high_resolution_clock::time_point m_startTime;
    std::chrono::nanoseconds m_timeOut= std::chrono::nanoseconds{};
    bool m_started= false;
    inline friend ostream& operator<<(ostream& os, const Timer& timer) {
        os << "Time taken: " << static_cast<double>(timer.currentTimeTakenInNanoSeconds().count()) / 1000000.0 << "ms";
        return (os);
    }
};

}// namespace fln
