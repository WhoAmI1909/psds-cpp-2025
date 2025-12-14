#include <stdexcept>
#include <vector>

std::vector<int> Unique(std::vector<int> sorted_nums) {
    std::vector<int> unique_nums;
    if(sorted_nums.empty()) {return unique_nums;}
    int previous = *(sorted_nums.begin());
    unique_nums.push_back(previous);
    for(auto num : sorted_nums) {
        if(previous != num) {
            previous = num;
            unique_nums.push_back(previous);
        }
    }
    unique_nums.shrink_to_fit();
    return unique_nums;
}