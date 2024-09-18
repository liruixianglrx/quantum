#ifndef PLOT_H
#define PLOT_H

#include <vector>
namespace plot{
    void plotYValue(const std::vector<double> &y);
    void plotYValueWithColor(const std::vector<double> &y,const std::vector<double> &color);
    void plotRolling(const std::vector<double> &y,int window);
    void cleanUp();
}

#endif // PLOT_H