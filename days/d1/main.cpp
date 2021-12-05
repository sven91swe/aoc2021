#include <iostream>
#include <numeric>

#include "lib/fileinput/fileinput.h"

int main(int argc, char *argv[]) {
    std::string fileName = findFileLocation(argc, argv, "input.txt");
    std::vector<int> data = readFileIntegers(fileName);

    std::cout << "Part 1:" << std::endl;

    int lastValue = 200;
    int numberOfIncreases = 0;
    for (int i : data) {
        if (i > lastValue) {
            numberOfIncreases++;
        }
        lastValue = i;
    }

    std::cout << "Part 1 answer: " << numberOfIncreases << std::endl;

    std::cout << "Part 2:" << std::endl;
    numberOfIncreases = 0;
    for (size_t i = 3; i < data.size(); i++) {
        int lastSum = std::accumulate(data.begin() + i - 3, data.begin() + i, 0);
        int currentSum = std::accumulate(data.begin() + i - 2, data.begin() + i + 1, 0);

        if (currentSum > lastSum) {
            numberOfIncreases++;
        }
    }

    std::cout << "Part 2 answer: " << numberOfIncreases << std::endl;
    return 0;
}