#ifndef STATICS_H
#define STATICS_H

#include <vector>
/* Write your declarations here */
namespace Statics{
    double mean(const std::vector<double>& data);
    double variance(const std::vector<double>& data);
    double standardDeviation(const std::vector<double>& data);
}
#endif // STATICS_H