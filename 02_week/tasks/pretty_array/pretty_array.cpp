#include <stdexcept>
#include <iostream>

void PrintArray(const int* begin, const int* end, int constraint = 0) {
    if (begin == end || begin == nullptr || end == nullptr)
    {
        std::cout << "[]\n";
        return;
    }
    
    int count = 0;
    std::cout << "[";
    if(begin < end) {
        for(const int* ptr = begin; ptr < end; ++ptr) {
            if((count == constraint) && (constraint != 0)) {
                count = 0;
                std::cout << "...\n ";
            }
            std::cout << *ptr;
            if(ptr != end - 1) { std::cout << ", "; }
            ++count;
        }
        std::cout << "]\n";
    } else {
        ++end;
        for(const int* ptr = begin; ptr >= end; --ptr) {
            if((count == constraint) && (constraint != 0)) {
                count = 0;
                std::cout << "...\n ";
            }
            std::cout << *ptr;
            if(ptr != end) { std::cout << ", "; }
            if(ptr == end) { break; }
            ++count;
        }
        std::cout << "]\n";
    }
}