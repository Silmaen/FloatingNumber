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
    TimeoutException():
        exception() {}
};

struct Timer {
    inline void startTimer(double durationInMilliseconds=0.0) {
        m_startTime= std::chrono::high_resolution_clock::now();
        m_timeOut  = std::chrono::nanoseconds((long long)(durationInMilliseconds * 1000000));
        m_started  = true;
    }
    inline void stopTimer() {
        m_duration= std::chrono::high_resolution_clock::now() - m_startTime;
        m_started = false;
    }
    inline void timeCheck() {
        if(!m_started) return;
        std::chrono::nanoseconds timeSpent= std::chrono::high_resolution_clock::now() - m_startTime;
        if(timeSpent > m_timeOut) {
            stopTimer();
            throw TimeoutException();
        }
    }
    [[nodiscard]] std::chrono::nanoseconds currentTimeTakenInNanoSeconds() const {
        if(m_started) return (std::chrono::high_resolution_clock::now() - m_startTime);
        return m_duration;
    }
    [[nodiscard]] f64 currentTimeTakenInMilliSeconds()const{return static_cast<f64>(currentTimeTakenInNanoSeconds().count()) / 1000000.0f;}

    std::chrono::high_resolution_clock::time_point m_startTime;
    std::chrono::nanoseconds m_timeOut = std::chrono::nanoseconds{};
    std::chrono::nanoseconds m_duration= std::chrono::nanoseconds{};
    bool m_started                     = false;
    inline friend ostream& operator<<(ostream& os, const Timer& timer) {
        os << "Time taken: " << timer.currentTimeTakenInMilliSeconds() << "ms";
        return (os);
    }
};

}// namespace fln
