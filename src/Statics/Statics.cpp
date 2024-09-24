#include <vector>
#include <numeric> // 用于std::accumulate
#include <cmath>   // 用于sqrt和pow
#include<algorithm> //max
#include <stdexcept>
#include "Statics.h"

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

// 计算RSI ，包含当天的涨跌幅，如果len为2,需要传入3天的数据(包含当天前一天)
double RSI(const std::vector<double>& data,int len) {
    std::vector <double>gains;
    std::vector <double>losses;

    for (int i=1;i<=len; i++) {
        gains.push_back(std::max(data[i] - data[i-1],0.0));
        losses.push_back(std::max(data[i-1]-data[i],0.0));
    }

    double SMA_gain = SMA(gains,len,1);
    double SMA_loss = SMA(losses,len,1);

    return SMA_gain/(SMA_gain+SMA_loss)*100;
}

// 计算SMA，返回当天的SMA，data len和len长度相同
double SMA(const std::vector<double> &data,int n,int weight) {
    std::vector<double> y;
    y.push_back(data[0]);
    double tmp;
    for (int i=1;i<n;i++) {
        tmp =  (weight*data[i] + (n-weight)*y[i-1])/n;
        y.push_back(tmp);
    }

    return y[n-1];
}

double AverageTrueRange(const std::vector<double> &close,const std::vector<double> &high,const std::vector<double> &low,int day){
    std::vector<double> TR;
    for (int i=0;i<day;i++) {
        double tmp;
        tmp = std::max(abs(high[i] - low[i]),abs(high[i]-close[i]));
        tmp = std::max(std::abs(low[i]-close[i]),tmp);
        TR.push_back(tmp);
    }

    return mean(TR);
}

double NormalizedAverageTrueRange(const std::vector<double> &close,const std::vector<double> &high,const std::vector<double> &low,int day){
    return AverageTrueRange(close,high,low)/close[day-1];
}

}
