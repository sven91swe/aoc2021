#include <algorithm>
#include <iostream>
#include <numeric>

#include "lib/fileinput/fileinput.h"
#include "lib/parseseperatevalues/parseseperatevalues.h"

int fuelBurn(int distance) {
    int fuelBurn = 0;
    for (int i = 0; i <= distance; i++) {
        fuelBurn += i;
    }
    return fuelBurn;
}

int groupFuelBurn(std::vector<int> &crabPositions, int targetPosition) {
    long int totalFuelBurn = 0;
    for (int crabPosition : crabPositions) {
        totalFuelBurn += fuelBurn(abs(targetPosition - crabPosition));
    }
    return totalFuelBurn;
}

int main(int argc, char *argv[]) {
    std::string fileName = findFileLocation(argc, argv, "input.txt");
    std::vector<std::string> input_data = readFileStrings(fileName);

    std::string totalInput;
    for (std::string line : input_data) {
        totalInput += line;
    }
    std::vector<int> crabPositions = parseToIntegers(totalInput, ",");

    // Part 1
    {
        std::cout << "Part 1:" << std::endl;

        std::sort(crabPositions.begin(), crabPositions.end());
        int const median = crabPositions.at(crabPositions.size() / 2);
        int fuelConsumption = 0;
        for (int crabPosition : crabPositions) {
            fuelConsumption += abs(median - crabPosition);
        }

        std::cout << "Part 1 answer: " << fuelConsumption << " - best location: " << median
                  << std::endl;
    }

    // Part 2
    {
        std::cout << "Part 2:" << std::endl;

        long int totalFuelBurn = groupFuelBurn(crabPositions, 0);
        long int newTotalFuelBurn = totalFuelBurn;
        int position = 0;
        do {
            totalFuelBurn = newTotalFuelBurn;
            position++;
            newTotalFuelBurn = groupFuelBurn(crabPositions, position);
        } while (totalFuelBurn >= newTotalFuelBurn);

        std::cout << "Part 2 answer: " << totalFuelBurn << " - best location: " << position - 1
                  << std::endl;
    }
    return 0;
}