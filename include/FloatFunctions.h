/**
* \date 12/10/2021
* \author Silmaen
*/
#pragma once
#include "FloatType.h"

namespace fln::object {
/**
 * @brief set of 32 constant and magic numbers
 */
namespace const32 {
constexpr baseBits oneAsInt  = 0x3f800000;        ///< bit representation of the float 1.0
constexpr baseFloat scaleUp  = float(implicitBit);///< Scaling bit_asFloat to Int
constexpr baseFloat scaleDown= 1.0f / scaleUp;    ///< Scaling bit_asInt to Float
}// namespace const32

/**
 * @brief Fast approximate logarithm base 2.
 *
 * Works for positive values of f, for negative value, the behavior is undefined.
 *
 * The absolute error is between 0.0 and -0.04 for any positive input value.
 *
 * @param f The input value.
 * @return The approximate log2.
 */
[[nodiscard]] inline BitFloat::baseFloat log2(const BitFloat& f) {
    return BitFloat::baseFloat((s32)f.bits() - (s32)const32::oneAsInt) * const32::scaleDown;
}
/**
 * @brief Fast approximate logarithm base 2 of the absolute value.
 *
 * The absolute error is between 0.0 and -0.04 for any positive input value.
 *
 * @param f The input value.
 * @return The approximate log2.
 */
[[nodiscard]] inline BitFloat::baseFloat log2a(const BitFloat& f) {
    return BitFloat::baseFloat((s32)(f.bits() & const32::notSign) - (s32)const32::oneAsInt) * const32::scaleDown;
}

/**
 * @brief Fast approximation of the power of 2.
 *
 * Works for values between -120 & 120, else the result is overflowing 32bits float and behavior is undefined.
 *
 * Relative error is between 0.0 and -0.04 for any value in non-overflowing range.
 *
 * @param f The input value.
 * @return The approximate exp2.
 */
[[nodiscard]] inline BitFloat::baseFloat exp2(const BitFloat& f) {
    BitFloat a;
    a.bits()= (s32)(f.fl() * const32::scaleUp) + (s32)const32::oneAsInt;
    return a.getFloat();
}
/**
 * @brief compute the power p of float f
 * @param f the base
 * @param p the exponent
 * @return f^p
 */
[[nodiscard]] inline BitFloat::baseFloat pow(const BitFloat& f, const BitFloat& p) {
    BitFloat a;
    a.bits()= (s32(p.fl() * ((s32)f.bits() - (s32)const32::oneAsInt)) + const32::oneAsInt);
    return a.fl();
}

}// namespace fln::object
