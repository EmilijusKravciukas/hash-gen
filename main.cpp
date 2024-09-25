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