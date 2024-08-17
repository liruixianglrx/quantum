#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <DateTime.h>
#include <unordered_map>
#include <vector>
/* Write your declarations here */
class Stock
{
private:
    // start date of data
    DateTime m_start_date;
    std::unordered_map<std::string,std::vector<double>> m_datas;

public:
    // stock code
    std::string m_stock_code;
    // stock info
    std::vector<std::string> m_stock_info;

    void addNewData(const std::string &data_name,double data);
    int getDataLen();
    std::vector<double> &getDataByDataName(const std::string &data_name);
    Stock(/* args */){};
    ~Stock(){};
};
#endif // STOCK_H