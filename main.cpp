#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cstdint>


std::string hexHashGenerate(std::string inputString) {
    uint64_t hash = 98317;
    uint64_t salt = 1099511628211ULL;

    for(char c : inputString) {
        hash = (hash ^ (salt * c)) + ((hash << 5) + c);
    }

    std::stringstream hexHash;

    hash = (hash << 15 | hash >> 49);

    hexHash << std::hex << (hash & 0xFFFFFFFFFFFFFFFFULL);

    return hexHash.str();
}

int main() {
    std::cout << "Menu:" << std::endl <<
            "(1) for file input" << std::endl <<
            "(2) for console input" << std::endl;
    
    std::string userInput;
    std::cin >> userInput;
    
    if(userInput == "1") {
        std::string inputFileName;
        unsigned int linesReadNum = 0;

        std::cout << "Enter the name of file to read from: " << std::endl;
        std::cin >> inputFileName;

        std::cout << "Enter the number of lines to read in the file, (0) stands for the whole file" << std::endl;
        std::cin >> linesReadNum;

        std::ifstream DF(inputFileName);
        std::string line;
        std::string inputString;
        unsigned int lineCounter = 0;

        if(DF.is_open()) {
            if(linesReadNum == 0) {
                while(std::getline(DF, line)) {
                    inputString += line;
                }
            } else {
                while(std::getline(DF, line) && lineCounter < linesReadNum) {
                    inputString += line;
                    lineCounter++;
                }
            }
            
        }

        DF.close();

        std::cout << "hash output: " << hexHashGenerate(inputString) << std::endl;
    } else if(userInput == "2") {
        std::cout << "Provide input string to be hashed: " << std::endl;
        std::cin >> userInput;

        std::cout << "hash output: " << hexHashGenerate(userInput) << std::endl;
    }

    return 0;
}