#pragma once
#include <string>

class MatchMethod
{
public:
    virtual ~MatchMethod() = default;
    virtual int match(const std::string& str, const std::string& pattern) const = 0;
    virtual std::string name() const = 0;
};