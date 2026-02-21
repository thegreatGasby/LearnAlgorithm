#pragma once
#include <vector>
#include <iostream>
#include <chrono>
#include "MatchMethod.h"

struct TestNode {
    int ans;
    std::string str;
    std::string pattern;
    TestNode(int ans, std::string str, std::string pattern) {
        this->ans = ans;
        this->str = str;
        this->pattern = pattern;
    }
};

class TestMatchString {
private:
    std::vector<TestNode> testCases;
public:
    TestMatchString() {
        // 基础功能测试
        testCases.push_back(TestNode{ 0, "hello", "he" });        // 开头匹配一次
        testCases.push_back(TestNode{ 3, "hello", "lo" });        // 结尾匹配一次  
        testCases.push_back(TestNode{ 2, "hello", "ll" });        // 中间匹配一次
        testCases.push_back(TestNode{ 0, "hellohello", "he" });   // 两次匹配

        // 多次匹配测试
        testCases.push_back(TestNode{ 0, "abababa", "aba" });     // 重叠匹配3次
        testCases.push_back(TestNode{ 0, "aaaaa", "aa" });        // 重叠匹配4次
        testCases.push_back(TestNode{ 0, "aaaaaaaa", "aaa" });    // 重叠匹配5次

        // 边界测试
        testCases.push_back(TestNode{ -1, "", "he" });              // 空文本
        testCases.push_back(TestNode{ 0, "h", "h" });               // 单字符匹配
        testCases.push_back(TestNode{ -1, "a", "b" });               // 单字符不匹配
        testCases.push_back(TestNode{ -1, "hi", "hello" });          // 模式比文本长

        // 位置分布测试
        testCases.push_back(TestNode{ 2, "ababcabcab", "abc" });    // 位置2,5,8
        testCases.push_back(TestNode{ 0, "hello world hello", "hello" }); // 位置0,12

        // 无匹配测试
        testCases.push_back(TestNode{ -1, "hello", "xyz" });         // 完全无匹配
        testCases.push_back(TestNode{ -1, "hello", "hello world" }); // 模式比文本长

        // 特殊字符测试
        testCases.push_back(TestNode{ 5, "hello!@#", "!@#" });      // 特殊符号
        testCases.push_back(TestNode{ 0, "a b a b", "a b" });       // 带空格

        // 性能基准测试（小规模）
        testCases.push_back(TestNode{ 23, "abcdefghijklmnopqrstuvwxyz", "xyz" });    // 结尾
        testCases.push_back(TestNode{ 0, "aaaaaaaaaaaaaaaaaaaa", "aaaa" });         // 长重复串
    }

    void addSample(int ans, std::string str, std::string pattern) {
        testCases.push_back(TestNode{ ans, str, pattern });
    }

    double test(MatchString& method, int num) {
        std::cout << "Testing method: " << method.getMethodName() << std::endl;
        for (auto& testCase : testCases) {
            int result = method.match(testCase.str, testCase.pattern);
            if (result != testCase.ans) {
                std::cout << "Test failed for: " << testCase.str << " with pattern: " << testCase.pattern
                    << ". Expected: " << testCase.ans << ", Got: " << result << std::endl;
                return -1;
            }
        }
        auto start_time = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < num; ++i) {
            for (auto& testCase : testCases) {
                method.match(testCase.str, testCase.pattern);
            }
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
        double avg_time_ns = static_cast<double>(duration_ns.count()) / (num * testCases.size());
        return avg_time_ns / 1000.0;
    }
};