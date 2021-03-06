#include <iostream>
#include <numeric>

#include "days/d4/BingoBoard.h"
#include "lib/fileinput/fileinput.h"
#include "lib/parseseperatevalues/parseseperatevalues.h"

std::vector<BingoBoard> createBoards(std::vector<std::string> input);
BingoBoard createBoard(std::vector<std::string> input);

int main(int argc, char *argv[]) {
    std::string fileName = findFileLocation(argc, argv, "input.txt");
    std::vector<std::string> data = readFileStrings(fileName);

    std::vector<int> calledNumbers;
    int numberOfStartLines = 0;
    for (auto line : data) {
        numberOfStartLines++;
        if (line == "") {
            break;
        }
        std::vector<int> lineInt = parseToIntegers(line, ",");
        for (int i : lineInt) {
            calledNumbers.emplace_back(i);
        }
    }

    // Part 1
    {
        std::cout << "Part 1:" << std::endl;
        std::vector<BingoBoard> boards =
            createBoards(std::vector<std::string>(data.begin() + numberOfStartLines, data.end()));

        int currentCalledNumber;
        for (int calledNumber : calledNumbers) {
            bool anyIsDone = false;
            currentCalledNumber = calledNumber;
            for (BingoBoard &b : boards) {
                b.checkNumber(calledNumber);
                anyIsDone |= b.hasWon();
            }
            if (anyIsDone) {
                break;
            }
        }

        unsigned int boardScore = 0;
        for (BingoBoard &b : boards) {
            if (b.hasWon()) {
                boardScore = std::max(boardScore, b.score());
            }
        }
        std::cout << "Part 1 answer: " << boardScore * currentCalledNumber << std::endl;
    }

    // Part 1
    {
        std::cout << "Part 2:" << std::endl;
        std::vector<BingoBoard> boards =
            createBoards(std::vector<std::string>(data.begin() + numberOfStartLines, data.end()));

        unsigned int latestWin = 0;
        unsigned int scoreAtLatestWin = 0;

        for (BingoBoard &b : boards) {
            for (size_t i = 0; i < calledNumbers.size(); i++) {
                int currentCalledNumber = calledNumbers.at(i);

                b.checkNumber(currentCalledNumber);
                if (b.hasWon()) {
                    if (i > latestWin) {
                        latestWin = i;
                        scoreAtLatestWin = b.score() * currentCalledNumber;
                    }
                    break;
                }
            }
        }

        std::cout << "Part 2 answer: " << scoreAtLatestWin << std::endl;
    }
    return 0;
}

std::vector<BingoBoard> createBoards(std::vector<std::string> input) {
    std::vector<BingoBoard> out;

    std::size_t startIndex = 0;
    std::size_t bingoSize = 5;
    while (startIndex < input.size()) {
        out.emplace_back(createBoard(std::vector<std::string>(
            input.begin() + startIndex, input.begin() + startIndex + bingoSize)));

        startIndex += bingoSize + 1;
    }
    return out;
}

BingoBoard createBoard(std::vector<std::string> input) {
    std::vector<std::vector<int>> input_int;
    for (auto line : input) {
        input_int.emplace_back(parseToIntegers(line, " "));
    }
    BingoBoard b(input_int);
    return b;
}