#include <cassert>
#include <iostream>
#include <numeric>
#include <regex>
#define assertm(exp, msg) assert(((void)msg, exp))

#include "lib/fileinput/fileinput.h"

struct line {
    unsigned int startX;
    unsigned int startY;
    unsigned int endX;
    unsigned int endY;
};

std::vector<line> vectorOfLinesFromStrings(std::vector<std::string> input) {
    std::vector<line> out;

    std::string expression = "(\\d+),(\\d+)\\s*->\\s*(\\d+),(\\d+)\\s*";
    std::regex e(expression);
    std::smatch string_matches;

    for (std::string sLine : input) {
        assertm(std::regex_match(sLine, string_matches, e), "input didn't match pattern");
        line l;
        l.startY = stoi(string_matches[1]);
        l.startX = stoi(string_matches[2]);
        l.endY = stoi(string_matches[3]);
        l.endX = stoi(string_matches[4]);
        out.emplace_back(l);
    }

    return out;
}

std::vector<std::vector<int>> createMap(unsigned int maxX, unsigned int maxY) {
    std::vector<std::vector<int>> map;
    for (size_t i = 0; i <= maxX; i++) {
        std::vector<int> row;
        for (size_t i = 0; i <= maxY; i++) {
            row.emplace_back(0);
        }
        map.emplace_back(row);
    }
    return map;
}

void drawLineOnMap(line l, std::vector<std::vector<int>> &map) {
    auto sign = [](int in) {
        if (in > 0) {
            return 1;
        } else if (in < 0) {
            return -1;
        }
        return 0;
    };
    int directionX = sign(l.endX - l.startX);
    int directionY = sign(l.endY - l.startY);

    unsigned int cordX = l.startX;
    unsigned int cordY = l.startY;

    map.at(cordX).at(cordY)++;
    while (cordX != l.endX || cordY != l.endY) {
        cordX += directionX;
        cordY += directionY;
        map.at(cordX).at(cordY)++;
    }
}

void printMap(std::vector<std::vector<int>> &map) {
    for (auto row : map) {
        for (int place : row) {
            if (place == 0) {
                std::cout << "- ";
            } else {
                std::cout << place << " ";
            }
        }
        std::cout << std::endl;
    }
}

int main(int argc, char *argv[]) {
    std::string fileName = findFileLocation(argc, argv, "input.txt");
    std::vector<std::string> input_data = readFileStrings(fileName);

    std::vector<line> data = vectorOfLinesFromStrings(input_data);
    unsigned int maxX = 0;
    unsigned int maxY = 0;
    for (line l : data) {
        maxX = std::max(std::max(maxX, l.startX), l.endX);
        maxY = std::max(std::max(maxX, l.startY), l.endY);
    }

    // Part 1
    {
        std::cout << "Part 1:" << std::endl;
        std::vector<std::vector<int>> map = createMap(maxX, maxY);
        for (line l : data) {
            if (l.startX == l.endX || l.startY == l.endY) {
                drawLineOnMap(l, map);
            }
        }
        // printMap(map);
        unsigned int above1 = 0;
        for (auto row : map) {
            for (int place : row) {
                if (place > 1) {
                    above1++;
                }
            }
        }

        std::cout << "Part 1 answer: " << above1 << std::endl;
    }

    // Part 2
    {
        std::cout << "Part 2:" << std::endl;
        std::vector<std::vector<int>> map = createMap(maxX, maxY);
        for (line l : data) {
            drawLineOnMap(l, map);
        }
        // printMap(map);
        unsigned int above1 = 0;
        for (auto row : map) {
            for (int place : row) {
                if (place > 1) {
                    above1++;
                }
            }
        }

        std::cout << "Part 2 answer: " << above1 << std::endl;
    }
    return 0;
}