#pragma once
#include<memory>
#include "MatchMethod.h"

class MatchString {
private:
    std::unique_ptr<MatchMethod> method;
public:
    explicit MatchString(std::unique_ptr<MatchMethod> m) :method(std::move(m)) {}
    void setMethod(std::unique_ptr<MatchMethod> m) {
        method = std::move(m);
    }
    std::string getMethodName() const {
        return method->name();
    }
    int match(const std::string& str, const std::string& pattern) const {
        return method->match(str, pattern);
    }
};