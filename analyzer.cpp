#include "analyzer.h"
#include <cassert>
#include "StringData.h"
#include <chrono>
#include <iostream>

int linearSearch(const std::vector<std::string>& data, const std::string& element)
{
    for (int i = 0; i < data.size(); i++) {
        if (data[i] == element) {
            return i;
        }
    }
    return -1;
}

int binarySearch(const std::vector<std::string>& data, const std::string& element)
{
    int s = 0;
    int e = data.size() - 1;
    int m = s + (e-s)/2;
    while (s <= e) {
        if (element < data[m])
        {
            e = m - 1;
            m = s + (e-s)/2;
        }
        else if (element > data[m]) {
            s = m + 1;
            m = s + (e-s)/2;
        }
        else {
            return m;
        }
    }
    return -1;
}

void timeTest(std::vector<std::string>& data, std::string element)
{
    auto start = std::chrono::system_clock::now();
    int lin_idx = linearSearch(data, element);
    auto end = std::chrono::system_clock::now();
    std::cout
    << element
    << " found at "
    << lin_idx
    << " via binary search in "
    << (std::chrono::duration_cast<std::chrono::microseconds>(end-start).count())
    << " microseconds"
    << std::endl;

    start = std::chrono::system_clock::now();
    int bin_idx = binarySearch(data, element);
    end = std::chrono::system_clock::now();
    std::cout
    << element
    << " found at "
    << lin_idx
    << " via binary search in "
    << (std::chrono::duration_cast<std::chrono::microseconds>(end-start).count())
    << " microseconds"
    << std::endl;

    assert(lin_idx == bin_idx);
}

int main()
{
    std::vector<std::string> data = getStringData();
    std::vector<std::string> tests = {"not_here", "mzzzz", "aaaaa"};
    for (const std::string& test: tests) {
        timeTest(data, test);
    }
}