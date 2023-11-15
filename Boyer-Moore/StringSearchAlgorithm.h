#pragma once

#include <string>

class StringSearchAlgorithm {
public:
    virtual std::string getName() = 0;

	// Returns the number of "keywords" that exist in the "file"
	virtual int search(const std::string& file, const std::string& keyword) = 0;

    bool checkCase(char file, char keyword) {
        if (IGNORE_CASE) {
            // Ensure both chars are lowercase before comparing
            if (file >= 65 && file <= 90) {
                file += 32;
            }
            if (keyword >= 65 && keyword <= 90) {
                keyword += 32;
            }
        }

        return file == keyword;
    }
};