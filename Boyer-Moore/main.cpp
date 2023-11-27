#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>
#include <chrono>

#define KEYWORD "Alice was beginning to get very tired of sitting by her sister"

//#define TEXT_FILE "HuckleberryFinn.txt"
//#define TEXT_FILE "InSearchOfLostTime.txt"
#define TEXT_FILE "ExtraLargeText.txt"

#include "StringSearchAlgorithm.h"
#include "SimpleSearch.h"
#include "BoyerMooreSearch.h"

char* OpenFile(size_t& length) {
    std::ifstream file(TEXT_FILE, std::ios::binary | std::ios::ate);
    length = file.tellg();
    file.seekg(0, std::ios::beg);
    char* text = new char[length];
    if (!file.read(text, length)) {
        delete[] text;
        return nullptr;
    }
    return text;
}

void Benchmark(const char* file, size_t length, const std::string& keyword, StringSearchAlgorithm* algorithm) {
    const uint8_t* text = (const uint8_t*)file;
    const uint8_t* pattern = (const uint8_t*)keyword.c_str();

    auto start = std::chrono::high_resolution_clock::now();
    int count = algorithm->search(text, length, pattern, keyword.length());
    auto diff = std::chrono::high_resolution_clock::now() - start;
    
    std::cout << "Algorithm: " << algorithm->getName() << std::endl;
    std::cout << "Found the pattern " << count << " times." << std::endl;
    std::cout << "Execution time: " << std::chrono::duration<double, std::milli>(diff).count() << " ms" << std::endl;
    std::cout << std::endl;

    delete algorithm;
}

int main()
{
    char* file;
    size_t length;
    if ((file = OpenFile(length)) == nullptr) {
        std::cout << "Unable to open file." << std::endl;
        return 0;
    }

    std::string pattern;
    while (true) {
        std::cout << "Enter the pattern to search for (blank for default): ";
        //std::cin >> pattern;
        std::getline(std::cin, pattern);
        if (pattern.empty()) {
            pattern = KEYWORD;
        }
        std::cout << "Searching for pattern \'" << pattern << "\'." << std::endl << std::endl;

        Benchmark(file, length, pattern, new SimpleSearch());
        Benchmark(file, length, pattern, new BoyerMooreSearch());

        std::cout << "----------------------------------------------" << std::endl;
        std::cout << std::endl;
    }

    delete[] file;

    return 0;
}
