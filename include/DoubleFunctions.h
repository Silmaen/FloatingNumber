/**
* \date 12/10/2021
* \author Silmaen
*/
#pragma once
#include "DoubleType.h"

namespace fln::object {
/**
 * @brief set of 32 constant and magic numbers
 */
namespace const64 {
constexpr baseBits oneAsInt  = 0x3FF0000000000000;        ///< bit representation of the float 1.0
constexpr baseFloat scaleUp  = float(implicitBit);///< Scaling bit_asFloat to Int
constexpr baseFloat scaleDown= 1.0f / scaleUp;    ///< Scaling bit_asInt to Float
}// namespace const32

/**
 * @brief absolute value of the given float
 * @param f the float to measure
 * @return the absolute value of f
 */
[[nodiscard]] constexpr BitDouble abs(const BitDouble& f)noexcept {
    return BitDouble(f.bits() & const64::notSign);
}
/**
 * @brief Fast approximate logarithm base 2.
 *
 * Works for positive values of f, for negative value, the behavior is undefined.
 *
 * The absolute error is between 0.0 and -0.04 for any positive input value.
 *
 * @warning no test are done on inputs, so incorrect inputs leads tu undefined behavior
 *
 * @param f The input value.
 * @return The approximate log2.
 */
[[nodiscard]] inline BitDouble::baseFloat log2(const BitDouble& f) {
    return BitDouble::baseFloat((s64)f.bits() - (s64)const64::oneAsInt) * const64::scaleDown;
}
/**
 * @brief Fast approximate logarithm base 2 of the absolute value.
 *
 * The absolute error is between 0.0 and -0.04 for any positive input value.
 *
 * @warning no test are done on inputs, so incorrect inputs leads tu undefined behavior
 *
 * @param f The input value.
 * @return The approximate log2.
 */
[[nodiscard]] inline BitDouble::baseFloat log2a(const BitDouble& f) {
    return BitDouble::baseFloat((s64)(f.bits() & const64::notSign) - (s64)const64::oneAsInt) * const64::scaleDown;
}

/**
 * @brief Fast approximation of the power of 2.
 *
 * Works for values between -120 & 120, else the result is overflowing 32bits float and behavior is undefined.
 *
 * Relative error is between 0.0 and -0.04 for any value in non-overflowing range.
 *
 * @warning no test are done on inputs, so incorrect inputs leads tu undefined behavior
 *
 * @param f The input value.
 * @return The approximate exp2.
 */
[[nodiscard]] inline BitDouble::baseFloat exp2(const BitDouble& f) {
    BitDouble a;
    a.bits()= (s64)(f.fl() * const64::scaleUp) + (s64)const64::oneAsInt;
    return a.fl();
}
/**
 * @brief compute the power p of float f
 *
 * @warning no test are done on inputs, so incorrect inputs leads tu undefined behavior
 *
 * @param f the base
 * @param p the exponent
 * @return f^p
 */
[[nodiscard]] inline BitDouble::baseFloat pow(const BitDouble& f, const BitDouble& p) {
    BitDouble a;
    a.bits()= (s64(p.fl() * ((s64)f.bits() - (s64)const64::oneAsInt)) + const64::oneAsInt);
    return a.fl();
}


}// namespace fln::object
