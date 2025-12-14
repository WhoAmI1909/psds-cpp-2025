#include <stdexcept>
#include <vector>
#include <cmath>

struct DataStats {
    double avg = 0.0;
    double sd = 0.0;
};

DataStats CalculateDataStats(std::vector<int> numbers) {
    DataStats stats;
    
    if(numbers.empty()) {
        return stats;
    }

    for(auto num : numbers) {
        stats.avg += num;
        stats.sd += static_cast<long long>(num) * num;
    }
    // Вычисляем среднее значение
    stats.avg = static_cast<double>(stats.avg) / numbers.size();

    if (numbers.size() > 1) {
        stats.sd = std::sqrt((stats.sd - numbers.size() * stats.avg * stats.avg) / numbers.size());
    }
    else {
        stats.sd = 0;
    }
    return stats;
}
