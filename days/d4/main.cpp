#include <iostream>
#include <numeric>

#include "lib/fileinput/fileinput.h"
#include "lib/parseseperatevalues/parseseperatevalues.h"
#include "days/d4/BingoBoard.h"

std::vector<BingoBoard> createBoards(std::vector<std::string> input);
BingoBoard createBoard(std::vector<std::string> input);

int main(int argc, char *argv[]) {
    std::string fileName = findFileLocation(argc, argv, "testinput.txt");
    std::vector<std::string> data = readFileStrings(fileName);

    std::vector<int> calledNumbers;
    int numberOfStartLines = 0;
    for(auto line : data){
        numberOfStartLines++;
        if(line == ""){
            break;
        }
        std::vector<int> lineInt = parseToIntegers(line, ",");
        for(int i : lineInt){
            calledNumbers.emplace_back(i);
        }
    }
    std::vector<BingoBoard> boards = createBoards(
        std::vector<std::string>(data.begin()+numberOfStartLines, data.end())
    );

    std::cout << "All boards:" << std::endl;
    for(auto & b : boards){
        b.printBoard();
        std::cout << std::endl;
    }

    // Part 1
    {
        std::cout << "Part 1:" << std::endl;

        int currentCalledNumber;
        for(int calledNumber : calledNumbers){
            bool anyIsDone = false;
            currentCalledNumber = calledNumber;
            for(BingoBoard & b : boards){
                b.checkNumber(calledNumber);
                anyIsDone |= b.hasWon();
            }
            if(anyIsDone){
                break;
            }
        }

        unsigned int boardScore = 0;
        for(BingoBoard & b : boards){
            if(b.hasWon()){
                boardScore = std::max(boardScore, b.score());
            }
        }
        std::cout << "Part 1 answer: " << boardScore * currentCalledNumber << std::endl;
    }

    // Part 2
    {
        std::cout << "Part 2:" << std::endl;

        std::cout << "Part 2 answer: " << std::endl;
    }
    return 0;
}

std::vector<BingoBoard> createBoards(std::vector<std::string> input){
    std::vector<BingoBoard> out;

    std::size_t startIndex = 0;
    std::size_t bingoSize = 5;
    while (startIndex < input.size())
    {
        out.emplace_back(createBoard(
            std::vector<std::string>(
                input.begin()+startIndex, input.begin()+startIndex+bingoSize)
        ));

        startIndex += bingoSize + 1;
    }
    return out;
}

BingoBoard createBoard(std::vector<std::string> input){
    std::vector<std::vector<int>> input_int;
    for(auto line : input){
        input_int.emplace_back(parseToIntegers(line, " "));
    }
    BingoBoard b(input_int);
    return b;
}