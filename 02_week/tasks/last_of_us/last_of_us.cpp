#include <stdexcept>


const int* FindLastElement(const int* begin, const int* end, bool (*predicate)(const int)) {
    if((begin > end) || (begin == nullptr) || (end == nullptr)) return end;

    for(const int* ptr = end - 1; ptr >= begin; --ptr) {
        if (predicate(*ptr)) {return ptr;}
    }
    return end;
}