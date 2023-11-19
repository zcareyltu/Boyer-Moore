#pragma once

#include <string>

class StringSearchAlgorithm {
public:
    virtual std::string getName() = 0;

	// Returns the number of "keywords" that exist in the "file"
	virtual int search(const uint8_t* text, size_t text_len, const uint8_t* keyword, size_t keyword_len) = 0;

};