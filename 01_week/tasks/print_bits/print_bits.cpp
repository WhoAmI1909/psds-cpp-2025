#include <cstddef>
#include <stdexcept>
#include <iostream>


void PrintBits(long long value, size_t bytes) {
    using std::cout;
    // Проверка корректности размера
    if (bytes == 0 || bytes > 8) {
        return;
    }
    std::cout << "0b";

    // Проходим по всем битам, начиная со старшего
    for (size_t pos = bytes * 8; pos > 0; --pos) {        
        // Получаем значение бита на текущей позиции
        int bit = (value >> (pos - 1)) & 1;
        std::cout << bit;
        
        // Добавляем апостроф между байтами (после каждых 4 бит, кроме последней группы)
        if ((pos - 1) > 0 && (pos - 1) % 4 == 0) {
            std::cout << "'";
        }
    }
    
    std::cout << "\n";
}
