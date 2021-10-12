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
 * @brief set of function based on classical bit hack
 *
 * the main Idea is to get access to the bits of float by using
 * the fln::bithack::asInt and fln::bithack::asFloat to toggle between float and ints
 */
namespace bithack {
// magic numbers
constexpr u32 oneAsInt32 = 0b00111111100000000000000000000000;///< float(1) as int
constexpr f32 ScaleUp32  = float(0x00800000);                 ///< 8388608.0, 2^23
constexpr f32 ScaleDown32= 1.0f / ScaleUp32;                  ///< Scaling down, inverse of ScaleUp32
constexpr u64 oneAsInt64 = 0b0011111111110000000000000000000000000000000000000000000000000000;///< double(1) as int
constexpr f64 ScaleUp64  = double(1ULL<<52U);                 ///< 2^52
constexpr f64 ScaleDown64= 1.0 / ScaleUp64;                   ///< Scaling down, inverse of ScaleUp32

// Bit masks for the position of the sign bit
constexpr u32 negZero32= 0x80000000;         ///< mask of the sign bit for 32 bits
constexpr u64 negZero64= 0x8000000000000000;///< mask of the sign bit for 64bits
constexpr u32 nnegZero32= ~negZero32;///< mask of the 32 bits except sign bit
constexpr u64 nnegZero64= ~negZero64;///< mask of the 64 bits except sign bit

// Conversions float & int
/**
 * @brief Get the 32bit float bit representation as 32bit unsigned
 * @param f The float to convert
 * @return The 32bits
 */
[[nodiscard]] constexpr u32 asInt(const f32& f) { return *(u32*)&f; }
/**
 * @brief Get the 64bit float bit representation as 64bit unsigned
 * @param f The float to convert
 * @return The 64bits
 */
[[nodiscard]] constexpr u64 asInt(const f64& f) { return *(u64*)&f; }
/**
 * @brief Get the 32bit float based on a 32bit representation.
 * @param i The 32bits integer.
 * @return The corresponding 32bit float.
 */
[[nodiscard]] constexpr f32 asFloat(const u32& i) { return *(f32*)&i; }
/**
 * @brief Get the 64bit float based on a 64bit representation.
 * @param i The 64bits integer.
 * @return The corresponding 64bit float.
 */
[[nodiscard]] constexpr f64 asFloat(const u64& i) { return *(f64*)&i; }


//sign
/**
 * @brief Test if the float is negative.
 * @param f The float to test.
 * @return True if negative.
 */
[[nodiscard]] constexpr bool isNegative(const f32& f) { return asInt(f) & negZero32; }
/**
 * @brief Test if the float is negative.
 * @param f The float to test.
 * @return True if negative.
 */
[[nodiscard]] constexpr bool isNegative(const f64& f) { return asInt(f) & negZero64; }

//negate
/**
 * @brief Change the sign of a float.
 * @param f The float to negate.
 * @return The float with a different sign.
 */
[[nodiscard]] constexpr f32 negate(const f32& f) { return asFloat(asInt(f) ^ negZero32); }
/**
 * @brief Change the sign of a float.
 * @param f The float to negate.
 * @return The float with a different sign.
 */
[[nodiscard]] constexpr f64 negate(const f64& f) { return asFloat(asInt(f) ^ negZero64); }

//abs float
/**
 * @brief get absolute value of a float
 * @param f the float negate
 * @return the absolute value of the float
 */
[[nodiscard]] constexpr f32 abs(const f32& f) { return asFloat(asInt(f) & nnegZero32); }
/**
 * @brief get absolute value of a float
 * @param f the float negate
 * @return the absolute value of the float
 */
[[nodiscard]] constexpr f64 abs(const f64& f) { return asFloat(asInt(f) & nnegZero64); }

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
[[nodiscard]] constexpr f32 log2(const f32& f) { return f32((s32)asInt(f) - (s32)oneAsInt32) * ScaleDown32; }

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
[[nodiscard]] constexpr f32 exp2(const f32& f) { return asFloat(s32(f * ScaleUp32) + oneAsInt32); }
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
[[nodiscard]] constexpr f64 log2(const f64& f) { return f64((s64)asInt(f) - (s64)oneAsInt64) * ScaleDown64; }

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
[[nodiscard]] constexpr f64 exp2(const f64& f) { return asFloat(s64(f * ScaleUp64) + oneAsInt64); }

/**
 * @brief compute the power p of float f
 * @param f the base
 * @param p the exponent
 * @return f^p
 */
[[nodiscard]] constexpr f32 pow(const f32& f, const f32& p) { return asFloat(s32(p * ((s32)asInt(f) - (s32)oneAsInt32)) + oneAsInt32); }

/**
 * @brief compute the power p of float f
 * @param f the base
 * @param p the exponent
 * @return f^p
 */
[[nodiscard]] constexpr f64 pow(const f64& f, const f64& p) { return asFloat(s64(p * ((s64)asInt(f) - (s64)oneAsInt64)) + oneAsInt64); }
}

// ---=== SQRT 32 ===---
constexpr u32 sqrt_oneL29= 1 << 29;
constexpr u32 sqrt_oneL22= 1 << 22;
constexpr u32 sqrt_magic = sqrt_oneL29 - sqrt_oneL22;
[[nodiscard]] constexpr f32 fastSqrt(const f32& x) {
    union {
        s32 i;
        f32 x;
    } u{};
    u.x= x;
    u.i= (1 << 29) + (u.i >> 1) - (1 << 22);
    return (u.x);
}
[[nodiscard]] constexpr f32 fastSqrt_(const f32& x) {
    union {s32 i;f32 x;} u{};u.x= x;
    u.i= sqrt_magic + (u.i >> 1);
    return (u.x);
}
[[nodiscard]] constexpr f32 fastSqrt2(const f32& x) { return bithack::asFloat((1 << 29) + (bithack::asInt(x) >> 1) - (1 << 22)); }
[[nodiscard]] constexpr f32 fastSqrt3(const f32& x) { return bithack::asFloat(sqrt_magic + (bithack::asInt(x) >> 1)); }
[[nodiscard]] constexpr f32 fasterSqrt(const f32& f) { return bithack::asFloat((bithack::asInt(f) + bithack::oneAsInt32) >> 1); }
[[nodiscard]] constexpr f32 sqrtNewRaph(const f32& f) {
    float y= fasterSqrt(f);
    return (y * y + f) / (2 * y);
}
// ---=== SQRT 32 ===---

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
