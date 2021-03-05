//
// Created by ivan- on 05.03.2021.
//
#include <gtest/gtest.h>
#include "../big_integer.hpp"

using namespace NBigInt;
TEST(sum, simple_string_construct){
    bint_t a = static_cast<NBigInt::bint_t>("100000");
    bint_t b = static_cast<NBigInt::bint_t>("500");
    bint_t res = static_cast<NBigInt::bint_t>("100500");
    bint_t kek = a+b;
    ASSERT_EQ(res, kek);
}

TEST(sum, simple_int_construct){
    bint_t a = 100000;
    bint_t b = 500;
    bint_t res = 100500;
    bint_t kek = a+b;
    ASSERT_EQ(res, kek);
}

TEST(sum, really_big){
    bint_t a ( "100000000000000000000000000000000" );
    bint_t b ( "000000000000000000500000000000000");
    EXPECT_EQ(static_cast<bint_t>("100000000000000000500000000000000"), a + b);
    bint_t c ( "999999999999999999999999999999999");
    bint_t d ( "100000000000020000000000000000003");
    bint_t python_power ("1100000000000020000000000000000002");
    EXPECT_EQ(python_power, c + d);
}

TEST(diff, simple){
    bint_t a = 100000;
    bint_t b = 500;
    EXPECT_EQ(99500, a - b);
    EXPECT_THROW( b - a, std::underflow_error );
    bint_t c = 10000;
    bint_t d = 9999;
    EXPECT_EQ( c - 1 , d);
    c -= 1;
    EXPECT_EQ( c - d, d - c );
}

TEST(diff, really_big){
    bint_t a ("555555555555555555555555555");
    bint_t b ("444444444444444444444444444");
    bint_t ab("111111111111111111111111111");
    EXPECT_EQ(ab, a - b);
    EXPECT_THROW( b - a, std::underflow_error );
    bint_t c ("100000000000000000000000000");
    bint_t d ("99999999999999999999999999");
    EXPECT_EQ( c - 1 , d);
    c -= 1;
    EXPECT_EQ( c - d, d - c );
}

TEST(eq, simple) {
    bint_t a = 100000;
    bint_t b = static_cast<NBigInt::bint_t>("100000");
    ASSERT_EQ(a, b);
}

TEST(ne, simple) {
    bint_t a = 1000001;
    bint_t b = static_cast<NBigInt::bint_t>("100000");
    ASSERT_NE(a, b);
}

TEST(zerroes, emty){
    bint_t a;
    bint_t z = 0;

    ASSERT_EQ(z, a);
    ASSERT_EQ(0, a);
    a = static_cast<bint_t> ("0");
    ASSERT_EQ(0, a);
    a = 0;
    ASSERT_EQ(0, a);
}

TEST(deconstructs, simple){
    bint_t a;
    std::stringstream ss;
    ss << "123456 ";
    ss >> a;
    ss << "77777";
    ss >> a;
    ASSERT_EQ(77777, a);
}


int main(int argc, char* argv[]){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


