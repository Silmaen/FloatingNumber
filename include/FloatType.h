/**
* \file FloatType.h
*
* \date 11/10/2021
* \author Silmaen
*/

#pragma once
#include "baseType.h"

namespace fln {

namespace f32const {
constexpr u32 signMask= 0b10000000000000000000000000000000;
constexpr u32 expoMask= 0b01111111100000000000000000000000;
constexpr u32 mantMask= 0b00000000011111111111111111111111;
constexpr u8 expoBias = 127;
constexpr u32 oneAsInt= 0x3f800000;
constexpr u32 NotSign = 0b01111111111111111111111111111111;
constexpr f32 scaleUp= float(0x00800000);
constexpr f32 scaleDown= 1.0f/scaleUp;
}// namespace f32const
/**
 * @brief class to better handle float and their bits
 *
 * this class is not designed for performance
 */
class explicitFloat {
public:
    explicitFloat()                          = default;
    explicitFloat(const explicitFloat& a)    = default;
    explicitFloat(explicitFloat&& a) noexcept= default;
    explicit explicitFloat(const f32& a):
        data{a} {}
    explicit explicitFloat(f32&& a):
        data{a} {}
    explicit explicitFloat(const u32& a) { data.i= a; }
    explicit explicitFloat(u32&& a) { data.i= a; }
    explicitFloat& operator=(const explicitFloat& a)= default;
    explicitFloat& operator=(explicitFloat&& a) noexcept= default;
    explicitFloat& operator                             =(const f32& a) {
        data.f= a;
        return *this;
    }
    explicitFloat& operator=(f32&& a) {
        data.f= a;
        return *this;
    }
    explicitFloat& operator=(const u32& a) {
        data.i= a;
        return *this;
    }
    explicitFloat& operator=(u32&& a) {
        data.i= a;
        return *this;
    }
    // classical comparison on floats
    bool operator==(const explicitFloat& o) { return data.f == o.data.f; }
    bool operator!=(const explicitFloat& o) { return data.f != o.data.f; }
    bool operator>(const explicitFloat& o) { return data.f > o.data.f; }
    bool operator<(const explicitFloat& o) { return data.f < o.data.f; }
    bool operator>=(const explicitFloat& o) { return data.f >= o.data.f; }
    bool operator<=(const explicitFloat& o) { return data.f <= o.data.f; }
    bool operator==(const f32& o) { return data.f == o; }
    bool operator!=(const f32& o) { return data.f != o; }
    bool operator>(const f32& o) { return data.f > o; }
    bool operator<(const f32& o) { return data.f < o; }
    bool operator>=(const f32& o) { return data.f >= o; }
    bool operator<=(const f32& o) { return data.f <= o; }

    // 'member' access
    bool sign() const { return (data.i & f32const::signMask) != 0; }
    u8 exponentRaw() const { return (data.i & f32const::expoMask) >> 23; }
    std::string exponentRawBits() const {
        std::string a;
        for(u8 i= 0; i < 8; ++i) {
            u32 bitMask= 1U << (30U - i);
            a+= ((data.i & bitMask) == bitMask) ? "1" : "0";
        }
        return a;
    }
    s8 exponent() const { return exponentRaw() - f32const::expoBias; }
    u32 mantissaRaw() const { return (data.i & f32const::mantMask); }
    std::string mantissaRawBits() const {
        std::string a;
        for(u8 i= 0; i < 23; ++i) {
            u32 bitMask= 1U << (22U - i);
            a+= ((data.i & bitMask) == bitMask) ? "1" : "0";
        }
        return a;
    }
    f32 mantissaEval() const {
        u32 m = mantissaRaw();
        f32 result= 0.;
        f32 div = 0.5;
        for(u8 i= 0; i < 23; ++i) {
            u32 bitMask= 1U << (22U - i);
            result+= ((m & bitMask) == bitMask) * div;
            div *= 0.5;
        }
        return result;
    }
    std::string bits() const {
        std::string a;
        for(u8 i= 0; i < 32; ++i) {
            u32 bitMask= 1U << (31U - i);
            a+= ((data.i & bitMask) == bitMask) ? "1" : "0";
        }
        return a;
    }
    // normalized
    bool isNormalized() const {
        return !isDenormalized();
    }
    bool isDenormalized() const {
        return exponentRaw() == 0 || exponentRaw() == 0b11111111;
    }
    // export
    f32 asFloat() const { return data.f; }
    u32 asUInt() const { return data.i; }

    // Fast approximate log2(|x|). It assumes the sign is positive.
    f32 log2()const{
        return f32((s32)data.i - (s32)f32const::oneAsInt)*f32const::scaleDown;
    }
    // Fast approximate log2(|x|).
    f32 log2a()const{
        return f32((s32)(data.i&f32const::NotSign) - (s32)f32const::oneAsInt)*f32const::scaleDown;
    }
    f32 exp2()const{
        Data a;
        a.i = (s32)(data.f*f32const::scaleUp)+(s32)f32const::oneAsInt;
        return a.f;
    }

private:
    union Data {
        f32 f;
        u32 i;
    } data{0};
};

}// namespace fln