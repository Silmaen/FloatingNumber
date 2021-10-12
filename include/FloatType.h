/**
* \file FloatType.h
*
* \date 11/10/2021
* \author Silmaen
*/

#pragma once
#include "baseType.h"
#include <bitset>
/**
 * @namespace fln::object
 * @brief set of function based on a float object that allow bit manipulation
 */
namespace fln::object {
/**
 * @brief set of 32 constant and magic numbers
 */
namespace const32 {
constexpr u32 signMask = 0b10000000000000000000000000000000;
constexpr u32 expoMask = 0b01111111100000000000000000000000;
constexpr u32 mantMask = 0b00000000011111111111111111111111;
constexpr u8 expoBias  = 127;
constexpr u32 oneAsInt = 0x3f800000;
constexpr u32 notSign  = 0b01111111111111111111111111111111;
constexpr u32 notExpo  = 0b10000000011111111111111111111111;
constexpr u32 notMant = 0b11111111100000000000000000000000;
constexpr f32 scaleUp  = float(0x00800000);
constexpr f32 scaleDown= 1.0f / scaleUp;
}// namespace baseFloatconst
/**
 * @brief class to better handle float and their bits
 *
 * this class is not designed for performance
 */
struct BitFloat {
    using baseFloat=f32; ///< base internal type of float
    using baseBits=u32;  ///< base internal type of bits

    // ------------------------------------------------------------------------
    // constructor and assignations
    // ------------------------------------------------------------------------
    /**
     * @brief Default constructor.
     */
    BitFloat()= default;
    /**
     * @brief Default copy constructor.
     */
    BitFloat(const BitFloat&)= default;
    /**
     * @brief Default move constructor.
     */
    BitFloat(BitFloat&&) noexcept= default;
    /**
     * @brief Constructor based on a float.
     * @param a The input float.
     */
    explicit BitFloat(const baseFloat& a):
        data{a} {}
    /**
     * @brief Constructor copy based on float.
     * @param a The input float.
     */
    explicit BitFloat(baseFloat&& a):
        data{a} {}
    /**
     * @brief Constructor based on bits.
     * @param a The input bits.
     */
    explicit BitFloat(const baseBits& a) { data.i= a; }
    /**
     * @brief Constructor copy based on bits.
     * @param a The input bits.
     */
    explicit BitFloat(baseBits&& a) { data.i= a; }
    /**
     * @brief Default assignation operator.
     * @param a The other BitFloat.
     * @return this
     */
    BitFloat& operator=(const BitFloat& a)= default;
    /**
     * @brief Default assignation operator.
     * @param a The other BitFloat.
     * @return this
     */
    BitFloat& operator=(BitFloat&& a) noexcept= default;
    /**
     * @brief Assignation operator based on a float.
     * @param a The other Float.
     * @return this
     */
    BitFloat& operator=(const baseFloat& a) {
        data.f= a;
        return *this;
    }
    /**
     * @brief Assignation operator based on a float.
     * @param a The other Float.
     * @return this
     */
    BitFloat& operator=(baseFloat&& a) {
        data.f= a;
        return *this;
    }
    /**
     * @brief Assignation operator based on bits.
     * @param a The other bits.
     * @return this
     */
    BitFloat& operator=(const baseBits& a) {
        data.i= a;
        return *this;
    }
    /**
     * @brief Assignation operator based on bits.
     * @param a The other bits.
     * @return this
     */
    BitFloat& operator=(baseBits&& a) {
        data.i= a;
        return *this;
    }
    // ------------------------------------------------------------------------
    // classical comparison on floats
    // ------------------------------------------------------------------------
    /**
     * @brief Comparison operator equality.
     * @param o The BitFloat to compare.
     * @return true if equality
     */
    [[nodiscard]] bool operator==(const BitFloat& o) { return data.f == o.data.f; }
    /**
     * @brief Comparison operator inequality.
     * @param o The BitFloat to compare.
     * @return true if not equality
     */
    [[nodiscard]] bool operator!=(const BitFloat& o) { return data.f != o.data.f; }
    /**
     * @brief Comparison operator greater than.
     * @param o The BitFloat to compare.
     * @return true if this greater than o
     */
    [[nodiscard]] bool operator>(const BitFloat& o) { return data.f > o.data.f; }
    /**
     * @brief Comparison operator lower than.
     * @param o The BitFloat to compare.
     * @return true if this lower than o
     */
    [[nodiscard]] bool operator<(const BitFloat& o) { return data.f < o.data.f; }
    /**
     * @brief Comparison operator greater or equal than.
     * @param o The BitFloat to compare.
     * @return true if this greater or equal than o
     */
    [[nodiscard]] bool operator>=(const BitFloat& o) { return data.f >= o.data.f; }
    /**
     * @brief Comparison operator lower or equal than.
     * @param o The BitFloat to compare.
     * @return true if this lower or equal than o
     */
    [[nodiscard]] bool operator<=(const BitFloat& o) { return data.f <= o.data.f; }
    /**
     * @brief Comparison operator equality.
     * @param o The float to compare.
     * @return true if equality
     */
    [[nodiscard]] bool operator==(const baseFloat& o) { return data.f == o; }
    /**
     * @brief Comparison operator inequality.
     * @param o The float to compare.
     * @return true if not equality
     */
    [[nodiscard]] bool operator!=(const baseFloat& o) { return data.f != o; }
    /**
     * @brief Comparison operator greater than.
     * @param o The float to compare.
     * @return true if this greater than o
     */
    [[nodiscard]] bool operator>(const baseFloat& o) { return data.f > o; }
    /**
     * @brief Comparison operator lower than.
     * @param o The float to compare.
     * @return true if this lower than o
     */
    [[nodiscard]] bool operator<(const baseFloat& o) { return data.f < o; }
    /**
     * @brief Comparison operator greater or equal than.
     * @param o The float to compare.
     * @return true if this greater or equal than o
     */
    [[nodiscard]] bool operator>=(const baseFloat& o) { return data.f >= o; }
    /**
     * @brief Comparison operator lower or equal than.
     * @param o The float to compare.
     * @return true if this lower or equal than o
     */
    [[nodiscard]] bool operator<=(const baseFloat& o) { return data.f <= o; }

    // ------------------------------------------------------------------------
    // arithmetic operators
    // ------------------------------------------------------------------------
    /**
     * @brief Self add.
     * @param b The other number to add.
     * @return this
     */
    [[nodiscard]] BitFloat& operator+=(const BitFloat& b){data.f+=(b.fl());return *this;}
    /**
     * @brief Self add.
     * @param b The other number to add.
     * @return this
     */
    [[nodiscard]] BitFloat& operator+=(const baseFloat& b){data.f+=b;return *this;}
    /**
     * @brief Add.
     * @param b The other number to add.
     * @return Result
     */
    [[nodiscard]] BitFloat operator+(const BitFloat& b)const{BitFloat bb(*this);return bb+=b;}
    /**
     * @brief Add.
     * @param b The other number to add.
     * @return Result
     */
    [[nodiscard]] BitFloat operator+(const baseFloat& b)const{BitFloat bb(*this);return bb+=b;}
    /**
     * @brief Add.
     * @param b The other number to add.
     * @param a The number to add.
     * @return Result
     */
    [[nodiscard]] friend BitFloat operator+(const baseFloat& b, const BitFloat& a){return a+b;}

    /**
     * @brief Self subtract.
     * @param b The other number to subtract.
     * @return this
     */
    [[nodiscard]] BitFloat& operator-=(const BitFloat& b){data.f-=(b.fl());return *this;}
    /**
     * @brief Self subtract.
     * @param b The other number to subtract.
     * @return this
     */
    [[nodiscard]] BitFloat& operator-=(const baseFloat& b){data.f-=b;return *this;}
    /**
     * @brief subtract.
     * @param b The other number to subtract.
     * @return Result
     */
    [[nodiscard]] BitFloat operator-()const{BitFloat bb(*this);bb.toggleSign();return bb;}
    /**
     * @brief subtract.
     * @param b The other number to subtract.
     * @return Result
     */
    [[nodiscard]] BitFloat operator-(const BitFloat& b)const{BitFloat bb(*this);return bb-=b;}
    /**
     * @brief subtract.
     * @param b The other number to subtract.
     * @return Result
     */
    [[nodiscard]] BitFloat operator-(const baseFloat& b)const{BitFloat bb(*this);return bb-=b;}
    /**
     * @brief subtract.
     * @param b The other number to subtract.
     * @param a The number to subtract.
     * @return Result
     */
    [[nodiscard]] friend BitFloat operator-(const baseFloat& b, const BitFloat& a){return -a+b;}

    /**
     * @brief Self multiply.
     * @param b The other number to multiply.
     * @return this
     */
    [[nodiscard]] BitFloat& operator*=(const BitFloat& b){data.f*=(b.fl());return *this;}
    /**
     * @brief Self multiply.
     * @param b The other number to multiply.
     * @return this
     */
    [[nodiscard]] BitFloat& operator*=(const baseFloat& b){data.f*=b;return *this;}
    /**
     * @brief multiply.
     * @param b The other number to multiply.
     * @return Result
     */
    [[nodiscard]] BitFloat operator*(const BitFloat& b)const{BitFloat bb(*this);return bb*=b;}
    /**
     * @brief multiply.
     * @param b The other number to multiply.
     * @return Result
     */
    [[nodiscard]] BitFloat operator*(const baseFloat& b)const{BitFloat bb(*this);return bb*=b;}
    /**
     * @brief multiply.
     * @param b The other number to multiply.
     * @param a The number to multiply.
     * @return Result
     */
    [[nodiscard]] friend BitFloat operator*(const baseFloat& b, const BitFloat& a){return a*b;}

    /**
     * @brief Self divide.
     * @param b The other number to divide.
     * @return this
     */
    [[nodiscard]] BitFloat& operator/=(const BitFloat& b){data.f/=(b.fl());return *this;}
    /**
     * @brief Self divide.
     * @param b The other number to divide.
     * @return this
     */
    [[nodiscard]] BitFloat& operator/=(const baseFloat& b){data.f/=b;return *this;}
    /**
     * @brief divide.
     * @param b The other number to divide.
     * @return Result
     */
    [[nodiscard]] BitFloat operator/(const BitFloat& b)const{BitFloat bb(*this);return bb/=b;}
    /**
     * @brief divide.
     * @param b The other number to divide.
     * @return Result
     */
    [[nodiscard]] BitFloat operator/(const baseFloat& b)const{BitFloat bb(*this);return bb/=b;}
    /**
     * @brief divide.
     * @param b The other number to divide.
     * @param a The number to divide.
     * @return Result
     */
    [[nodiscard]] friend BitFloat operator/(const baseFloat& b, const BitFloat& a){return BitFloat(b/a.fl());}

    // ------------------------------------------------------------------------
    // bit shift operators
    // ------------------------------------------------------------------------
    /**
     * @brief Self bit shift left.
     * @param b The number of bits to shift.
     * @return this
     */
    [[nodiscard]] BitFloat& operator<<=(const BitFloat& b){data.i<<=(b.bits());return *this;}
    /**
     * @brief Self bit shift left.
     * @param b The number of bits to shift.
     * @return this
     */
    [[nodiscard]] BitFloat& operator<<=(const baseBits& b){data.i<<=b;return *this;}
    /**
     * @brief Bit shift left.
     * @param b The number of bits to shift.
     * @return Shifted Number
     */
    [[nodiscard]] BitFloat operator<<(const BitFloat& b)const{BitFloat bb(*this);return bb<<=b;}
    /**
     * @brief Bit shift left.
     * @param b The number of bits to shift.
     * @return Shifted Number
     */
    [[nodiscard]] BitFloat operator<<(const baseBits& b)const{BitFloat bb(*this);return bb<<=b;}
    /**
     * @brief Self bit shift right.
     * @param b The number of bits to shift.
     * @return this
     */
    [[nodiscard]] BitFloat& operator>>=(const BitFloat& b){data.i>>=(b.bits());return *this;}

    /**
     * @brief Self bit shift right.
     * @param b The number of bits to shift.
     * @return this
     */
    [[nodiscard]] BitFloat& operator>>=(const baseBits& b){data.i>>=b;return *this;}
    /**
     * @brief Bit shift right.
     * @param b The number of bits to shift.
     * @return Shifted Number
     */
    [[nodiscard]] BitFloat operator>>(const BitFloat& b)const{BitFloat bb(*this);return bb>>=b;}
    /**
     * @brief Bit shift right.
     * @param b The number of bits to shift.
     * @return Shifted Number
     */
    [[nodiscard]] BitFloat operator>>(const baseBits& b)const{BitFloat bb(*this);return bb>>=b;}
    // ------------------------------------------------------------------------
    // bitwise operators
    // ------------------------------------------------------------------------
    /**
     * @brief Self bitwise and.
     * @param b The bits to add.
     * @return this
     */
    [[nodiscard]] BitFloat& operator&=(const BitFloat& b){data.i&=(b.bits());return *this;}
    /**
     * @brief Self bitwise and.
     * @param b The bits to add.
     * @return this
     */
    [[nodiscard]] BitFloat& operator&=(const baseBits& b){data.i&=b;return *this;}
    /**
     * @brief Bitwise and.
     * @param b The bits to add.
     * @return Result
     */
    [[nodiscard]] BitFloat operator&(const BitFloat& b)const{BitFloat bb(*this);return bb&=b;}
    /**
     * @brief Bitwise and.
     * @param b The bits to add.
     * @return Result
     */
    [[nodiscard]] BitFloat operator&(const baseBits& b)const{BitFloat bb(*this);return bb&=b;}
    /**
     * @brief Self bitwise or.
     * @param b The bits to or.
     * @return this
     */
    [[nodiscard]] BitFloat& operator|=(const BitFloat& b){data.i|=(b.bits());return *this;}
    /**
     * @brief Self bitwise or.
     * @param b The bits to or.
     * @return this
     */
    [[nodiscard]] BitFloat& operator|=(const baseBits& b){data.i|=b;return *this;}
    /**
     * @brief Bitwise or.
     * @param b The bits to or.
     * @return Result
     */
    [[nodiscard]] BitFloat operator|(const BitFloat& b)const{BitFloat bb(*this);return bb|=b;}
    /**
     * @brief Bitwise or.
     * @param b The bits to or.
     * @return Result
     */
    [[nodiscard]] BitFloat operator|(const baseBits& b)const{BitFloat bb(*this);return bb|=b;}
    /**
     * @brief Self bitwise xor.
     * @param b The bits to xor.
     * @return this
     */
    [[nodiscard]] BitFloat& operator^=(const BitFloat& b){data.i^=(b.bits());return *this;}
    /**
     * @brief Self bitwise xor.
     * @param b The bits to xor.
     * @return this
     */
    [[nodiscard]] BitFloat& operator^=(const baseBits& b){data.i^=b;return *this;}
    /**
     * @brief Bitwise xor.
     * @param b The bits to xor.
     * @return Result
     */
    [[nodiscard]] BitFloat operator^(const BitFloat& b)const{BitFloat bb(*this);return bb^=b;}
    /**
     * @brief Bitwise xor.
     * @param b The bits to xor.
     * @return Result
     */
    [[nodiscard]] BitFloat operator^(const baseBits& b)const{BitFloat bb(*this);return bb^=b;}
    /**
     * @brief Bitwise not.
     * @param b The bits to not.
     * @return Result
     */
    [[nodiscard]] BitFloat operator~()const{BitFloat bb(*this);bb.bits()=~bb.bits();return bb;}

    // ------------------------------------------------------------------------
    // member Access
    // ------------------------------------------------------------------------
    // the sign bit
    /**
     * @brief Get the value of the bit sign
     * @return true if negative.
     */
    [[nodiscard]] bool sign() const { return (data.i & const32::signMask) != 0; }
    /**
     * @brief define the sign of the float
     * @param s the new sign
     */
    void setSign(bool s) { data.i= (data.i & const32::notSign) | (s * const32::signMask); }
    /**
     * @brief change the sign of the float
     */
    void toggleSign() { data.i^= const32::signMask; }

    // the exponent bits
    /**
     * @brief Get the bits representing the exponent.
     * @return The exponent bits.
     */
    [[nodiscard]] u8 exponentRaw() const { return (data.i & const32::expoMask) >> 23U; }
    /**
     * @brief get the exponent bits as a string.
     * @return String with bit representation.
     */
    [[nodiscard]] std::string exponentRawBits() const {
        std::string a;
        for(u8 i= 0; i < 8; ++i) {
            baseBits bitMask= 1U << (30U - i);
            a+= ((data.i & bitMask) == bitMask) ? "1" : "0";
        }
        return a;
    }
    /**
     * @brief Get The value of the exponent unbiased
     * @return unbiased value of the exponent
     */
    [[nodiscard]] s8 exponent() const { return exponentRaw() - const32::expoBias; }
    /**
     * @brief Define the exponent bits
     * @param exp the new exponent bits
     */
    void setExponentRaw(const u8& exp) { data.i= (data.i & const32::notExpo) | (baseBits(exp) << 23U); }
    /**
     * @brief Define the unbiased exponent.
     * @param exp unbiased exponent
     */
    void setExponent(const s8& exp) { setExponentRaw(exp + const32::expoBias); }

    // the mantissa bits
    /**
     * @brief Get raw bits of the mantissa.
     * @return The raw bits of the mantissa.
     */
    [[nodiscard]] baseBits mantissaRaw() const { return (data.i & const32::mantMask); }
    /**
     * @brief Get raw bits of the mantissa as string.
     * @return String with mantissa's bits.
     */
    [[nodiscard]] std::string mantissaRawBits() const {
        std::string a;
        for(u8 i= 0; i < 23; ++i) {
            baseBits bitMask= 1U << (22U - i);
            a+= ((data.i & bitMask) == bitMask) ? "1" : "0";
        }
        return a;
    }
    /**
     * @brief Get bits of the mantissa with the implicit one.
     * @return The bits of the mantissa.
     */
    [[nodiscard]] baseBits mantissa() const { return (data.i & const32::mantMask)| 1U<<23U; }
    /**
     * @brief Set raw bits of the mantissa.
     * @param m The bits of the mantissa.
     */
    void setMantissaRaw(const baseBits& m){data.i = ( data.i & const32::notMant) | (m & const32::mantMask);}

    /**
     * @brief Get a string representation of all bits.
     * @return String of the bits
     */
    [[nodiscard]] std::string rawBits() const {
        std::stringstream oss;
        oss  << "[" << std::bitset<1>(sign()) << "][" << std::bitset<8>(exponentRaw()) << "][" << std::bitset<23>(mantissaRaw()) << "]";
        return oss.str();
    }

    // ------------------------------------------------------------------------
    // Direct Access
    // ------------------------------------------------------------------------
    /**
     * @brief View this object as a float.
     * @return A float copy of this object.
     */
    [[nodiscard]] baseFloat getFloat() const { return data.f; }
    /**
     * @brief View this object as a set of bits.
     * @return A uint copy of this object
     */
    [[nodiscard]] baseBits getBits() const { return data.i; }
    /**
     * @brief Access to the bits const.
     * @return Const reference to the bits.
     */
    [[nodiscard]] const baseBits& bits()const{return data.i;}
    /**
     * @brief Access to the bits.
     * @return Reference to the bits.
     */
    [[nodiscard]] baseBits& bits(){return data.i;}
    /**
     * @brief Access to the bits const.
     * @return Const reference to the bits.
     */
    [[nodiscard]] const baseFloat& fl()const{return data.f;}
    /**
     * @brief Access to the bits.
     * @return Reference to the bits.
     */
    [[nodiscard]] baseFloat& fl(){return data.f;}

    // ------------------------------------------------------------------------
    // Normalization information
    // ------------------------------------------------------------------------
    /**
     * @brief Determine if a float is a normalize one.
     * @return true if the float is a normalized one.
     */
    [[nodiscard]] bool isNormalized() const {
        return !isDenormalized();
    }
    /**
     * @brief Determine if a float is not a normalize one.
     * @return true if the float is not a normalized one.
     */
    [[nodiscard]] bool isDenormalized() const {
        return (exponentRaw() == 0 && mantissaRaw() != 0 ) || exponentRaw() == 0b11111111;
    }
    /**
     * @brief Determine if a float is an infinite representation.
     * @return true if the float is an infinite representation.
     */
    [[nodiscard]] bool isInfinite()const {
        return ((data.i & const32::expoMask) == const32::expoMask)&&((data.i & const32::mantMask)==0);
    }
    /**
     * @brief Determine if a float is not a number.
     * @return true if the float is not a number.
     */
    [[nodiscard]] bool isNaN()const{
        return ((data.i & const32::expoMask) == const32::expoMask)&&((data.i & const32::mantMask)!=0);
    }
private:
    /**
     * @brief internal data
     */
    union Data {
        baseFloat f; ///< data view as float
        baseBits i; ///< data view as bits
    } data{0};
};

}// namespace fln::object