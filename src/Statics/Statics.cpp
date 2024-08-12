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

double correlationCoefficient(const std::vector<double>& dataX, const std::vector<double>& dataY) {
    if (dataX.size() != dataY.size()) {
        throw std::invalid_argument("The sizes of the two datasets do not match.");
    }

    double meanX = mean(dataX);
    double meanY = mean(dataY);

    double sumXY = 0.0, sumX2 = 0.0, sumY2 = 0.0;

    for (size_t i = 0; i < dataX.size(); ++i) {
        sumXY += (dataX[i] - meanX) * (dataY[i] - meanY);
        sumX2 += (dataX[i] - meanX) * (dataX[i] - meanX);
        sumY2 += (dataY[i] - meanY) * (dataY[i] - meanY);
    }

    double numerator = sumXY;
    double denominator = sqrt(sumX2 * sumY2);

    if (denominator == 0) {
        throw std::invalid_argument("Denominator is zero, indicating no variability in one or both datasets.");
    }

    return numerator / denominator;
}
}