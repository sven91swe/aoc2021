#include <gtest/gtest.h>

#include <fstream>
#include <iostream>

#include "lib/fileinput/fileinput.h"

// Support function for the tests
void writeFile(std::string filename, std::vector<std::string> data) {
    // Set up file
    ofstream myfile(filename);
    if (myfile.is_open()) {
        for (std::string d : data) {
            myfile << d << "\n";
        }
        myfile.close();
    } else {
        cout << "Unable to open file";
    }
}

TEST(FileInput_Test, ReadStrings) {
    std::vector<std::string> write_data;
    write_data.push_back("ABC");
    write_data.push_back("DEF123");
    std::string filename = "example.txt";

    writeFile(filename, write_data);

    // Actual test
    std::vector<std::string> read_data = readFileStrings(filename);
    EXPECT_EQ(read_data.size(), write_data.size());
    EXPECT_EQ(read_data.at(0), "ABC");
    EXPECT_EQ(read_data.at(1), "DEF123");
}