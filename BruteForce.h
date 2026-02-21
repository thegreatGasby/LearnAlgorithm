#pragma once
#include "MatchMethod.h"

class BruteForce : public MatchMethod
{
public:
    std::string name() const override { return "BruteForce"; }

    int match(const std::string& text, const std::string& pattern) const override {
        int m = pattern.size();
        int n = text.size();
        if (n < m) return -1;
        for (int i = 0; i <= n - m; ++i) {
            int j = 0;
            while (j < m && text[i + j] == pattern[j]) {
                ++j;
            }
            if (j == m) {
                return i; // Found a match at index i
            }
        }
        return -1; // No match found
    }
};