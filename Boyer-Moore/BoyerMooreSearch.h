#pragma once

#include "StringSearchAlgorithm.h"

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>

#define ALPHABET_LEN 256 // Using char for file which has 256 unique values

class BoyerMooreSearch : public StringSearchAlgorithm
{
public:
    std::string getName() override { return "Boyer-Moore"; }

    int search(const uint8_t* text, size_t text_len, const uint8_t* keyword, size_t keyword_len) override
    {
        int count = 0;
        ptrdiff_t delta1[ALPHABET_LEN];
        ptrdiff_t* delta2 = new ptrdiff_t[keyword_len]; 
        make_delta1(delta1, keyword, keyword_len);
        make_delta2(delta2, keyword, keyword_len);

        // The empty pattern must be considered specially
        if (keyword_len == 0) {
            return 0;
        }

        size_t i = keyword_len - 1; // string index
        while (i < text_len) {
            ptrdiff_t j = keyword_len - 1; // pattern index
            while (j >= 0 && (text[i] == keyword[j])) {
                --i;
                --j;
            }
            if (j < 0) {
                // Found a match! 
                // move past the string to find the next match
                count++;
                i += keyword_len + 1;
                continue;
            }

            ptrdiff_t shift = std::max(delta1[text[i]], delta2[j]);
            i += shift;
        }

        delete[] delta2;
        return count;
    }

private:
    // Bad-character rule
    void make_delta1(ptrdiff_t* delta1, const uint8_t* pat, size_t patlen) {
        for (int i = 0; i < ALPHABET_LEN; i++) {
            delta1[i] = patlen;
        }
        for (int i = 0; i < patlen; i++) {
            delta1[pat[i]] = patlen - 1 - i;
        }
    }

    // Good-suffix rule
    void make_delta2(ptrdiff_t* delta2, const uint8_t* pat, size_t patlen) {
        long long p;
        size_t last_prefix_index = 1;

        // first loop
        for (p = patlen - 1; p >= 0; p--) {
            if (is_prefix(pat, patlen, p + 1)) {
                last_prefix_index = p + 1;
            }
            delta2[p] = last_prefix_index + (patlen - 1 - p);
        }

        // second loop
        for (p = 0; p < patlen - 1; p++) {
            size_t slen = suffix_length(pat, patlen, p);
            if (pat[p - slen] != pat[patlen - 1 - slen]) {
                delta2[patlen - 1 - slen] = patlen - 1 - p + slen;
            }
        }
    }


    bool is_prefix(const uint8_t* word, size_t wordlen, ptrdiff_t pos) {
        int suffixlen = wordlen - pos;
        for (int i = 0; i < suffixlen; i++) {
            if (word[i] != word[pos + i]) {
                return false;
            }
        }
        return true;
    }

    size_t suffix_length(const uint8_t* word, size_t wordlen, ptrdiff_t pos) {
        size_t len = 0;
        // increment suffix length i to the first mismatch or beginning
        // of the word
        for (size_t i = pos, j = wordlen - 1; (i >= 0) && (word[i] == word[j]); --i, --j) {
            len += 1;
        }
        return len;
    }

};
