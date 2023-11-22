#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>
#include <chrono>

//#define KEYWORD "the"
//#define KEYWORD "Alice was beginning to get"
#define KEYWORD "Alice was beginning to get very tired of sitting by her sister"

//#define TEXT_FILE "HuckleberryFinn.txt"
//#define TEXT_FILE "InSearchOfLostTime.txt"
#define TEXT_FILE "ExtraLargeText.txt"

#define SAMPLES 50

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
    std::cout << "Algorithm: " << algorithm->getName() << std::endl;
    int count;

    //Test the algorith for every length of the keyword
    for (int i = 1; i <= keyword.length(); i++) {
        std::string pattern = keyword.substr(0, i);

        double totalMS = 0.0;
        for (int i = 0; i < SAMPLES; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            count = algorithm->search(text, length, (const uint8_t*)pattern.c_str(), pattern.length());
            auto diff = std::chrono::high_resolution_clock::now() - start;

            double ms = std::chrono::duration<double, std::milli>(diff).count();
            totalMS += ms;
            
        }

        std::cout << (totalMS / SAMPLES) << std::endl; // Dont print anything else so it's easier to copy into excel
    }



    std::cout << "Found \'" << keyword << "\' " << count << " times." << std::endl;
    std::cout << std::endl;

    delete algorithm;
}

int main()
{
    std::string keyword = KEYWORD;
    char* file;
    size_t length;
    if ((file = OpenFile(length)) == nullptr) {
        std::cout << "Unable to open file." << std::endl;
        return 0;
    }

    //length /= 10;
    //length *= 1;
    std::cout << "Length: " << length << std::endl;

    Benchmark(file, length, keyword, new SimpleSearch());
    Benchmark(file, length, keyword, new BoyerMooreSearch());
    delete[] file;

    return 0;
}
