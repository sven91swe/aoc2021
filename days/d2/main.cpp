#include <iostream>
#include <numeric>

#include "lib/fileinput/fileinput.h"

enum class Direction { up, down, forward, invalid };

Direction directionFromString(std::string s) {
    if (s == "forward") {
        return Direction::forward;
    } else if (s == "down") {
        return Direction::down;
    } else if (s == "up") {
        return Direction::up;
    } else {
        return Direction::invalid;
    }
}

int main(int argc, char *argv[]) {
    std::string fileName = findFileLocation(argc, argv, "input.txt");
    std::vector<std::string> data = readFileStrings(fileName);

    // Part 1
    {
        std::cout << "Part 1:" << std::endl;

        int depth = 0;
        int horizontal = 0;

        for (std::string s : data) {
            std::size_t pos = s.find(" ");
            std::string key = s.substr(0, pos);
            int value = stoi(s.substr(pos + 1));

            switch (directionFromString(key)) {
                case Direction::forward:
                    horizontal += value;
                    break;
                case Direction::down:
                    depth += value;
                    break;
                case Direction::up:
                    depth -= value;
                    break;
                case Direction::invalid:
                default:
                    break;
            }
        }

        std::cout << "Part 1 answer: "
                  << "D: " << depth << " - H: " << horizontal << " - result: " << depth * horizontal
                  << std::endl;
    }

    // Part 2
    {
        std::cout << "Part 2:" << std::endl;

        int depth = 0;
        int horizontal = 0;
        int aim = 0;

        for (std::string s : data) {
            std::size_t pos = s.find(" ");
            std::string key = s.substr(0, pos);
            int value = stoi(s.substr(pos + 1));

            switch (directionFromString(key)) {
                case Direction::forward:
                    horizontal += value;
                    depth += aim * value;
                    break;
                case Direction::down:
                    aim += value;
                    break;
                case Direction::up:
                    aim -= value;
                    break;
                case Direction::invalid:
                default:
                    break;
            }
        }

        std::cout << "Part 2 answer: "
                  << "D: " << depth << " - H: " << horizontal << " - result: " << depth * horizontal
                  << std::endl;
    }
    return 0;
}