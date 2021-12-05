#include <gtest/gtest.h>

#include <fstream>
#include <iostream>

#include "days/d4/BingoBoard.h"

TEST(BingoBoard_Test, checkConstruct) {
    std::vector<std::vector<int>> input = {{1, 2}, {3, 4}};
    BingoBoard b(input);

    EXPECT_EQ(b.score(), 1 + 2 + 3 + 4);  // unchecked numbers in board
}

TEST(BingoBoard_Test, checkWinColumn) {
    std::vector<std::vector<int>> input = {{1, 2}, {3, 4}};
    BingoBoard b(input);

    EXPECT_EQ(b.score(), 1 + 2 + 3 + 4);  // unchecked numbers in board
    EXPECT_FALSE(b.hasWon());
    b.checkNumber(1);
    EXPECT_FALSE(b.hasWon());
    b.checkNumber(3);
    EXPECT_TRUE(b.hasWon());
    EXPECT_EQ(b.score(), 2 + 4);  // unchecked numbers in board
}

TEST(BingoBoard_Test, checkWinRow) {
    std::vector<std::vector<int>> input = {{1, 2}, {3, 4}};
    BingoBoard b(input);

    EXPECT_EQ(b.score(), 1 + 2 + 3 + 4);  // unchecked numbers in board
    EXPECT_FALSE(b.hasWon());
    b.checkNumber(1);
    EXPECT_FALSE(b.hasWon());
    b.checkNumber(2);
    EXPECT_TRUE(b.hasWon());
    EXPECT_EQ(b.score(), 3 + 4);  // unchecked numbers in board
}