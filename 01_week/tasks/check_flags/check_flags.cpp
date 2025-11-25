#include <cstdint>
#include <stdexcept>
#include <iostream>


enum class CheckFlags : uint8_t {
    NONE = 0,
    TIME = (1 << 0),
    DATE = (1 << 1),
    USER = (1 << 2),
    CERT = (1 << 3),
    KEYS = (1 << 4),
    DEST = (1 << 5),
    ALL = TIME | DATE | USER | CERT | KEYS | DEST
};

void PrintCheckFlags(CheckFlags flags) {
    // Значение находится в допустимом диапазоне
    uint8_t value = static_cast<uint8_t>(flags);
    if (value == 0) {
        std::cout << "[]";
        return;
    }
    if (value > static_cast<uint8_t>(CheckFlags::ALL)) {
        return;
    }
    // Последнее значение
    if (value == static_cast<uint8_t>(CheckFlags::ALL)) {
        std::cout << "[TIME,DATE,USER,CERT,KEYS,DEST]";
        return;
    }

    std::cout << "[";
    bool first = true;
    
    const std::pair<CheckFlags, const char*> flag_names[] = {
        {CheckFlags::TIME, "TIME"},
        {CheckFlags::DATE, "DATE"},
        {CheckFlags::USER, "USER"},
        {CheckFlags::CERT, "CERT"},
        {CheckFlags::KEYS, "KEYS"},
        {CheckFlags::DEST, "DEST"}
    };
    
    for (const auto& [flag, name] : flag_names) {
        if (value & static_cast<uint8_t>(flag)) {
            if (!first) std::cout << ",";
            std::cout << name;
            first = false;
        }
    }
    
    std::cout << "]";
}
