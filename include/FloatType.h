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
using baseFloat               = f32;                              ///< base internal type of float
using baseBits                = u32;                              ///< base internal type of bits
constexpr baseBits one        = 1U;                               ///< one
constexpr baseBits mantBitNum = 23U;                              ///< number of bit in the mantissa (see IEEE 754)
constexpr baseBits expoBitNum = 8U;                               ///< number of bits in the exponent (see IEEE 754)
constexpr baseBits signMask   = 0x80000000;                       ///< bit mask for the sign
constexpr baseBits expoMask   = 0x7F800000;                       ///< bit mask for the exponent
constexpr baseBits mantMask   = 0x007FFFFF;                       ///< bitmask for the mantissa
constexpr baseBits expoBias   = (one << (expoBitNum - one)) - one;///< bias of exponent (see IEEE 754)
constexpr baseBits notSign    = ~signMask;                        ///< bit mask for all except the sign
constexpr baseBits notExpo    = ~expoMask;                        ///< bit mask for all except the exponent
constexpr baseBits notMant    = ~mantMask;                        ///< bitmask for all except the mantissa
constexpr baseBits fullExpo   = expoMask >> mantBitNum;           ///< exponent fully filled
constexpr baseBits implicitBit= one << mantBitNum;                ///< the implicit mantissa bit
}// namespace const32
/**
 * @brief class to better handle float and their bits
 *
 * this class is not designed for performance
 */
struct BitFloat {
    using baseFloat= const32::baseFloat;///< base internal type of float
    using baseBits = const32::baseBits; ///< base internal type of bits

    // ------------------------------------------------------------------------
    // constructor and assignations
    // ------------------------------------------------------------------------
    /**
     * @brief Default constructor.
     */
    constexpr BitFloat() noexcept= default;
    /**
     * @brief Default copy constructor.
     */
    constexpr BitFloat(const BitFloat&) noexcept= default;
    /**
     * @brief Default move constructor.
     */
    constexpr BitFloat(BitFloat&&) noexcept= default;
    /**
     * @brief Constructor based on a float.
     * @param a The input float.
     */
    explicit constexpr BitFloat(const baseFloat& a) noexcept:
        data{a} {}
    /**
     * @brief Constructor copy based on float.
     * @param a The input float.
     */
    explicit constexpr BitFloat(baseFloat&& a) noexcept:
        data{a} {}
    /**
     * @brief Constructor based on bits.
     * @param a The input bits.
     */
    explicit constexpr BitFloat(const baseBits& a) noexcept { data.i= a; }
    /**
     * @brief Constructor copy based on bits.
     * @param a The input bits.
     */
    explicit constexpr BitFloat(baseBits&& a) noexcept { data.i= a; }
    /**
     * @brief Default assignation operator.
     * @param a The other BitFloat.
     * @return this
     */
    constexpr BitFloat& operator=(const BitFloat& a) noexcept= default;
    /**
     * @brief Default assignation operator.
     * @param a The other BitFloat.
     * @return this
     */
    constexpr BitFloat& operator=(BitFloat&& a) noexcept= default;
    /**
     * @brief Assignation operator based on a float.
     * @param a The other Float.
     * @return this
     */
    constexpr BitFloat& operator=(const baseFloat& a) noexcept {
        data.f= a;
        return *this;
    }
    /**
     * @brief Assignation operator based on a float.
     * @param a The other Float.
     * @return this
     */
    constexpr BitFloat& operator=(baseFloat&& a) noexcept {
        data.f= a;
        return *this;
    }
    /**
     * @brief Assignation operator based on bits.
     * @param a The other bits.
     * @return this
     */
    constexpr BitFloat& operator=(const baseBits& a) noexcept {
        data.i= a;
        return *this;
    }
    /**
     * @brief Assignation operator based on bits.
     * @param a The other bits.
     * @return this
     */
    constexpr BitFloat& operator=(baseBits&& a) noexcept {
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
    [[nodiscard]] constexpr bool operator==(const BitFloat& o) const noexcept{ return data.f == o.data.f; }
    /**
     * @brief Comparison operator inequality.
     * @param o The BitFloat to compare.
     * @return true if not equality
     */
    [[nodiscard]] constexpr bool operator!=(const BitFloat& o) const noexcept{ return data.f != o.data.f; }
    /**
     * @brief Comparison operator greater than.
     * @param o The BitFloat to compare.
     * @return true if this greater than o
     */
    [[nodiscard]] constexpr bool operator>(const BitFloat& o) const noexcept{ return data.f > o.data.f; }
    /**
     * @brief Comparison operator lower than.
     * @param o The BitFloat to compare.
     * @return true if this lower than o
     */
    [[nodiscard]] constexpr bool operator<(const BitFloat& o) const noexcept{ return data.f < o.data.f; }
    /**
     * @brief Comparison operator greater or equal than.
     * @param o The BitFloat to compare.
     * @return true if this greater or equal than o
     */
    [[nodiscard]] constexpr bool operator>=(const BitFloat& o) const noexcept{ return data.f >= o.data.f; }
    /**
     * @brief Comparison operator lower or equal than.
     * @param o The BitFloat to compare.
     * @return true if this lower or equal than o
     */
    [[nodiscard]] constexpr bool operator<=(const BitFloat& o) const noexcept{ return data.f <= o.data.f; }
    /**
     * @brief Comparison operator equality.
     * @param o The float to compare.
     * @return true if equality
     */
    [[nodiscard]] constexpr bool operator==(const baseFloat& o) const noexcept{ return data.f == o; }
    /**
     * @brief Comparison operator inequality.
     * @param o The float to compare.
     * @return true if not equality
     */
    [[nodiscard]] constexpr bool operator!=(const baseFloat& o) const noexcept{ return data.f != o; }
    /**
     * @brief Comparison operator greater than.
     * @param o The float to compare.
     * @return true if this greater than o
     */
    [[nodiscard]] constexpr bool operator>(const baseFloat& o) const noexcept{ return data.f > o; }
    /**
     * @brief Comparison operator lower than.
     * @param o The float to compare.
     * @return true if this lower than o
     */
    [[nodiscard]] constexpr bool operator<(const baseFloat& o) const noexcept{ return data.f < o; }
    /**
     * @brief Comparison operator greater or equal than.
     * @param o The float to compare.
     * @return true if this greater or equal than o
     */
    [[nodiscard]] constexpr bool operator>=(const baseFloat& o) const noexcept{ return data.f >= o; }
    /**
     * @brief Comparison operator lower or equal than.
     * @param o The float to compare.
     * @return true if this lower or equal than o
     */
    [[nodiscard]] constexpr bool operator<=(const baseFloat& o) const noexcept{ return data.f <= o; }

    // ------------------------------------------------------------------------
    // arithmetic operators
    // ------------------------------------------------------------------------
    /**
     * @brief Self add.
     * @param b The other number to add.
     * @return this
     */
    [[nodiscard]] constexpr BitFloat& operator+=(const BitFloat& b) noexcept{
        data.f+= (b.fl());
        return *this;
    }
    /**
     * @brief Self add.
     * @param b The other number to add.
     * @return this
     */
    [[nodiscard]] constexpr BitFloat& operator+=(const baseFloat& b) noexcept{
        data.f+= b;
        return *this;
    }
    /**
     * @brief Add.
     * @param b The other number to add.
     * @return Result
     */
    [[nodiscard]] constexpr BitFloat operator+(const BitFloat& b) const noexcept{
        BitFloat bb(*this);
        return bb+= b;
    }
    /**
     * @brief Add.
     * @param b The other number to add.
     * @return Result
     */
    [[nodiscard]] constexpr BitFloat operator+(const baseFloat& b) const noexcept{
        BitFloat bb(*this);
        return bb+= b;
    }
    /**
     * @brief Add.
     * @param b The other number to add.
     * @param a The number to add.
     * @return Result
     */
    [[nodiscard]] friend constexpr BitFloat operator+(const baseFloat& b, const BitFloat& a) noexcept{ return a + b; }

    /**
     * @brief Self subtract.
     * @param b The other number to subtract.
     * @return this
     */
    [[nodiscard]] constexpr BitFloat& operator-=(const BitFloat& b) noexcept{
        data.f-= (b.fl());
        return *this;
    }
    /**
     * @brief Self subtract.
     * @param b The other number to subtract.
     * @return this
     */
    [[nodiscard]] constexpr BitFloat& operator-=(const baseFloat& b) noexcept{
        data.f-= b;
        return *this;
    }
    /**
     * @brief subtract.
     * @param b The other number to subtract.
     * @return Result
     */
    [[nodiscard]] constexpr BitFloat operator-() const noexcept{
        BitFloat bb(*this);
        bb.toggleSign();
        return bb;
    }
    /**
     * @brief subtract.
     * @param b The other number to subtract.
     * @return Result
     */
    [[nodiscard]] constexpr BitFloat operator-(const BitFloat& b) const noexcept{
        BitFloat bb(*this);
        return bb-= b;
    }
    /**
     * @brief subtract.
     * @param b The other number to subtract.
     * @return Result
     */
    [[nodiscard]] constexpr BitFloat operator-(const baseFloat& b) const noexcept{
        BitFloat bb(*this);
        return bb-= b;
    }
    /**
     * @brief subtract.
     * @param b The other number to subtract.
     * @param a The number to subtract.
     * @return Result
     */
    [[nodiscard]] friend constexpr BitFloat operator-(const baseFloat& b, const BitFloat& a) noexcept{ return -a + b; }

    /**
     * @brief Self multiply.
     * @param b The other number to multiply.
     * @return this
     */
    [[nodiscard]] constexpr BitFloat& operator*=(const BitFloat& b) noexcept{
        data.f*= (b.fl());
        return *this;
    }
    /**
     * @brief Self multiply.
     * @param b The other number to multiply.
     * @return this
     */
    [[nodiscard]] constexpr BitFloat& operator*=(const baseFloat& b) noexcept{
        data.f*= b;
        return *this;
    }
    /**
     * @brief multiply.
     * @param b The other number to multiply.
     * @return Result
     */
    [[nodiscard]] constexpr BitFloat operator*(const BitFloat& b) const noexcept{
        BitFloat bb(*this);
        return bb*= b;
    }
    /**
     * @brief multiply.
     * @param b The other number to multiply.
     * @return Result
     */
    [[nodiscard]] constexpr BitFloat operator*(const baseFloat& b) const noexcept{
        BitFloat bb(*this);
        return bb*= b;
    }
    /**
     * @brief multiply.
     * @param b The other number to multiply.
     * @param a The number to multiply.
     * @return Result
     */
    [[nodiscard]] friend constexpr BitFloat operator*(const baseFloat& b, const BitFloat& a) noexcept{ return a * b; }

    /**
     * @brief Self divide.
     * @param b The other number to divide.
     * @return this
     */
    [[nodiscard]] constexpr BitFloat& operator/=(const BitFloat& b) noexcept{
        data.f/= (b.fl());
        return *this;
    }
    /**
     * @brief Self divide.
     * @param b The other number to divide.
     * @return this
     */
    [[nodiscard]] constexpr BitFloat& operator/=(const baseFloat& b) noexcept{
        data.f/= b;
        return *this;
    }
    /**
     * @brief divide.
     * @param b The other number to divide.
     * @return Result
     */
    [[nodiscard]] constexpr BitFloat operator/(const BitFloat& b) const noexcept{
        BitFloat bb(*this);
        return bb/= b;
    }
    /**
     * @brief divide.
     * @param b The other number to divide.
     * @return Result
     */
    [[nodiscard]] constexpr BitFloat operator/(const baseFloat& b) const noexcept{
        BitFloat bb(*this);
        return bb/= b;
    }
    /**
     * @brief divide.
     * @param b The other number to divide.
     * @param a The number to divide.
     * @return Result
     */
    [[nodiscard]] friend constexpr BitFloat operator/(const baseFloat& b, const BitFloat& a) noexcept{ return BitFloat(b / a.fl()); }

    // ------------------------------------------------------------------------
    // bit shift operators
    // ------------------------------------------------------------------------
    /**
     * @brief Self bit shift left.
     * @param b The number of bits to shift.
     * @return this
     */
    [[nodiscard]] constexpr BitFloat& operator<<=(const BitFloat& b) noexcept{
        data.i<<= (b.bits());
        return *this;
    }
    /**
     * @brief Self bit shift left.
     * @param b The number of bits to shift.
     * @return this
     */
    [[nodiscard]] constexpr BitFloat& operator<<=(const baseBits& b) noexcept{
        data.i<<= b;
        return *this;
    }
    /**
     * @brief Bit shift left.
     * @param b The number of bits to shift.
     * @return Shifted Number
     */
    [[nodiscard]] constexpr BitFloat operator<<(const BitFloat& b) const noexcept{
        BitFloat bb(*this);
        return bb<<= b;
    }
    /**
     * @brief Bit shift left.
     * @param b The number of bits to shift.
     * @return Shifted Number
     */
    [[nodiscard]] constexpr BitFloat operator<<(const baseBits& b) const noexcept{
        BitFloat bb(*this);
        return bb<<= b;
    }
    /**
     * @brief Self bit shift right.
     * @param b The number of bits to shift.
     * @return this
     */
    [[nodiscard]] constexpr BitFloat& operator>>=(const BitFloat& b) noexcept{
        data.i>>= (b.bits());
        return *this;
    }

    /**
     * @brief Self bit shift right.
     * @param b The number of bits to shift.
     * @return this
     */
    [[nodiscard]] constexpr BitFloat& operator>>=(const baseBits& b) noexcept{
        data.i>>= b;
        return *this;
    }
    /**
     * @brief Bit shift right.
     * @param b The number of bits to shift.
     * @return Shifted Number
     */
    [[nodiscard]] constexpr BitFloat operator>>(const BitFloat& b) const noexcept{
        BitFloat bb(*this);
        return bb>>= b;
    }
    /**
     * @brief Bit shift right.
     * @param b The number of bits to shift.
     * @return Shifted Number
     */
    [[nodiscard]] constexpr BitFloat operator>>(const baseBits& b) const noexcept{
        BitFloat bb(*this);
        return bb>>= b;
    }
    // ------------------------------------------------------------------------
    // bitwise operators
    // ------------------------------------------------------------------------
    /**
     * @brief Self bitwise and.
     * @param b The bits to add.
     * @return this
     */
    [[nodiscard]] constexpr BitFloat& operator&=(const BitFloat& b) noexcept{
        data.i&= (b.bits());
        return *this;
    }
    /**
     * @brief Self bitwise and.
     * @param b The bits to add.
     * @return this
     */
    [[nodiscard]] constexpr BitFloat& operator&=(const baseBits& b) noexcept{
        data.i&= b;
        return *this;
    }
    /**
     * @brief Bitwise and.
     * @param b The bits to add.
     * @return Result
     */
    [[nodiscard]] constexpr BitFloat operator&(const BitFloat& b) const noexcept{
        BitFloat bb(*this);
        return bb&= b;
    }
    /**
     * @brief Bitwise and.
     * @param b The bits to add.
     * @return Result
     */
    [[nodiscard]] constexpr BitFloat operator&(const baseBits& b) const noexcept{
        BitFloat bb(*this);
        return bb&= b;
    }
    /**
     * @brief Self bitwise or.
     * @param b The bits to or.
     * @return this
     */
    [[nodiscard]] constexpr BitFloat& operator|=(const BitFloat& b) noexcept{
        data.i|= (b.bits());
        return *this;
    }
    /**
     * @brief Self bitwise or.
     * @param b The bits to or.
     * @return this
     */
    [[nodiscard]] constexpr BitFloat& operator|=(const baseBits& b) noexcept{
        data.i|= b;
        return *this;
    }
    /**
     * @brief Bitwise or.
     * @param b The bits to or.
     * @return Result
     */
    [[nodiscard]] constexpr BitFloat operator|(const BitFloat& b) const noexcept{
        BitFloat bb(*this);
        return bb|= b;
    }
    /**
     * @brief Bitwise or.
     * @param b The bits to or.
     * @return Result
     */
    [[nodiscard]] constexpr BitFloat operator|(const baseBits& b) const noexcept{
        BitFloat bb(*this);
        return bb|= b;
    }
    /**
     * @brief Self bitwise xor.
     * @param b The bits to xor.
     * @return this
     */
    [[nodiscard]] constexpr BitFloat& operator^=(const BitFloat& b) noexcept{
        data.i^= (b.bits());
        return *this;
    }
    /**
     * @brief Self bitwise xor.
     * @param b The bits to xor.
     * @return this
     */
    [[nodiscard]] constexpr BitFloat& operator^=(const baseBits& b) noexcept{
        data.i^= b;
        return *this;
    }
    /**
     * @brief Bitwise xor.
     * @param b The bits to xor.
     * @return Result
     */
    [[nodiscard]] constexpr BitFloat operator^(const BitFloat& b) const noexcept{
        BitFloat bb(*this);
        return bb^= b;
    }
    /**
     * @brief Bitwise xor.
     * @param b The bits to xor.
     * @return Result
     */
    [[nodiscard]] constexpr BitFloat operator^(const baseBits& b) const noexcept{
        BitFloat bb(*this);
        return bb^= b;
    }
    /**
     * @brief Bitwise not.
     * @param b The bits to not.
     * @return Result
     */
    [[nodiscard]] constexpr BitFloat operator~() const noexcept{
        BitFloat bb(*this);
        bb.bits()= ~bb.bits();
        return bb;
    }

    // ------------------------------------------------------------------------
    // member Access
    // ------------------------------------------------------------------------
    // the sign bit
    /**
     * @brief Get the value of the bit sign
     * @return true if negative.
     */
    [[nodiscard]] constexpr bool sign() const noexcept{ return (data.i & const32::signMask) != 0; }
    /**
     * @brief define the sign of the float
     * @param s the new sign
     */
    void setSign(bool s) noexcept{ data.i= (data.i & const32::notSign) | (s * const32::signMask); }
    /**
     * @brief change the sign of the float
     */
    constexpr void toggleSign() noexcept{ data.i^= const32::signMask; }

    // the exponent bits
    /**
     * @brief Get the bits representing the exponent.
     * @return The exponent bits.
     */
    [[nodiscard]] constexpr u8 exponentRaw() const noexcept{ return (data.i & const32::expoMask) >> const32::mantBitNum; }
    /**
     * @brief get the exponent bits as a string.
     * @return String with bit representation.
     */
    [[nodiscard]] std::string exponentRawBits() const noexcept{
        std::string a;
        for(u8 i= 0; i < const32::expoBitNum; ++i) {
            baseBits bitMask= const32::one << (const32::expoBitNum + const32::mantBitNum - const32::one - i);
            a+= ((data.i & bitMask) == bitMask) ? "1" : "0";
        }
        return a;
    }
    /**
     * @brief Get The value of the exponent unbiased
     * @return unbiased value of the exponent
     */
    [[nodiscard]] constexpr s8 exponent() const noexcept{ return exponentRaw() - const32::expoBias; }
    /**
     * @brief Define the exponent bits
     * @param exp the new exponent bits
     */
    void setExponentRaw(const u8& exp) noexcept{ data.i= (data.i & const32::notExpo) | (baseBits(exp) << const32::mantBitNum); }
    /**
     * @brief Define the unbiased exponent.
     * @param exp unbiased exponent
     */
    void setExponent(const s8& exp) noexcept{ setExponentRaw(exp + const32::expoBias); }

    // the mantissa bits
    /**
     * @brief Get raw bits of the mantissa.
     * @return The raw bits of the mantissa.
     */
    [[nodiscard]] constexpr baseBits mantissaRaw() const noexcept{ return (data.i & const32::mantMask); }
    /**
     * @brief Get raw bits of the mantissa as string.
     * @return String with mantissa's bits.
     */
    [[nodiscard]] std::string mantissaRawBits() const noexcept{
        std::string a;
        for(u8 i= 0; i < const32::mantBitNum; ++i) {
            baseBits bitMask= const32::one << (const32::mantBitNum - const32::one - i);
            a+= ((data.i & bitMask) == bitMask) ? "1" : "0";
        }
        return a;
    }
    /**
     * @brief Get bits of the mantissa with the implicit one.
     * @return The bits of the mantissa.
     */
    [[nodiscard]] constexpr baseBits mantissa() const noexcept{ return (data.i & const32::mantMask) | const32::implicitBit; }
    /**
     * @brief Set raw bits of the mantissa.
     * @param m The bits of the mantissa.
     */
    void setMantissaRaw(const baseBits& m) noexcept{ data.i= (data.i & const32::notMant) | (m & const32::mantMask); }

    /**
     * @brief Get a string representation of all bits.
     * @return String of the bits
     */
    [[nodiscard]] std::string rawBits() const noexcept{
        std::stringstream oss;
        oss << "[" << std::bitset<const32::one>(sign()) << "][" << std::bitset<const32::expoBitNum>(exponentRaw()) << "][" << std::bitset<const32::mantBitNum>(mantissaRaw()) << "]";
        return oss.str();
    }

    // ------------------------------------------------------------------------
    // Direct Access
    // ------------------------------------------------------------------------
    /**
     * @brief View this object as a float.
     * @return A float copy of this object.
     */
    [[nodiscard]] constexpr baseFloat getFloat() const noexcept{ return data.f; }
    /**
     * @brief View this object as a set of bits.
     * @return A uint copy of this object
     */
    [[nodiscard]] constexpr baseBits getBits() const noexcept{ return data.i; }
    /**
     * @brief Access to the bits const.
     * @return Const reference to the bits.
     */
    [[nodiscard]] constexpr const baseBits& bits() const noexcept{ return data.i; }
    /**
     * @brief Access to the bits.
     * @return Reference to the bits.
     */
    [[nodiscard]] constexpr baseBits& bits() noexcept{ return data.i; }
    /**
     * @brief Access to the bits const.
     * @return Const reference to the bits.
     */
    [[nodiscard]] constexpr const baseFloat& fl() const noexcept{ return data.f; }
    /**
     * @brief Access to the bits.
     * @return Reference to the bits.
     */
    [[nodiscard]] constexpr baseFloat& fl() noexcept{ return data.f; }

    // ------------------------------------------------------------------------
    // Normalization information
    // ------------------------------------------------------------------------
    /**
     * @brief Determine if a float is a normalize one.
     * @return true if the float is a normalized one.
     */
    [[nodiscard]] constexpr bool isNormalized() const noexcept{
        return !isDenormalized();
    }
    /**
     * @brief Determine if a float is not a normalize one.
     * @return true if the float is not a normalized one.
     */
    [[nodiscard]] constexpr bool isDenormalized() const noexcept{
        return (exponentRaw() == 0 && mantissaRaw() != 0) || exponentRaw() == const32::fullExpo;
    }
    /**
     * @brief Determine if a float is an infinite representation.
     * @return true if the float is an infinite representation.
     */
    [[nodiscard]] constexpr bool isInfinite() const noexcept{
        return ((data.i & const32::expoMask) == const32::expoMask) && ((data.i & const32::mantMask) == 0);
    }
    /**
     * @brief Determine if a float is not a number.
     * @return true if the float is not a number.
     */
    [[nodiscard]] constexpr bool isNaN() const noexcept{
        return ((data.i & const32::expoMask) == const32::expoMask) && ((data.i & const32::mantMask) != 0);
    }

private:
    /**
     * @brief internal data
     */
    union Data {
        baseFloat f;///< data view as float
        baseBits i; ///< data view as bits
    } data{0};
};

}// namespace fln::object