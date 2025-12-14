#include <stdexcept>
#include <vector>

std::vector<size_t> FindAll(const std::vector<int>& container, bool (*predicate)(int)) {
    if(container.empty() || predicate == nullptr) {
        return {};
    }
    
    std::vector<size_t> result;
    
    for (size_t i = 0; i < container.size(); ++i) {
        if (predicate(container[i])) {
            result.push_back(i);
        }
    }
    result.shrink_to_fit();
    return result;
}