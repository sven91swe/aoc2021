#include <bitset>
#include <iostream>

#include "lib/fileinput/fileinput.h"

std::bitset<16> getMostCommonBit(std::vector<std::bitset<16>> inputs, std::bitset<16> key,
                                 std::bitset<16> keyMask) {
    std::bitset<16> out;
    out.reset();

    std::bitset<16> searchHelp{0};
    std::bitset<16> zeroSet{0};
    searchHelp.set(searchHelp.size() - 1);  // Leftmost bit set to true

    while (searchHelp.to_ulong() != 0) {
        int numberOfOnes = 0;
        int numberOfZeros = 0;

        for (std::bitset<16> b : inputs) {
            if ((key & keyMask) == (b & keyMask)) {
                if ((searchHelp & b) == zeroSet) {
                    numberOfZeros++;
                } else {
                    numberOfOnes++;
                }
            }
        }

        if (numberOfOnes >= numberOfZeros) {
            out |= searchHelp;
        }
        searchHelp >>= 1;
    }

    return out;
}

std::bitset<16> createBitMask(std::string l) {
    std::bitset<16> out;
    out.reset();

    std::bitset<16> one{1};
    for (auto c : l) {
        (void)c;
        out <<= 1;
        out |= one;
    }

    return out;
}

int main(int argc, char *argv[]) {
    std::string fileName = findFileLocation(argc, argv, "input.txt");
    std::vector<std::string> input_data = readFileStrings(fileName);

    std::vector<std::bitset<16>> data;
    for (std::string line : input_data) {
        data.emplace_back(std::bitset<16>(line));
    }
    std::bitset<16> bitMask = createBitMask(input_data.at(0));
    std::cout << "Number of entries in input: " << input_data.size() << std::endl;
    std::cout << "Bitmask: " << bitMask.to_string() << std::endl;

    {
        std::cout << std::endl << "Part 1:" << std::endl;

        std::bitset<16> commonBits = getMostCommonBit(data, std::bitset<16>(0), std::bitset<16>(0));
        std::bitset<16> uncommonBits = (~commonBits & bitMask);

        std::cout << "Commonbits: " << commonBits.to_string() << std::endl;
        std::cout << "Uncommonbits: " << uncommonBits.to_string() << std::endl;

        long unsigned int gamma = (commonBits & bitMask).to_ulong();
        long unsigned int epsilon = (uncommonBits & bitMask).to_ulong();

        std::cout << "Part 1 answer: " << epsilon * gamma << " - g: " << gamma << " - e:" << epsilon
                  << std::endl;
    }

    {
        std::cout << std::endl << "Part 2:" << std::endl;

        std::bitset<16> searchMask;

        // Find best match for oxygen
        int numberOfFound = 0;
        searchMask.reset();
        std::bitset<16> oxyMatch;
        std::bitset<16> commonBits;
        while (numberOfFound != 1) {
            numberOfFound = 0;
            commonBits = (commonBits & searchMask) |
                         (getMostCommonBit(data, commonBits, searchMask) & ~(searchMask));
            commonBits &= bitMask;
            for (std::bitset<16> b : data) {
                if ((b & searchMask) == (commonBits & searchMask)) {
                    oxyMatch = b;
                    numberOfFound++;
                }
            }
            searchMask >>= 1;
            searchMask.set(searchMask.size() - 1);
        }
        std::cout << "Oxygen match: " << oxyMatch.to_string() << " - " << oxyMatch.to_ulong()
                  << std::endl;

        numberOfFound = 0;
        searchMask.reset();
        std::bitset<16> scrubberMatch;
        std::bitset<16> uncommonBits;
        while (numberOfFound != 1) {
            numberOfFound = 0;
            uncommonBits = (uncommonBits & searchMask) |
                           (~getMostCommonBit(data, uncommonBits, searchMask) & ~(searchMask));
            uncommonBits &= bitMask;
            for (std::bitset<16> b : data) {
                if ((b & searchMask) == (uncommonBits & searchMask)) {
                    scrubberMatch = b;
                    numberOfFound++;
                }
            }
            searchMask >>= 1;
            searchMask.set(searchMask.size() - 1);
        }

        std::cout << "Scrubber match: " << scrubberMatch.to_string() << " - "
                  << scrubberMatch.to_ulong() << std::endl;

        std::cout << "Part 2 answer: " << oxyMatch.to_ulong() * scrubberMatch.to_ulong()
                  << std::endl;
    }

    return 0;
}