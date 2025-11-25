#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <cmath>

void PrintRoot(double x) {
    // Для избавления от заведомо небольших значений
    if (std::abs(x) < 1e-10) {
        x = 0.0;
    }
    std::cout << std::setprecision(6) << x;
}

void SolveQuadratic(int a, int b, int c) {
    if(a == 0 && b == 0 && c == 0) {
        std::cout << "infinite solutions";
        return;
    }

    double a_ = static_cast<double>(a);
    double b_ = static_cast<double>(b);
    double c_ = static_cast<double>(c);

    if(a_ == 0) {
        if(b_ == 0) {
            // Нет решений
            std::cout << "no solutions";
        } else {
            // Один корень линейного уравнения
            PrintRoot(-c_ / b_);
        }
        return;
    }

    double D = b_*b_ - 4*a_*c_;
    if (D > 0) {
        double sqrt_d = std::sqrt(D);
        double x1 = (-b_ - sqrt_d) / (2.0 * a_);
        double x2 = (-b_ + sqrt_d) / (2.0 * a_);
        
        // Гарантируем, что x1 < x2
        if (x1 > x2) {
            std::swap(x1, x2);
        }
        PrintRoot(x1); 
        std::cout << " ";
        PrintRoot(x2);
    }
    else if (D == 0) {
        double x = -b_ / (2.0 * a_);
        PrintRoot(x);
    }
    else {
        std::cout << "no solutions";
    }
}