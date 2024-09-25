#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cstdint>
#include <chrono>
#include <algorithm>
#include <bitset>


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

uint64_t hashGenerate(std::string inputString) {
    uint64_t hash = 98317;
    uint64_t salt = 1099511628211ULL;

    for(char c : inputString) {
        hash = (hash ^ (salt * c)) + ((hash << 5) + c);
    }

    std::stringstream hexHash;

    hash = (hash << 15 | hash >> 49);

    return hash & 0xFFFFFFFFFFFFFFFFULL;
}

std::string random_string( size_t length )
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}

unsigned int collisionTest(){
    unsigned int collisionCounter = 0;
    std::ifstream DF("test_4.txt");
    std::string line;
    std::stringstream buffer;
    std::string pair1, pair2;

    while(std::getline(DF, line)) {
        buffer << line;
        buffer >> pair1 >> pair2;

        if(hexHashGenerate(pair1) == hexHashGenerate(pair2)) {
            collisionCounter++;
            std::cout << "Collision: " << pair1 << " " << pair2 << std::endl;
        }

        buffer.str("");
        buffer.clear();
    }

    return collisionCounter;
}

void avalancheTest(){
    std::ifstream DF("test_5.txt");
    std::string line;
    std::stringstream buffer;
    std::string pair1, pair2;

    unsigned int bitLowCount = 0;
    unsigned int bitMedCount = 0;
    unsigned int bitHighCount = 0;

    unsigned int hexLowCount = 0;
    unsigned int hexMedCount = 0;
    unsigned int hexHighCount = 0;

    while(std::getline(DF, line)) {
        buffer << line;
        buffer >> pair1 >> pair2;

        uint64_t pair1Hash = hashGenerate(pair1);
        uint64_t pair2Hash = hashGenerate(pair2);

        unsigned int bitDifference = std::bitset<64>(pair1Hash ^ pair2Hash).count();

        double bitPercentageDif = (double(bitDifference) * 100 / 64);

        if(bitPercentageDif <= 33) {
            bitLowCount++;
        } else if(bitPercentageDif <= 66) {
            bitMedCount++;
        } else {
            bitHighCount++;
        }

        buffer.str("");
        buffer.clear();
        buffer << std::hex << (pair1Hash & 0xFFFFFFFFFFFFFFFFULL);
        pair1 = buffer.str();

        buffer.str("");
        buffer.clear();
        buffer << std::hex << (pair2Hash & 0xFFFFFFFFFFFFFFFFULL);
        pair2 = buffer.str();

        unsigned int hexDifference = 0;

        for(int i = 0; i < 16; i++) {
            if(pair1[i] != pair2[i]) {
                hexDifference++;
            }
        }

        double hexPercentageDif = (double(hexDifference) * 100 / 16);

        if(hexPercentageDif <= 33) {
            hexLowCount++;
        } else if(hexPercentageDif <= 66) {
            hexMedCount++;
        } else {
            hexHighCount++;
        }

        buffer.str("");
        buffer.clear();
    }

    std::cout << "Bit comparison results: " << std::endl <<
                "High Difference (>66%): " << bitHighCount << std::endl <<
                "Medium Difference (<=66%): " << bitMedCount << std::endl <<
                "Low Difference (<=33%): " << bitLowCount << std::endl << std::endl << 
                "Hex comparison results: " << std::endl << 
                "High Difference (>66%): " << hexHighCount << std::endl <<
                "Medium Difference (<=66%): " << hexMedCount << std::endl <<
                "Low Difference (<=33%): " << hexLowCount << std::endl;
}

void generateTestingFile4() {
    std::ofstream TF("test_4.txt");

    std::stringstream buffer;

    for(int i = 0; i < 25000; i++) {
        buffer << random_string(10) << " " << random_string(10) << "\n";
    }
    TF << buffer.str();
    buffer.str("");
    buffer.clear();

    for(int i = 0; i < 25000; i++) {
        buffer << random_string(100) << " " << random_string(100) << "\n";
    }
    TF << buffer.str();
    buffer.str("");
    buffer.clear();

    for(int i = 0; i < 25000; i++) {
        buffer << random_string(500) << " " << random_string(500) << "\n";
    }
    TF << buffer.str();
    buffer.str("");
    buffer.clear();

    for(int i = 0; i < 25000; i++) {
        buffer << random_string(1000) << " " << random_string(1000) << "\n";
    }
    TF << buffer.str();
    buffer.str("");
    buffer.clear();

    TF.close();
}

void generateTestingFile5() {
    std::ofstream TF("test_5.txt");
    std::string rString1, rString2;

    std::stringstream buffer;

    for(int i = 0; i < 25000; i++) {
        rString1 = random_string(10);
        rString2 = rString1;
        do {
            rString2[0] = random_string(1)[0];
        } while (rString1 == rString2);
        
        buffer << rString1 << " " << rString2 << "\n";
    }
    TF << buffer.str();
    buffer.str("");
    buffer.clear();

    for(int i = 0; i < 25000; i++) {
        rString1 = random_string(100);
        rString2 = rString1;
        do {
            rString2[0] = random_string(1)[0];
        } while (rString1 == rString2);
        
        buffer << rString1 << " " << rString2 << "\n";
    }
    TF << buffer.str();
    buffer.str("");
    buffer.clear();

    for(int i = 0; i < 25000; i++) {
        rString1 = random_string(500);
        rString2 = rString1;
        do {
            rString2[0] = random_string(1)[0];
        } while (rString1 == rString2);
        
        buffer << rString1 << " " << rString2 << "\n";
    }
    TF << buffer.str();
    buffer.str("");
    buffer.clear();

    for(int i = 0; i < 25000; i++) {
        rString1 = random_string(1000);
        rString2 = rString1;
        do {
            rString2[0] = random_string(1)[0];
        } while (rString1 == rString2);
        
        buffer << rString1 << " " << rString2 << "\n";
    }
    TF << buffer.str();
    buffer.str("");
    buffer.clear();

    TF.close();
}



int main() {
    std::cout << "Menu:" << std::endl <<
            "(1) for file input" << std::endl <<
            "(2) for console input" << std::endl <<
            "(3) for testing file 4 generation" << std::endl << 
            "(4) for testing file 5 generation" << std::endl << 
            "(5) for collision testing" << std::endl << 
            "(6) for avalanche testing" << std::endl << 
            "(0) for exit" << std::endl;
    
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

    auto startTime = std::chrono::high_resolution_clock::now();

    std::cout << "hash output: " << hexHashGenerate(inputString) << std::endl;

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    std::cout << "hashing process took: " << duration.count() << " microseconds" << std::endl;
    } else if(userInput == "2") {
        std::cout << "Provide input string to be hashed: " << std::endl;
        std::cin >> userInput;

        std::cout << "hash output: " << hexHashGenerate(userInput) << std::endl;
    } else if(userInput == "3") {
        generateTestingFile4();
    } else if(userInput == "4") {
        generateTestingFile5();
    } else if(userInput == "5") {
        std::cout << "Amount of collisions: " << collisionTest() << std::endl;
    } else if(userInput == "6") {
        avalancheTest();
    }
    

    return 0;
}