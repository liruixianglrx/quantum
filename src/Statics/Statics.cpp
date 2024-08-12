#include <vector>
#include <numeric> // 用于std::accumulate
#include <cmath>   // 用于sqrt和pow
// #include "Statics.h"

namespace Statics{

double mean(const std::vector<double>& data) {
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    return sum / data.size();
}

double variance(const std::vector<double>& data) {
    double m = mean(data);
    double sum = 0.0;
    for (double x : data) {
        sum += (x - m) * (x - m);
    }
    return sum / data.size();
}

double standardDeviation(const std::vector<double>& data) {
    return sqrt(variance(data));
}
}