/**
 * \author Silmaen
 * \date 07/10/2021
 */
#pragma once
#include "baseDefines.h"

/**
 * @brief base namespace for the project
 */
namespace fln {

// SIGNED INTEGERS
/// 64-bit signed integer
using s64= int64_t;// -170 141 183 460 469 231 731 687 303 715 884 105 728 to 170 141 183 460 469 231 731 687 303 715 884 105 727
/// 32-bit signed integer
using s32= int32_t;// -2 147 483 648 to 2 147 483 647
/// 16-bit signed integer
using s16= int16_t;// -32 768 to 32 767
/// 8-bit signed integer
using s8= int8_t;// -128 to 127

// UNSIGNED INTEGERS
/// 64-bit unsigned integer
using u64= uint64_t;// 0 to 340 282 366 920 938 463 463 374 607 431 768 211 455
/// 32-bit unsigned integer
using u32= uint32_t;// 0 to 4 294 967 295
/// 16-bit unsigned integer
using u16= uint16_t;// 0 to 65 535
/// 8-bit unsigned integer
using u8= uint8_t;// 0 to 255
//   1   2   3   4   5   6   7   8   9   10   11   12   13
//   1   3   7  15  31  63 127 255 511 1023 2048 4096 8128

// FLOATS
/// 32-bit Floating point number
using f32= float;
/// 64-bit Floating point number
using f64= double;

}// namespace fln
