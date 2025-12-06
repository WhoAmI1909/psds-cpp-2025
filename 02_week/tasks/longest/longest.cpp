#include <stdexcept>


char* FindLongestSubsequence(const char* begin, const char* end, size_t& count) {
    if (begin == nullptr || end == nullptr || begin >= end) {
        count = 0;
        return nullptr;
    }

    const char* longest_ptr = begin;
    const char* current_ptr = begin;
    size_t max_count = 1; 
    size_t current_count = 1;

    for (const char* ptr = begin + 1; ptr < end; ++ptr) {
        if (*ptr == *(ptr - 1)) {
            current_count++;
        } else {
            if(current_count > max_count) {
                max_count = current_count;
                longest_ptr = current_ptr;
            }
            current_ptr = ptr;
            current_count = 1;
        }
    }

    if(current_count > max_count) {
        max_count = current_count;
        longest_ptr = current_ptr;
    }
    count = max_count;
    return const_cast<char*>(longest_ptr);
}
