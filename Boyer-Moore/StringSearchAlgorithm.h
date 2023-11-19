#pragma once

#include <string>

class StringSearchAlgorithm {
public:
    virtual std::string getName() = 0;

	// Returns the number of "keywords" that exist in the "file"
	virtual int search(const std::string& file, const std::string& keyword) = 0;

};