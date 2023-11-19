#pragma once

#include "StringSearchAlgorithm.h"

class SimpleSearch : public StringSearchAlgorithm 
{
public:
    std::string getName() override { return "Simple Search"; }

	int search(const uint8_t* text, size_t text_len, const uint8_t* keyword, size_t keyword_len) override
	{
        int count = 0;
        for (int i = 0; i < text_len; i++) {
            bool found = true;
            for (int j = 0; j < keyword_len; j++) {
                if (text[i + j] != keyword[j]) {
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