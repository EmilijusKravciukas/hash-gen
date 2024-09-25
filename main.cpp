#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>


std::string hexHashGenerate(std::string inputString){
    unsigned int hash = 98317;
    unsigned int salt = 53;

    for(char c : inputString){
        hash = (hash ^ (salt * c)) + ((hash << 3) + c);
    }

    std::stringstream hexHash;

    hexHash << std::hex << std::setw(8) << std::setfill('0') << (hash & 0xFFFFFFFF);

    return hexHash.str();
}

int main() {
    std::string inputString = "k";

    std::cout << "hash output: " << hexHashGenerate(inputString) << std::endl;

    return 0;
}