

double ApplyOperations(double a, double b, double (*ptr[])(double, double), size_t size) {
    double sum = 0.0;

    if(size == 0 || ptr == nullptr) {
        return sum;
    }

    for (size_t i = 0; i < size; ++i) {
        if(ptr[i] == nullptr) continue;
        sum += ptr[i](a, b);
    }
    
    return sum;
}