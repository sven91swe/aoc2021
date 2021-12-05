#include <iostream>
#include <numeric>

#include "lib/fileinput/fileinput.h"

int main(int argc, char *argv[]) {
    std::string fileName = findFileLocation(argc, argv, "testinput.txt");
    std::vector<std::string> data = readFileStrings(fileName);

    {
    std::cout << "Part 1:" << std::endl;
    std::vector<int> numberOfElement(data.at(0).size());
    for(std::string line : data){
        for(size_t i=0; i<line.size(); i++){
            if(line.at(i) == '1'){
                numberOfElement.at(i)++;
            }
        }
    }

    long unsigned int epsilon = 0;
    long unsigned int gamma = 0;
    for(int n : numberOfElement){
        epsilon *= 2;
        gamma *= 2;
        if(n > (int)(data.size() / 2)){
            gamma++;
        }else{
            epsilon++;
        }
    }

    std::cout << "Part 1 answer: " << epsilon * gamma << " - g: " << gamma
    << " - e:" << epsilon << std::endl;
    }
    return 0;
}