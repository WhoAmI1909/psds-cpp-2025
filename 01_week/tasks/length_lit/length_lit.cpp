double FT_IN_M = 1.0 / 0.3048;
double FT_IN_INCHES = 12.0;
double INCH_IN_CM = 2.54;

// Футы в другие величины
double operator""_ft_to_m(long double ft) {
    return ft / FT_IN_M;
}

double operator""_ft_to_cm(long double ft) {
    return ft / FT_IN_M * 100.0;
}

double operator""_ft_to_in(long double ft) {
    return ft * FT_IN_INCHES;
}

// Дюймы в другие величины
double operator""_in_to_ft(long double in) {
    return in / FT_IN_INCHES;
}

double operator""_in_to_cm(long double in) {
    return in * INCH_IN_CM;
}

double operator""_in_to_m(long double inches) {
    return inches * INCH_IN_CM / 100;
}

// См в другие величины
double operator""_cm_to_m(long double centimeters) {
    return centimeters / 100;
}

double operator""_cm_to_in(long double centimeters) {
    return centimeters / INCH_IN_CM;
}

double operator""_cm_to_ft(long double centimeters) {
    return centimeters / (FT_IN_INCHES * INCH_IN_CM);
}

// Метры в другие величины
double operator""_m_to_ft(long double meters) {
    return meters * 100 / (INCH_IN_CM * FT_IN_INCHES);
}

double operator""_m_to_in(long double meters) {
    return meters * 100 / INCH_IN_CM;
}

double operator""_m_to_cm(long double meters) {
    return meters * 100;
}