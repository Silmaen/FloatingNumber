/**
* \date 14/10/2021
* \author Silmaen
*/
#pragma once
#include "baseType.h"

/**
 * @namespace fln::rand
 * @brief the functions for random number generation
 */
namespace fln::rand {

/**
 * @brief simple and fast random number generator based of xorshift64 algorithm
 */
struct RandomGenerator {
    RandomGenerator(u64 _seed= 0) {
        if(_seed == 0) {
            seed= (u64)time(0);
        } else {
            seed= _seed;
        }
    }
    inline u64 getRandomU64(const u64& bound) { return (rand() % bound); }
    inline u32 getRandomU32(const u32& bound) { return (rand() % bound); }
    inline u16 getRandomU16(const u16& bound) { return (rand() % bound); }
    inline u64 getRandomU64(const u64& a, const u64& b) { return (a + getRandomU64(b - a + 1ULL)); }
    inline u32 getRandomU32(const u32& a, const u32& b) { return (a + getRandomU32(b - a + 1UL)); }
    inline u16 getRandomU16(const u16& a, const u16& b) { return (a + getRandomU16(b - a + 1U)); }
    inline f32 getRandomF32(const f32& a, const f32& b) { return (a + (static_cast<f32>(rand()) / 0x7FFF) * (b - a)); }
    inline f32 getRandomF64(const f64& a, const f64& b) { return (a + (static_cast<f64>(rand()) / 0x7FFFFFFF) * (b - a)); }
    /**
     * @brief base rand function
     * @return new number
     */
    u64 rand() {
        //    seed= (214013 * seed + 2531011);
        //    return ((seed >> 32U) & 0x7FFFFFFFU);
        u64 a{seed};
        a^= a << 13U;
        a^= a >> 7U;
        a^= a << 17U;
        return seed= a;
    }
    u64 seed;///< the actual seed of the generator
};

}// namespace fln::rand