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
    ASSERT_EQ(a, 100000);
}

TEST(ne, simple) {
    bint_t a = 1000001;
    bint_t b = static_cast<NBigInt::bint_t>("100000");
    ASSERT_NE(a, b);
    ASSERT_NE(a, 1000000);
}

TEST(streams, io){
    std::stringstream i,o;
    bint_t a;
    std::string f = "123456789", s = "98765432";
    i << f << ' ' << s;
    i >> a;
    o << a << ' ';
    i >> a;
    o << a;
    ASSERT_EQ(o.str(), f + ' ' + s );
}

TEST(gtlt, all){
    bint_t a ( "55555555555555" );
    EXPECT_GT(a, 100);
    EXPECT_LT(100, a);
    bint_t b ( "44444444444444" );
    EXPECT_GT(a, b);
    EXPECT_LT(b, a);
}
/*
TEST(div, all){
    bint_t a ( "55555555555555" );
    EXPECT_THROW( b / 0, std::exception );
 }

TEST(multiply, all){
    bint_t a ( "55555555555555" );
    ASSERT_EQ(a * 0, 0 * a);
    ASSERT_EQ(a * 1, 1 * a);
    EXPECT_EQ(a * 5, static_cast<bint_t>("277777777777775"));
    EXPECT_EQ(a * a, static_cast<bint_t>("3086419753086358024691358025"));
}

TEST(pow, all){
    bint_t a ( "55555555555555" );
    ASSERT_EQ(a ^ 0, 1);
    ASSERT_EQ(0 ^ a, 1);
    ASSERT_EQ(0 ^ 0, 1);
    ASSERT_EQ(1 ^ a, 1);
    ASSERT_EQ(a ^ 1, a);
    EXPECT_EQ(a ^ 5, static_cast<bint_t>("529221494013419998645192975854798557130513429524632085243822926721875"));
    bint_t b = 55;
    EXPECT_EQ(b^b, static_cast<bint_t>("524744532468751923546122657597368049278513737089035272057324643668607677682302892208099365234375"));
}
*/


TEST(zerroes, emty){
    bint_t a;
    bint_t z = 0;
    ASSERT_EQ(z, a);
    ASSERT_EQ(0, a);
    a = static_cast<bint_t> ("0");
    ASSERT_EQ(0, a);
    a = static_cast<bint_t> ("");
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


