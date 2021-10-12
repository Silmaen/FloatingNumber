/**
 *  \date 31/12/2018
 *  \author Silmaen
 */

#pragma once
#include "baseDefines.h"
#include "baseType.h"

/**
 * namespace fln::time
 * @brief time management
 */
namespace fln::time {
/**
 * @brief Timeout exception
 */
struct TimeoutException: public std::exception {
    /**
     * @brief base constructor
     */
    TimeoutException():
        exception() {}
};

/**
 * @brief timing structure
 */
struct Timer {
    /**
     * @brief Start the chronometer
     * @param durationInMilliseconds the duration before throwing an exception (0.0: disable)
     */
    inline void startTimer(double durationInMilliseconds=0.0) {
        m_startTime= std::chrono::high_resolution_clock::now();
        m_timeOut  = std::chrono::nanoseconds((long long)(durationInMilliseconds * 1000000));
        m_started  = true;
    }
    /**
     * @brief stop timer and save the duration
     */
    inline void stopTimer() {
        if(!m_started) return;
        m_duration= std::chrono::high_resolution_clock::now() - m_startTime;
        m_started = false;
    }
    /**
     * @brief check the time for timout
     *
     * do nothing if chronometer is not started
     * do nothing if durationInMilliseconds is set to 0.0 when starting the chronometer
     * throw an timout exception & stop chronometer if time ran out
     */
    inline void timeCheck() {
        if(!m_started) return;
        if(m_timeOut.count()==0) return;
        if(std::chrono::high_resolution_clock::now() - m_startTime > m_timeOut) {
            stopTimer();
            throw TimeoutException();
        }
    }
    /**
     * @brief get the chronometer value in nanoseconds
     * @return the duration if chronometer is stopped, else the time since the start
     */
    [[nodiscard]] std::chrono::nanoseconds currentTimeTakenInNanoSeconds() const {
        if(m_started) return (std::chrono::high_resolution_clock::now() - m_startTime);
        return m_duration;
    }
    /**
     * @brief get the chronometer value in milliseconds
     * @return the chronometer value in milliseconds
     */
    [[nodiscard]] f64 currentTimeTakenInMilliSeconds()const{return static_cast<f64>(currentTimeTakenInNanoSeconds().count()) / 1000000.0f;}

    std::chrono::high_resolution_clock::time_point m_startTime; ///< The instant when chronometer starts.
    std::chrono::nanoseconds m_timeOut = std::chrono::nanoseconds{}; ///< The timout duration.
    std::chrono::nanoseconds m_duration= std::chrono::nanoseconds{}; ///< The current duration.
    bool m_started                     = false; ///< The state of the chronometer
    /**
     * @brief friend streaming operator
     * @param os the inbound output stream
     * @param timer the Timer objecty to stream
     * @return the outbound output stream
     */
    inline friend ostream& operator<<(ostream& os, const Timer& timer) {
        os << "Time taken: " << timer.currentTimeTakenInMilliSeconds() << "ms";
        return (os);
    }
};

}// namespace fln
