#ifndef PARSESEPERATEDVALUES_H
#define PARSESEPERATEDVALUES_H

#include <regex>
#include <string>
#include <vector>

using namespace std;

std::vector<std::string> parseToString(std::string row, std::string delimitor) {
    std::vector<std::string> data;

    std::string expression = "\\s*([^\\s" + delimitor + "]+)";
    std::regex e(expression);
    std::smatch string_matches;
    while (std::regex_search(row, string_matches, e)) {
        data.emplace_back(string_matches[1]);
        row = string_matches.suffix().str();
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
