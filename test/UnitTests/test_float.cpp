#include <gtest/gtest.h>

#define IDEBUG
#include "baseDefines.h"
#include "FloatType.h"

using namespace fln::object;

TEST(BitFloat, Creations_affetation_comparison) {
    BitFloat f(-1789.523f); // constructor by float
    BitFloat f2(f);            // constructor by copy
    BitFloat f3;
    f3 = f;
    EXPECT_TRUE(f==f2);
    EXPECT_FALSE(f!=f2);
    EXPECT_FALSE(f<f2);
    EXPECT_FALSE(f>f2);
    EXPECT_TRUE(f<=f2);
    EXPECT_TRUE(f>=f2);
    EXPECT_TRUE(f==-1789.523f);
    EXPECT_FALSE(f!=-1789.523f);
    EXPECT_FALSE(f<-1789.523f);
    EXPECT_FALSE(f>-1789.523f);
    EXPECT_TRUE(f<=-1789.523f);
    EXPECT_TRUE(f>=-1789.523f);
    f2 = 1024U;
    EXPECT_FALSE(f3 == f2);
    BitFloat f4(1024U);
    EXPECT_TRUE(f4 == f2);
}

TEST(BitFloat, ElementManipulation){
    BitFloat f(-1789.523f); // constructor by float

    // sign manipulation
    EXPECT_TRUE(f.sign());
    f.toggleSign();
    EXPECT_FALSE(f.sign());
    f.setSign(true);
    EXPECT_TRUE(f.sign());

    // exponent manipulation
    EXPECT_EQ(f.exponentRaw(),0b10001001);
    EXPECT_EQ(f.exponent(),10);
    f.setExponent(11);
    EXPECT_EQ(f.exponent(),11);
    EXPECT_EQ(f.exponentRaw(),0b10001010);
    BitFloat ff(-1789.523f*2.0f);
    EXPECT_TRUE(f==ff);
    f.setExponent(10);

    // mantissa manipulation
    EXPECT_EQ(f.mantissaRaw(), 0b10111111011000010111100);
    EXPECT_EQ(f.mantissa(), 0b110111111011000010111100);
    f.setMantissaRaw(0b10111111011010010111100);
    EXPECT_EQ(f.fl(), -(1789.523f+0.125f));
}

TEST(BitFloat, Normalization){
    BitFloat f(-1789.523f);
    EXPECT_TRUE(f.isNormalized());
    EXPECT_FALSE(f.isInfinite());
    EXPECT_FALSE(f.isNaN());
    f=0.f;
    EXPECT_FALSE(f.isDenormalized());
    EXPECT_FALSE(f.isInfinite());
    EXPECT_FALSE(f.isNaN());
    f.setExponentRaw(255U);
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

TEST(BitFloat, DirectAccess){
    BitFloat f(-1789.523f);
    EXPECT_TRUE(f.getFloat() == -1789.523f);
    EXPECT_EQ(f.getBits(), 3302994108U);
    f.fl() = 0;
    EXPECT_TRUE(f.getFloat() == 0.f);
    EXPECT_TRUE(f.bits() == 0U);
}

TEST(BitFloat, BitsDisplay){
    BitFloat f(-1789.523f);
    EXPECT_STREQ(f.rawBits().c_str(), "[1][10001001][10111111011000010111100]");
    EXPECT_TRUE(f.sign());
    EXPECT_STREQ(f.mantissaRawBits().c_str(), "10111111011000010111100");
    EXPECT_STREQ(f.exponentRawBits().c_str(), "10001001");
    f= 1.0f;
    EXPECT_FALSE(f.sign());
    EXPECT_STREQ(f.mantissaRawBits().c_str(), "00000000000000000000000");
    EXPECT_STREQ(f.exponentRawBits().c_str(), "01111111");
    f= 512.0f;
    EXPECT_FALSE(f.sign());
    EXPECT_STREQ(f.mantissaRawBits().c_str(), "00000000000000000000000");
    EXPECT_STREQ(f.exponentRawBits().c_str(), "10001000");
}

TEST(BitFloat, ArithmeticOprators){
    BitFloat f(-12.5f);
    EXPECT_EQ((3.0+f).fl(),-9.5f);
    EXPECT_EQ((f+3.0).fl(),-9.5f);
    EXPECT_EQ((3.0-f).fl(),15.5f);
    EXPECT_EQ((f-3.0).fl(),-15.5f);
    EXPECT_EQ((3.0*f).fl(),-37.5f);
    EXPECT_EQ((f*3.0).fl(),-37.5f);
    EXPECT_EQ((f/3.0).fl(),-4.16666667f);
    EXPECT_EQ((3.0/f).fl(),-0.24f);
    BitFloat f3(3.0f);
    EXPECT_EQ((f3+f).fl(),-9.5f);
    EXPECT_EQ((f+f3).fl(),-9.5f);
    EXPECT_EQ((f3-f).fl(),15.5f);
    EXPECT_EQ((f-f3).fl(),-15.5f);
    EXPECT_EQ((f3*f).fl(),-37.5f);
    EXPECT_EQ((f*f3).fl(),-37.5f);
    EXPECT_EQ((f/f3).fl(),-4.16666667f);
    EXPECT_EQ((f3/f).fl(),-0.24f);
}

TEST(BitFloat, BitShiftOprators){
    BitFloat f(-1789.523f);
    EXPECT_EQ( (f << 3U).bits(), 654149088U);
    EXPECT_EQ( (f >> 3U).bits(), 412874263U);

}

TEST(BitFloat, BitwiseOprators){
    BitFloat f(-1789.523f);
    EXPECT_EQ( (f & ~f).bits(), 0U);
    EXPECT_EQ( (f | ~f).bits(), 4294967295U);
    EXPECT_EQ( (f ^ ~f).bits(), 4294967295U);
}
