#include <gtest/gtest.h>

#define IDEBUG
#include "baseDefines.h"
#include "DoubleType.h"

using namespace fln::object;

TEST(BitDouble, Creations_affetation_comparison) {
    BitDouble f(-1789.523); // constructor by float
    EXPECT_EQ(f.fl(),-1789.523 );
    BitDouble f2(f);            // constructor by copy
    BitDouble f3;
    f3 = f;
    EXPECT_TRUE(f==f2);
    EXPECT_FALSE(f!=f2);
    EXPECT_FALSE(f<f2);
    EXPECT_FALSE(f>f2);
    EXPECT_TRUE(f<=f2);
    EXPECT_TRUE(f>=f2);
    EXPECT_TRUE(f==-1789.523);
    EXPECT_FALSE(f!=-1789.523);
    EXPECT_FALSE(f<-1789.523);
    EXPECT_FALSE(f>-1789.523);
    EXPECT_TRUE(f<=-1789.523);
    EXPECT_TRUE(f>=-1789.523);
    f2 = 1024ULL;
    EXPECT_FALSE(f3 == f2);
    BitDouble f4(1024ULL);
    EXPECT_TRUE(f4 == f2);
}

TEST(BitDouble, ElementManipulation){
    BitDouble f(-1789.523);
    // sign manipulation
    EXPECT_TRUE(f.sign());
    f.toggleSign();
    EXPECT_FALSE(f.sign());
    f.setSign(true);
    EXPECT_TRUE(f.sign());

    // exponent manipulation
    EXPECT_EQ(f.exponentRaw(),0b10000001001);
    EXPECT_EQ(f.exponent(),10);
    f.setExponent(11);
    EXPECT_EQ(f.exponent(),11);
    EXPECT_EQ(f.exponentRaw(),0b10000001010);
    BitDouble ff(-1789.523*2.0);
    EXPECT_TRUE(f==ff);
    f.setExponent(10);

    // mantissa manipulation
    EXPECT_EQ(f.mantissaRaw(), 0b1011111101100001011110001101010011111101111100111011);
    EXPECT_EQ(f.mantissa(), 0b11011111101100001011110001101010011111101111100111011);
    f.setMantissaRaw(0b1011111101101001011110001101010011111101111100111011);
    EXPECT_EQ(f.mantissaRaw(), 0b1011111101101001011110001101010011111101111100111011);
    BitDouble ff2(-(1789.523+0.125));
    EXPECT_EQ(f.fl(),-(1789.523+0.125));
}

TEST(BitDouble, Normalization){
    BitDouble f(-1789.523);
    EXPECT_TRUE(f.isNormalized());
    EXPECT_FALSE(f.isInfinite());
    EXPECT_FALSE(f.isNaN());
    f=0.f;
    EXPECT_FALSE(f.isDenormalized());
    EXPECT_FALSE(f.isInfinite());
    EXPECT_FALSE(f.isNaN());
    f.setExponentRaw(2047UL);
    EXPECT_TRUE(f.isDenormalized());
    EXPECT_TRUE(f.isInfinite());
    EXPECT_FALSE(f.isNaN());
    f.setMantissaRaw(128U);
    EXPECT_TRUE(f.isDenormalized());
    EXPECT_FALSE(f.isInfinite());
    EXPECT_TRUE(f.isNaN());
    f.setExponentRaw(0U);
    EXPECT_TRUE(f.isDenormalized());
    EXPECT_FALSE(f.isInfinite());
    EXPECT_FALSE(f.isNaN());
}

TEST(BitDouble, DirectAccess){
    BitDouble f(-1789.523);
    EXPECT_TRUE(f.getFloat() == -1789.523);
    EXPECT_EQ(f.getBits(), 13878957257687818043ULL);
    f.fl() = 0;
    EXPECT_TRUE(f.getFloat() == 0.);
    EXPECT_TRUE(f.bits() == 0U);
}

TEST(BitDouble, BitsDisplay){
    BitDouble f(-1789.523);
    EXPECT_STREQ(f.rawBits().c_str(), "[1][10000001001][1011111101100001011110001101010011111101111100111011]");
    EXPECT_TRUE(f.sign());
    EXPECT_STREQ(f.mantissaRawBits().c_str(), "1011111101100001011110001101010011111101111100111011");
    EXPECT_STREQ(f.exponentRawBits().c_str(), "10000001001");
    f= 1.0;
    EXPECT_FALSE(f.sign());
    EXPECT_STREQ(f.mantissaRawBits().c_str(), "0000000000000000000000000000000000000000000000000000");
    EXPECT_STREQ(f.exponentRawBits().c_str(), "01111111111");
    f= 512.0;
    EXPECT_FALSE(f.sign());
    EXPECT_STREQ(f.mantissaRawBits().c_str(), "0000000000000000000000000000000000000000000000000000");
    EXPECT_STREQ(f.exponentRawBits().c_str(), "10000001000");
}

TEST(BitDouble, ArithmeticOprators){
    BitDouble f(-12.5);
    EXPECT_EQ((3.0+f).fl(),-9.5);
    EXPECT_EQ((f+3.0).fl(),-9.5);
    EXPECT_EQ((3.0-f).fl(),15.5);
    EXPECT_EQ((f-3.0).fl(),-15.5);
    EXPECT_EQ((3.0*f).fl(),-37.5);
    EXPECT_EQ((f*3.0).fl(),-37.5);
    EXPECT_EQ((f/3.0).fl(),-4.16666666666666667);
    EXPECT_EQ((3.0/f).fl(),-0.24);
    BitDouble f3(3.0);
    EXPECT_EQ((f3+f).fl(),-9.5);
    EXPECT_EQ((f+f3).fl(),-9.5);
    EXPECT_EQ((f3-f).fl(),15.5);
    EXPECT_EQ((f-f3).fl(),-15.5);
    EXPECT_EQ((f3*f).fl(),-37.5);
    EXPECT_EQ((f*f3).fl(),-37.5);
    EXPECT_EQ((f/f3).fl(),-4.1666666666666666667);
    EXPECT_EQ((f3/f).fl(),-0.24);
}

TEST(BitDouble, BitShiftOprators){
    BitDouble f(-1789.523);
    EXPECT_EQ( (f << 3U).bits(), 351193619245234648ULL);
    EXPECT_EQ( (f >> 3U).bits(), 1734869657210977255ULL);

}

TEST(BitDouble, BitwiseOprators){
    BitDouble f(-1789.523);
    EXPECT_EQ( (f & ~f).bits(), 0ULL);
    EXPECT_EQ( (f | ~f).bits(), 18446744073709551615ULL);
    EXPECT_EQ( (f ^ ~f).bits(), 18446744073709551615ULL);
}
