#define NDEBUG

#include "headers/print_ip.h"
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>


TEST(Test_integral_value, SNINAE) {

    std::ostringstream local;
    auto cout_buff = std::cout.rdbuf();
    std::cout.rdbuf(local.rdbuf());

    generator_ip(char(-1));
    generator_ip(short(0));
    generator_ip(2130706433);
    generator_ip(8875824491850138409L);

    std::cout.rdbuf(cout_buff);

    ASSERT_EQ(local.str(), "255\n0.0\n127.0.0.1\n123.45.67.89.101.112.131.41\n");

}

TEST(Test_string_value, SNINAE) {

    std::ostringstream local;
    auto cout_buff = std::cout.rdbuf();
    std::cout.rdbuf(local.rdbuf());

    generator_ip(std::string("qwerty.123,098?567"));

    std::cout.rdbuf(cout_buff);

    ASSERT_EQ(local.str(), "qwerty.123,098?567\n");

}

TEST(Test_containers_value, SNINAE) {

    std::ostringstream local;
    auto cout_buff = std::cout.rdbuf();
    std::cout.rdbuf(local.rdbuf());
    std::vector vec{127, 1, 3, 11};
    std::list lst{127, 1, 3, 255, 11};

    generator_ip(vec);
    generator_ip(lst);

    std::cout.rdbuf(cout_buff);

    ASSERT_EQ(local.str(), "127.1.3.11\n127.1.3.255.11\n");

}

TEST(Test_tuple_value, SNINAE) {

    std::ostringstream local;
    auto cout_buff = std::cout.rdbuf();
    std::cout.rdbuf(local.rdbuf());
    auto tpl = std::make_tuple(12, 13, 14, 15);

    generator_ip(tpl);

    std::cout.rdbuf(cout_buff);

    ASSERT_EQ(local.str(), "12.13.14.15\n");

}

int main(int argc, char** argv) {

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}

