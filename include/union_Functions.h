/**
 * \file trickFunctions.h
 *
 * \date 06/10/20*21
 * \author Silmaen
 */

#pragma once
#include "baseDefines.h"
#include "baseType.h"

namespace fln {

/**
 * @brief set of function based bit hack using a union
 *
 * Typically: union{f32 x,u32 i} u;
 */
namespace _union {
// magic numbers
constexpr u32 oneAsInt32 = 0b00111111100000000000000000000000;                                ///< float(1) as int
constexpr f32 ScaleUp32  = float(0x00800000);                                                 ///< 8388608.0, 2^23
constexpr f32 ScaleDown32= 1.0f / ScaleUp32;                                                  ///< Scaling down, inverse of ScaleUp32
constexpr u64 oneAsInt64 = 0b0011111111110000000000000000000000000000000000000000000000000000;///< double(1) as int
constexpr f64 ScaleUp64  = double(1ULL << 52U);                                               ///< 2^52
constexpr f64 ScaleDown64= 1.0 / ScaleUp64;                                                   ///< Scaling down, inverse of ScaleUp32

// Bit masks for the position of the sign bit
constexpr u32 negZero32 = 0x80000000;        ///< mask of the sign bit for 32 bits
constexpr u64 negZero64 = 0x8000000000000000;///< mask of the sign bit for 64bits
constexpr u32 nnegZero32= ~negZero32;        ///< mask of the 32 bits except sign bit
constexpr u64 nnegZero64= ~negZero64;        ///< mask of the 64 bits except sign bit

// Conversions float & int
using ff32 = union{f32 x;u32 i;}; ///< 32bit union with float based initialization
using ff64 = union{f64 x;u64 i;}; ///< 64bit union with uint based initialization
using if32 = union{u32 i;f32 x;}; ///< 32bit union with float based initialization
using if64 = union{u64 i;f64 x;}; ///< 64bit union with uint based initialization

//sign
/**
 * @brief Test if the float is negative.
 * @param x The float to test.
 * @return True if negative.
 */
[[nodiscard]] constexpr bool isNegative(const f32& x) { return ff32{x}.i & negZero32; }
/**
 * @brief Test if the float is negative.
 * @param x The float to test.
 * @return True if negative.
 */
[[nodiscard]] constexpr bool isNegative(const f64& x) { return ff64{x}.i & negZero64; }

//negate
/**
 * @brief Change the sign of a float.
 * @param x The float to negate.
 * @return The float with a different sign.
 */
[[nodiscard]] constexpr f32 negate(const f32& x) { ff32 r{x}; r.i ^= negZero32; return r.x; }
/**
 * @brief Change the sign of a float.
 * @param x The float to negate.
 * @return The float with a different sign.
 */
[[nodiscard]] constexpr f64 negate(const f64& x) { ff64 r{x}; r.i ^= negZero64; return r.x; }

//abs float
/**
 * @brief get absolute value of a float
 * @param x the float negate
 * @return the absolute value of the float
 */
[[nodiscard]] constexpr f32 abs(const f32& x) { ff32 r{x}; r.i &= nnegZero32; return r.x; }
/**
 * @brief get absolute value of a float
 * @param x the float negate
 * @return the absolute value of the float
 */
[[nodiscard]] constexpr f64 abs(const f64& x) { ff64 r{x}; r.i &= nnegZero64; return r.x; }

/**
 * @brief Fast approximate logarithm base 2.
 *
 * Works for positive values of x, for negative value, the behavior is undefined.
 *
 * The absolute error is between 0.0 and -0.04 for any positive input value.
 *
 * @param x The input value.
 * @return The approximate log2.
 */
[[nodiscard]] constexpr f32 log2(const f32& x) {
    return ((f32)ff32{x}.i - (f32)oneAsInt32) * ScaleDown32;
}

/**
 * @brief Fast approximation of the power of 2.
 *
 * Works for values between -120 & 120, else the result is overflowing 32bits float and behavior is undefined.
 *
 * Relative error is between 0.0 and -0.04 for any value in non-overflowing range.
 *
 * @param x The input value.
 * @return The approximate exp2.
 */
[[nodiscard]] constexpr f32 exp2(const f32& x) {return if32{s32(x * ScaleUp32) + oneAsInt32}.x;}
/**
 * @brief Fast approximate logarithm base 2.
 *
 * Works for positive values of x, for negative value, the behavior is undefined.
 *
 * The absolute error is between 0.0 and -0.04 for any positive input value.
 *
 * @param x The input value.
 * @return The approximate log2.
 */
[[nodiscard]] constexpr f64 log2(const f64& x) {return ((f64)ff64{x}.i - (f64)oneAsInt64) * ScaleDown64;}

/**
 * @brief Fast approximation of the power of 2.
 *
 * Works for values between -120 & 120, else the result is overflowing 32bits float and behavior is undefined.
 *
 * Relative error is between 0.0 and -0.04 for any value in non-overflowing range.
 *
 * @param x The input value.
 * @return The approximate exp2.
 */
[[nodiscard]] constexpr f64 exp2(const f64& x) {return if64{s64(x * ScaleUp64) + oneAsInt64}.x;}

/**
 * @brief compute the power p of float f
 * @param x the base
 * @param p the exponent
 * @return x^p
 */
[[nodiscard]] constexpr f32 pow(const f32& x, const f32& p) {return if32{s32(p * ((s32)ff32{x}.i - (s32)oneAsInt32)) + oneAsInt32}.x;}

/**
 * @brief compute the power p of float f
 * @param x the base
 * @param p the exponent
 * @return x^p
 */
[[nodiscard]] constexpr f64 pow(const f64& x, const f64& p) {return if64{static_cast<u64>(s64(p * ((s64)ff64{x}.i - (s64)oneAsInt64) + oneAsInt64))}.x;}

/**
 * @brief square root using pow(x,0.5)
 * @param x the float to square root
 * @return the square root
 */
[[nodiscard]] constexpr f32 sqrt_pow(const f32& x) {return if32{s32(0.5f * ((s32)ff32{x}.i - (s32)oneAsInt32)) + oneAsInt32}.x;}

/**
 * @brief square root using pow(x,0.5)
 * @param x the float to square root
 * @return the square root
 */
[[nodiscard]] constexpr f64 sqrt_pow(const f64& x) {return if64{static_cast<u64>(s64(0.5 * ((s64)ff64{x}.i - (s64)oneAsInt64) + oneAsInt64))}.x;}
/**
 * @brief square root
 * @param x the float to square root
 * @return the square root
 */
[[nodiscard]] constexpr f32 sqrt(const f32& x) {
    return if32{(ff32{x}.i + oneAsInt32) >> 1U}.x;
}
/**
 * @brief square root
 * @param x the float to square root
 * @return the square root
 */
[[nodiscard]] constexpr f64 sqrt(const f64& x) {
    return if64{(ff64{x}.i + oneAsInt64) >> 1U}.x;
}

/**
 * @brief square root using codingame formula
 * @param f the float to square root
 * @return the square root
 */
[[nodiscard]] constexpr f32 sqrt_b(const f32& x) {
    constexpr u32 sqrt_magic= (1U << 29U) - (1U << 22U);
    ff32 u{x};
    u.i= sqrt_magic + (u.i >> 1U);
    return u.x;
}

[[nodiscard]] constexpr f32 rsqrt_quake(const f32& x) {
    f32 x2{x * 0.5F};
    ff32 y{x};
    y.i = 0x5f3759df - (y.i >> 1);// what the fuck?
    y.x *= (1.5F - (x2 * y.x * y.x));// 1st iteration
    // y.x *= ( threehalfs - ( x2 * y.x * y.x ) ); // 2nd iteration, this can be removed
    return y.x;
}

}// namespace bithack


// LOGARITM
[[nodiscard]] constexpr f32 fasterlog(const f32& x) {
    union {
        f32 f;
        u32 i;
    } vx  = {x};
    auto y= (f32)vx.i;
    y*= 8.2629582881927490e-8f;
    return (y - 87.989971088f);
}

}// namespace fln
