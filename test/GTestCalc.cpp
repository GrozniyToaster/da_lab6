//
// Created by ivan- on 05.03.2021.
//
#include <gtest/gtest.h>
#include "../big_integer.hpp"
TEST(sum, simple_string_construct){
    NBigInt::bint_t a = static_cast<NBigInt::bint_t>("100000");
    NBigInt::bint_t b = static_cast<NBigInt::bint_t>("500");
    NBigInt::bint_t res = static_cast<NBigInt::bint_t>("100500");
    NBigInt::bint_t kek = a+b;
    ASSERT_EQ(res, kek);
}

TEST(sum, simple_int_construct){
    NBigInt::bint_t a = 100000;
    NBigInt::bint_t b = 500;
    NBigInt::bint_t res = 100500;
    NBigInt::bint_t kek = a+b;
    ASSERT_EQ(res, kek);
}

TEST(eq, simple) {
    NBigInt::bint_t a = 100000;
    NBigInt::bint_t b = static_cast<NBigInt::bint_t>("100000");
    ASSERT_EQ(a, b);
}

TEST(ne, simple) {
    NBigInt::bint_t a = 1000001;
    NBigInt::bint_t b = static_cast<NBigInt::bint_t>("100000");
    ASSERT_NE(a, b);
}

TEST(zerroes, emty){
    NBigInt::bint_t a;
    NBigInt::bint_t z = 0;

    ASSERT_EQ(z, a);
    ASSERT_EQ(0, a);
    a = static_cast<NBigInt::bint_t> ("0");
    ASSERT_EQ(0, a);
    a = 0;
    ASSERT_EQ(0, a);
}

TEST(deconstructs, simple){
    NBigInt::bint_t a;
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


