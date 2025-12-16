#include <stdexcept>
#include <vector>


void Filter(std::vector<int>& vec, bool (*predicate)(int)) {
    size_t write_index = 0;

    if (vec.empty() || predicate == nullptr) {
        return;
    }
    
    for (size_t i = 0; i < vec.size(); ++i) {
        if (predicate(vec[i])) {
            if (i != write_index) {
                vec[write_index] = vec[i];
            }
            ++write_index;
        }
    }
    vec.resize(write_index);
}