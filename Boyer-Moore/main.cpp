#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>
#include <chrono>

#define KEYWORD "the"
//#define TEXT_FILE "HuckleberryFinn.txt"
#define TEXT_FILE "InSearchOfLostTime.txt"

#include "StringSearchAlgorithm.h"
#include "SimpleSearch.h"
#include "BoyerMooreSearch.h"

bool OpenFile(std::string& textResult) {
    std::ifstream file(TEXT_FILE);
    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    textResult = std::string(size, 0);
    file.seekg(0);
    file.read(&textResult[0], size);
    return true;
}

void Benchmark(const std::string& file, const std::string& keyword, StringSearchAlgorithm* algorithm) {
    auto start = std::chrono::steady_clock::now();
    int count = algorithm->search(file, keyword);
    auto diff = std::chrono::steady_clock::now() - start;
    
    std::cout << "Algorithm: " << algorithm->getName() << std::endl;
    std::cout << "Found \'" << keyword << "\' " << count << " times." << std::endl;
    std::cout << "Execution time: " << std::chrono::duration<double, std::milli>(diff).count() << " ms" << std::endl;
    std::cout << std::endl;

    delete algorithm;
}

int main()
{
    std::string keyword = KEYWORD;
    //FileIterator file(TEXT_FILE);
    std::string file;
    if (!OpenFile(file)) {
        std::cout << "Unable to open file." << std::endl;
        return 0;
    }

    Benchmark(file, keyword, new SimpleSearch());
    Benchmark(file, keyword, new BoyerMooreSearch());

    return 0;
}
