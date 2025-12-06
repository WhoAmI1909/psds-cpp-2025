#include <cstddef>
#include <stdexcept>
#include <cmath>


double CalculateRMS(double values[], size_t size) {
    if(size == 0 || values == nullptr) {    // Проверка на отсутствие элементов в массиве и на нулевой указатель
        return 0.0;
    }
    double square_sum = 0.0;
    for(size_t i = 0; i < size; ++i) {
        square_sum += values[i] * values[i];
    }
    return sqrt(square_sum/size);
}