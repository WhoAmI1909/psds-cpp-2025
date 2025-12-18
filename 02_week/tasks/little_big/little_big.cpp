#include <stdexcept>
#include <cstring>
#include <iomanip>
#include <iostream>


void PrintMemory(int value, bool reverse = false) {
    unsigned char* bytes = reinterpret_cast<unsigned char*>(&value);
    
    std::cout << "0x";
    
    if (reverse) {
        // Вывод в обратном порядке (big-endian)
        for (int i = sizeof(int) - 1; i >= 0; --i) {
            std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(bytes[i]);
        }
    } else {
        // Вывод в естественном порядке (little-endian)
        for (size_t i = 0; i < sizeof(int); ++i) {
            std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(bytes[i]);
        }
    }
    
    std::cout << std::endl;
}

void PrintMemory(double value, bool reverseBytes = false) {
    unsigned char* bytes = reinterpret_cast<unsigned char*>(&value);
    
    std::cout << "0x";
    
    if (reverseBytes) {
        // Вывод в обратном порядке (big-endian)
        for (int i = sizeof(double) - 1; i >= 0; --i) {
            std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(bytes[i]);
        }
    } else {
        // Вывод в естественном порядке (little-endian)
        for (size_t i = 0; i < sizeof(double); ++i) {
            std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(bytes[i]);
        }
    }
    
    std::cout << std::endl;
}