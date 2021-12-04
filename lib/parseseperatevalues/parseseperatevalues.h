#ifndef PARSESEPERATEDVALUES_H
#define PARSESEPERATEDVALUES_H

#include <string>
#include <vector>

using namespace std;

std::vector<std::string> parseToString(std::string row, std::string delimitor) {
    std::vector<std::string> data;

    while(true){
        std::size_t firstDelimitorPosition = row.find_first_of(delimitor);
        if(firstDelimitorPosition != std::string::npos){
            data.emplace_back(row.substr(0, firstDelimitorPosition));
            row = row.substr(firstDelimitorPosition + 1);
        }else{
            data.emplace_back(row);
            break;
        }
    }
    return data;
}

std::vector<int> parseToIntegers(std::string row, std::string delimitor) {
    std::vector<std::string> input = parseToString(row, delimitor);
    std::vector<int> data;
    for (std::string line : input) {
        data.emplace_back(stoi(line));
    }

  return data;
}

#endif  // PARSESEPERATEDVALUES_H
