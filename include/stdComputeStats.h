/**
* \date 15/10/2021
* \author Silmaen
*/
#pragma once

#include "baseType.h"

/**
 * @namespace fln::stats
 * @brief function for computing statistic on datsets
 */
namespace fln::stats {

/**
 * @brief Structure holding statistical results
 * @tparam T The baase type of results
 */
template<class T>
struct stats {
    T mean;        ///< the mean of the set of data
    T sum;         ///< the sum of the set of data
    T squareSum;   ///< the sum of squared data elements
    T stdDeviation;///< the standard deviation
    T min;
    T max;
};

/**
 * @brief Compute the stats for the given set of data
 * @tparam data the base type of dta
 * @tparam result the base type of result
 * @param data the set of data
 * @return structure holding the results
 */
template<class data>
stats<data> getStats(const std::vector<data>& dataset, bool print=false) {
    stats<data> res;
    res.sum      = data{};
    res.squareSum= data{};
    for(auto i: dataset) {
        res.sum+= i;
        res.squareSum+= i * i;
    }
    res.mean        = static_cast<data>(res.sum) / static_cast<data>(dataset.size());
    res.stdDeviation= std::sqrt(res.squareSum / static_cast<data>(dataset.size()) - res.mean * res.mean);
    res.min         = static_cast<data>(*std::min_element(dataset.begin(), dataset.end()));
    res.max         = static_cast<data>(*std::max_element(dataset.begin(), dataset.end()));
    if (print) {
        std::cout << "sum         : " << res.sum << std::endl;
        std::cout << "squareSum   : " << res.squareSum << std::endl;
        std::cout << "mean        : " << res.mean << std::endl;
        std::cout << "stdDeviation: " << res.stdDeviation << std::endl;
        std::cout << "min         : " << res.min << std::endl;
        std::cout << "max         : " << res.max << std::endl;
    }
    return res;
}

}// namespace fln::stats
