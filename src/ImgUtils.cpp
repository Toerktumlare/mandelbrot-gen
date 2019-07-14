#include <complex>
#include "ImgUtils.h"

double ImgUtils::filter(const int &iterations, const std::complex<double> z) {
    return iterations + 1 - std::log2(log(norm(z)) * 0.5);
}
