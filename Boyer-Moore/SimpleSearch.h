#pragma once

#include "StringSearchAlgorithm.h"

class SimpleSearch : public StringSearchAlgorithm 
{
public:
    std::string getName() override { return "Simple Search"; }

	int search(const uint8_t* text, size_t text_len, const uint8_t* keyword, size_t keyword_len) override
	{
        int count = 0;
        for (size_t i = 0; i < text_len; i++) {
            bool found = true;
            if (text[i] == 205) {
                found = true;
            }
            for (size_t j = 0; j < keyword_len; j++) {
                uint8_t text1 = text[i + j];
                uint8_t k1 = keyword[j];
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