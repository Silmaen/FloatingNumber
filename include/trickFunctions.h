/**
 * \file trickFunctions.h
 *
 * \date 06/10/20*21
 * \author Silmaen
 */

#pragma once
#include "baseDefines.h"
#include "baseType.h"

namespace fln{

// magic numbers
constexpr u32 oneAsInt32 = 0x3F800000; // float(1) as int
constexpr u32 oneL29 = 1<<29;
constexpr u32 oneL22 = 1<<22;

constexpr u32 magic = oneL29-oneL22;
constexpr f32 ScaleUp32 = float(0x00800000); // 8388608.0, 2^23
constexpr f32 ScaleDown32 = 1.0f/ScaleUp32;

// Bit masks for the position of the sign bit
constexpr u8 negZero8=0x8;
constexpr u16 negZero16=0x8000;
constexpr u32 negZero32=0x80000000;
constexpr u64 negZero64=0x8000000000000000;

// Conversions float & int
[[nodiscard]] constexpr u32 asInt(const f32& f){return *(u32*)&f;}
[[nodiscard]] constexpr f32 asFloat(const u32& i){return *(f32*)&i;}
[[nodiscard]] constexpr u64 asInt(const f64& f){return *(u64*)&f;}
[[nodiscard]] constexpr f64 asFloat(const u64& i){return *(f64*)&i;}

//negate
[[nodiscard]] constexpr s8 negate(const s8& i){return i^negZero8;}
[[nodiscard]] constexpr s16 negate(const s16& i){return i^negZero16;}
[[nodiscard]] constexpr s32 negate(const s32& i){return i^negZero32;}
[[nodiscard]] constexpr f32 negate(const f32& f){return asFloat(asInt(f)^negZero32);}
[[nodiscard]] constexpr f64 negate(const f64& f){return asFloat(asInt(f)^negZero64);}

//abs float
[[nodiscard]] constexpr f32 fastAbs(const f32& f){return asFloat(asInt(f)&~negZero32);}
[[nodiscard]] constexpr f32 fastAbsV(f32 f){return asFloat(asInt(f)&~negZero32);}
[[nodiscard]] constexpr f64 fastAbs(const f64& f){return asFloat(asInt(f)&~negZero64);}

//sign
[[nodiscard]] constexpr bool isNegative(const s8& i){return i&negZero8;}
[[nodiscard]] constexpr bool isNegative(const s16& i){return i&negZero16;}
[[nodiscard]] constexpr bool isNegative(const s32& i){return i&negZero32;}
[[nodiscard]] constexpr bool isNegative(const f32& f){return asInt(f)&negZero32;}
[[nodiscard]] constexpr bool isNegative(const f64& f){return asInt(f)&negZero64;}
// log2
[[nodiscard]] constexpr f32 log2(const float& f){return f32(asInt(f)-oneAsInt32)*ScaleDown32;}
[[nodiscard]] constexpr f32 exp2(const float& f){return asFloat(int(f*ScaleUp32)+oneAsInt32);}
[[nodiscard]] constexpr f32 pow(const float& f,const float& p){return asFloat(int(p*(asInt(f)-oneAsInt32))+oneAsInt32);}

[[nodiscard]] constexpr f32 fastSqrt(const float& f){return asFloat((asInt(f)+oneAsInt32)>>1);}
[[nodiscard]] constexpr f32 fasterSqrt(const f32& x){return asFloat((1<<29)+(asInt(x)>>1)-(1<<22));}
[[nodiscard]] constexpr f32 fasterSqrt2(const f32& x){return asFloat(magic+(asInt(x)>>1));}
[[nodiscard]] constexpr f32 sqrtNewRaph(const float& f){float y=fastSqrt(f);return (y*y+f)/(2*y);}

}
