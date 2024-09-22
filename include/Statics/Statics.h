#ifndef STATICS_H
#define STATICS_H

#include <vector>
/* Write your declarations here */
namespace Statics{
    double mean(const std::vector<double>& data);
    double variance(const std::vector<double>& data);
    double standardDeviation(const std::vector<double>& data);
    double correlationCoefficient(const std::vector<double>& dataX, const std::vector<double>& dataY);
    double RSI(const std::vector<double>& data,int len);
    double SMA(const std::vector<double> &data,int n,int weight);
    double AverageTrueRange(const std::vector<double> &close,const std::vector<double> &high,const std::vector<double> &low,int day=14);
    double NormalizedAverageTrueRange(const std::vector<double> &close,const std::vector<double> &high,const std::vector<double> &low,int day=14);
}
#endif // STATICS_H