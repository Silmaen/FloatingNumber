/**
* \author Silmaen
* \date 07/10/2021
*/
#pragma once
#include "baseDefines.h"
#include "baseType.h"

namespace fln {

/**
 * @brief set of ternary-based math operations
 */
namespace ternary {
// SIGN
[[nodiscard]] constexpr s32 sign(const s32& x) { return (x < 0 ? -1 : ((x > 0) ? 1 : 0)); }
[[nodiscard]] constexpr f32 sign(const f32& x) { return (x < 0 ? -1.0f : ((x > 0) ? 1.0f : 0.0f)); }
[[nodiscard]] constexpr f64 sign(const f64& x) { return (x < 0 ? -1.0f : ((x > 0) ? 1.0f : 0.0f)); }

// ABS
[[nodiscard]] constexpr s64 abs(const s64& x) { return (x < 0 ? -x : x); }
[[nodiscard]] constexpr f32 abs(const f32& x) { return (x < 0 ? -x : x); }
[[nodiscard]] constexpr f64 abs(const f64& x) { return (x < 0 ? -x : x); }

// CLAMP
[[nodiscard]] constexpr s32 clamp(const s32& x, const s32& a, const s32& b) { return ((x < a) ? a : ((x > b) ? b : x)); }
[[nodiscard]] constexpr f32 clamp(const f32& x, const f32& a, const f32& b) { return ((x < a) ? a : ((x > b) ? b : x)); }
[[nodiscard]] constexpr f64 clamp(const f64& x, const f64& a, const f64& b) { return ((x < a) ? a : ((x > b) ? b : x)); }

//MIN
[[nodiscard]] constexpr u8 min(const u8& a, const u8& b) { return ((a > b) ? b : a); }
[[nodiscard]] constexpr u16 min(const u16& a, const u16& b) { return ((a > b) ? b : a); }
[[nodiscard]] constexpr u32 min(const u32& a, const u32& b) { return ((a > b) ? b : a); }
[[nodiscard]] constexpr u64 min(const u64& a, const u64& b) { return ((a > b) ? b : a); }
[[nodiscard]] constexpr s32 min(const s32& a, const s32& b) { return ((a > b) ? b : a); }
[[nodiscard]] constexpr s64 min(const s64& a, const s64& b) { return ((a > b) ? b : a); }
[[nodiscard]] constexpr f32 min(const f32& a, const f32& b) { return ((a > b) ? b : a); }
[[nodiscard]] constexpr f64 min(const f64& a, const f64& b) { return ((a > b) ? b : a); }
//MAX
[[nodiscard]] constexpr u8 max(const u8& a, const u8& b) { return ((a > b) ? a : b); }
[[nodiscard]] constexpr u16 max(const u16& a, const u16& b) { return ((a > b) ? a : b); }
[[nodiscard]] constexpr u32 max(const u32& a, const u32& b) { return ((a > b) ? a : b); }
[[nodiscard]] constexpr u64 max(const u64& a, const u64& b) { return ((a > b) ? a : b); }
[[nodiscard]] constexpr s32 max(const s32& a, const s32& b) { return ((a > b) ? a : b); }
[[nodiscard]] constexpr s64 max(const s64& a, const s64& b) { return ((a > b) ? a : b); }
[[nodiscard]] constexpr f32 max(const f32& a, const f32& b) { return ((a > b) ? a : b); }
[[nodiscard]] constexpr f64 max(const f64& a, const f64& b) { return ((a > b) ? a : b); }
}// namespace ternary

/**
 * @brief set of bits operations
 */
namespace bits {
// Bits operations
constexpr void bitSet(u8& number, const u8& bit) { number|= 1ul << bit; }
constexpr void bitDefine(u8& number, const u8& bit, const bool& value) { number= (number & ~(1UL << bit)) | (value << bit); }
constexpr void bitClear(u8& number, const u8& bit) { number&= ~(1ul << bit); }
constexpr void bitToggle(u8& number, const u8& bit) { number^= 1ul << bit; }
[[nodiscard]] constexpr bool bitGet(const u8& number, const u8& bit) { return ((number >> bit) & 1u); }
constexpr void bitSet(u64& number, const u8& bit) { number|= 1ull << bit; }
constexpr void bitDefine(u64& number, const u8& bit, const bool& value) { number= (number & ~(1ull << bit)) | ((u64)value << bit); }
constexpr void bitClear(u64& number, const u8& bit) { number&= ~(1ull << bit); }
constexpr void bitToggle(u64& number, const u8& bit) { number^= 1ull << bit; }
[[nodiscard]] constexpr bool bitGet(const u64& number, const u8& bit) { return ((number >> bit) & 1ull); }
}// namespace bits

/**
 * @brief set of builtin-based functions
 */
namespace builtin {
// log2
/**
 * @brief compute the log2 of a 32bit unsigned integer
 * @param x the input integer
 * @return the log2
 */
[[nodiscard]] constexpr u32 log2i(const u32& x) {
#ifdef _MSC_VER
    unsigned long result= 0;
    _BitScanReverse(&result, static_cast<u32>(x));
    return (result);
#else
    return (32 - __builtin_clz(x));
#endif
}
}// namespace builtin

}// namespace fln