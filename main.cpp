#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>


std::string hexHashGenerate(std::string inputString) {
    unsigned int hash = 98317;
    unsigned int salt = 53;

    for(char c : inputString) {
        hash = (hash ^ (salt * c)) + ((hash << 3) + c);
    }

    std::stringstream hexHash;

    hexHash << std::hex << std::setw(8) << std::setfill('0') << (hash & 0xFFFFFFFF);

    return hexHash.str();
}

int main() {
    std::cout << "Menu:" << std::endl <<
            "(1) for file input" << std::endl <<
            "(2) for console input" << std::endl;
    
    std::string userInput;
    std::cin >> userInput;
    
    if(userInput == "1") {
        unsigned int linesReadNum = 1;
        for(int i = 0; i < linesReadNum; i++) {
            std::ifstream DF("input.txt");
            std::string line;
            std::string inputString;
            unsigned int lineCounter = 0;

            if(DF.is_open()) {
                while(std::getline(DF, line) && lineCounter < linesReadNum) {
                    inputString += line;
                    lineCounter++;
                }
            }

            DF.close();

            std::cout << "hash output: " << hexHashGenerate(inputString) << std::endl;
        }
    } else if(userInput == "2") {
        std::cout << "Provide input string to be hashed: " << std::endl;
        std::cin >> userInput;
        std::cout << "hash output: " << hexHashGenerate(userInput) << std::endl;
    }

    return 0;
}