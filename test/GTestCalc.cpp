//
// Created by ivan- on 05.03.2021.
//
#include <gtest/gtest.h>
#include "../big_integer.hpp"

#include <cmath>

using namespace NBigInt;
TEST(sum, simple_string_construct){
    TBint a = static_cast<NBigInt::TBint>("100000");
    TBint b = static_cast<NBigInt::TBint>("500");
    TBint res = static_cast<NBigInt::TBint>("100500");
    TBint kek = a+b;
    ASSERT_EQ(res, kek);
}


TEST(sum, simple_int_construct){
    TBint a = 100000;
    TBint b = 500;
    TBint res = 100500;
    TBint kek = a+b;
    ASSERT_EQ(res, kek);
}

TEST(sum, really_big){
    TBint a ( "100000000000000000000000000000000" );
    TBint b ( "000000000000000000500000000000000");
    EXPECT_EQ(static_cast<TBint>("100000000000000000500000000000000"), a + b);
    TBint c ( "999999999999999999999999999999999");
    TBint d ( "100000000000020000000000000000003");
    TBint python_power ("1100000000000020000000000000000002");
    EXPECT_EQ(python_power, c + d);
}

TEST(diff, simple){
    TBint a = 100000;
    TBint b = 500;
    EXPECT_EQ(99500, a - b);
#ifdef EXCEPTION_OPT
    EXPECT_THROW( b - a, std::underflow_error );
#endif
    TBint c = 10000;
    TBint d = 9999;
    EXPECT_EQ( c - 1 , d);
    c -= 1;
    EXPECT_EQ( c - d, d - c );
}

TEST(diff, really_big){
    TBint a ("555555555555555555555555555");
    TBint b ("444444444444444444444444444");
    TBint ab("111111111111111111111111111");
    EXPECT_EQ(ab, a - b);
#ifdef EXCEPTION_OPT
    EXPECT_THROW( b - a, std::underflow_error );
#endif
    TBint c ("100000000000000000000000000");
    TBint d ("99999999999999999999999999");
    EXPECT_EQ( c - 1 , d);
    c -= 1;
    EXPECT_EQ( c - d, d - c );
}

TEST(eq, simple) {
    TBint a = 100000;
    TBint b = static_cast<NBigInt::TBint>("100000");
    ASSERT_EQ(a, b);
    ASSERT_EQ(a, 100000);
}

TEST(ne, simple) {
    TBint a = 1000001;
    TBint b = static_cast<NBigInt::TBint>("100000");
    ASSERT_NE(a, b);
    ASSERT_NE(a, 1000000);
}

TEST(streams, io){
    std::stringstream i,o;
    TBint a;
    std::string f = "123456789", s = "98765432";
    i << f << ' ' << s;
    i >> a;
    o << a << ' ';
    i >> a;
    o << a;
    ASSERT_EQ(o.str(), f + ' ' + s );
}

TEST(gtlt, all){
    TBint a ( "55555555555555" );
    EXPECT_GT(a, 100);
    EXPECT_LT(100, a);
    TBint b ( "44444444444444" );
    EXPECT_GT(a, b);
    EXPECT_LT(b, a);
}

TEST(multiply, all){
    TBint a ( "55555555555555" );
    ASSERT_EQ(a * 0, 0 * a);
    ASSERT_EQ(a * 1, 1 * a);
    ASSERT_EQ(a * 1, a);
    EXPECT_EQ(a * 5, static_cast<TBint>("277777777777775"));
    EXPECT_EQ(a * a, static_cast<TBint>("3086419753086358024691358025"));
    a *= a;
    EXPECT_EQ(a, static_cast<TBint>("3086419753086358024691358025"));
}

TEST(div, all){
    TBint a ( "55555555555555" );
#ifdef EXCEPTION_OPT
    EXPECT_THROW( a / 0, std::exception );
#endif
    EXPECT_EQ( 0, 0 / a);
    EXPECT_EQ( 0, 1 / a);
    EXPECT_EQ( a, a / 1);
    EXPECT_EQ(a / 5, static_cast<TBint>("11111111111111"));
    TBint b = 121;
    EXPECT_EQ(b / 11, 11);
 }




TEST(pow, all){
    TBint a ( "55555555555555" );
    ASSERT_EQ(pow(a, 0), 1);
    ASSERT_EQ(pow(0, a), 0);
    ASSERT_EQ(pow(0, 0), 1);
    ASSERT_EQ(pow(1, a), 1);
    ASSERT_EQ(pow(a, 1), a);
    EXPECT_EQ(pow(a, 5), static_cast<TBint>("529221494013419998645192975854798557130513429524632085243822926721875"));
    TBint b = 55;
    EXPECT_EQ(pow(b, b), static_cast<TBint>("524744532468751923546122657597368049278513737089035272057324643668607677682302892208099365234375"));
}



TEST(zerroes, emty){
    TBint a;
    TBint z = 0;
    ASSERT_EQ(z, a);
    ASSERT_EQ(0, a);
    a = static_cast<TBint> ("0");
    ASSERT_EQ(0, a);
    a = static_cast<TBint> ("");
    ASSERT_EQ(0, a);
    a = 0;
    ASSERT_EQ(0, a);
}

TEST(deconstructs, simple){
    TBint a;
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


