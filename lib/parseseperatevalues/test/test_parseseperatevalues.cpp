#include <gtest/gtest.h>

#include "lib/parseseperatevalues/parseseperatevalues.h"

TEST(ParseSeperateValue_Test, ParseToStrings) {
    std::vector<std::string> input;
    input.emplace_back("ABC");
    input.emplace_back("DEF");
    input.emplace_back("123");
    input.emplace_back("456");

    std::string singleline = input.at(0);
    for (std::size_t i = 1; i < input.size(); i++) {
        singleline += "," + input.at(i);
    }

    std::vector<std::string> output = parseToString(singleline, ",");

    // Actual test
    EXPECT_EQ(input.size(), output.size());
    for (std::size_t i = 0; i < input.size(); i++) {
        EXPECT_EQ(input.at(i), output.at(i));
    }
}

TEST(ParseSeperateValue_Test, ParseToIntegers) {
    std::string input = " 1 4 6 8 ";

    std::vector<int> output = parseToIntegers(input, " ");

    // Actual test
    EXPECT_EQ(output.size(), 4);

    EXPECT_EQ(output.at(0), 1);
    EXPECT_EQ(output.at(1), 4);
    EXPECT_EQ(output.at(2), 6);
    EXPECT_EQ(output.at(3), 8);
}