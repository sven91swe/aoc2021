#include <cassert>
#include <iostream>
#include <numeric>

#include "lib/fileinput/fileinput.h"
#include "lib/parseseperatevalues/parseseperatevalues.h"

std::vector<long int> createFishPopulation(std::vector<std::string> input) {
    std::string totalInput;
    for (std::string line : input) {
        totalInput += line;
    }
    std::vector<int> currentFishes = parseToIntegers(totalInput, ",");

    std::vector<long int> out(9);  // 8 days + 0

    for (int f : currentFishes) {
        out.at(f)++;
    }

    return out;
}

void updateFishPopulation(std::vector<long int> &fishPopulation) {
    std::vector<long int> temp = fishPopulation;

    for (std::size_t i = 0; i < fishPopulation.size() - 1; i++) {
        fishPopulation.at(i) = temp.at(i + 1);
    }
    fishPopulation.at(6) += temp.at(0);  // Those that gave birth gets 6 days until next birth
    fishPopulation.at(8) = temp.at(0);   // Those that were born will give birth in 8 days
}

int main(int argc, char *argv[]) {
    std::string fileName = findFileLocation(argc, argv, "input.txt");
    std::vector<std::string> input_data = readFileStrings(fileName);

    std::vector<long int> fishPopulation = createFishPopulation(input_data);

    // Part 1
    {
        std::cout << "Part 1:" << std::endl;
        int const numberOfDays = 80;
        for (int i = 0; i < numberOfDays; i++) {
            updateFishPopulation(fishPopulation);
        }

        long int fishSum = 0;
        for (long int f : fishPopulation) {
            fishSum += f;
        }

        std::cout << "Part 1 answer: " << fishSum << std::endl;
    }

    fishPopulation = createFishPopulation(input_data);

    // Part 2
    {
        std::cout << "Part 2:" << std::endl;
        int const numberOfDays = 256;
        for (int i = 0; i < numberOfDays; i++) {
            updateFishPopulation(fishPopulation);
        }

        long int fishSum = 0;
        for (long int f : fishPopulation) {
            fishSum += f;
        }

        std::cout << "Part 2 answer: " << fishSum << std::endl;
    }
    return 0;
}