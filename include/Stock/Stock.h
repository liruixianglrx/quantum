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

    void addNewData(std::string data_name,double data);
    Stock(/* args */){};
    ~Stock();
};

// Stock::Stock(/* args */)
// {
// }

// Stock::~Stock()
// {
// }


#endif // STOCK_H