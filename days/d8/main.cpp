#include <cassert>
#include <iostream>
#include <numeric>
#include <regex>
#define assertm(exp, msg) assert(((void)msg, exp))

#include "lib/fileinput/fileinput.h"
#include "lib/parseseperatevalues/parseseperatevalues.h"

struct sequence{
    std::vector<std::string> before;
    std::vector<std::string> after;
};

sequence parseLine(std::string in){
    sequence out;
    std::regex e(R"(([a-g]+) ([a-g]+) ([a-g]+) ([a-g]+) ([a-g]+) ([a-g]+) ([a-g]+) ([a-g]+) ([a-g]+) ([a-g]+) \| ([a-g]+) ([a-g]+) ([a-g]+) ([a-g]+))");
    std::smatch string_matches;

    assertm(std::regex_match(in, string_matches, e), "input didn't match pattern");
    for(int i=1; i<=10; i++){
        out.before.emplace_back(string_matches[i]);
    }
    for(int i=11; i<=14; i++){
        out.after.emplace_back(string_matches[i]);
    }

    return out;
}

int main(int argc, char *argv[]) {
    std::string fileName = findFileLocation(argc, argv, "input.txt");
    std::vector<std::string> input_data = readFileStrings(fileName);

    std::vector<sequence> data;
    for(std::string row : input_data){
        data.emplace_back(parseLine(row));
    }


    // Part 1
    {
        std::cout << "Part 1:" << std::endl;

        int numberOf1478 = 0;

        for(sequence s : data){
            for(std::string n : s.after){
                size_t size = n.size();
                if(size == 2 || 
                size == 3 || 
                size == 4 || 
                size == 7){
                    numberOf1478++;
                }
            }
        }


        std::cout << "Part 1 answer: " << numberOf1478 << std::endl;
    }

    // Part 2
    {
        std::cout << "Part 2:" << std::endl;

        std::cout << "Part 2 answer: " << std::endl;
    }
    return 0;
}