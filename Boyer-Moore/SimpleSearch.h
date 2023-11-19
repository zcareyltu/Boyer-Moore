#pragma once

#include "StringSearchAlgorithm.h"

class SimpleSearch : public StringSearchAlgorithm 
{
public:
    std::string getName() override { return "Simple Search"; }

	int search(const std::string& file, const std::string& keyword) override
	{
        int count = 0;
        for (int i = 0; i < file.size(); i++) {
            bool found = true;
            for (int j = 0; j < keyword.size(); j++) {
                if (file[i + j] != keyword[j]) {
                    found = false;
                    break;
                }
            }
            if (found) {
                count++;
            }
        }

        return count;
	}
};