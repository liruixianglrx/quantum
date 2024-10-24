#include "DataReader.h"

DataReader::DataReader(const std::string &file_name){
    // setPath("D:/coding/codes/quantum_data");
    // setTimePos("D2");
    // setRowPos(2);
    m_path += file_name+".xlsx";
    m_doc.open(m_path);
}

void DataReader::setPath(const std::string &path){
    m_path = path;
}


void DataReader::setStartPos(const int row_pos,const int column_pos){
    m_row_pos = row_pos;
    m_column_pos = column_pos;
}

void DataReader::readDataFromWorksheet(const std::string &work_sheet,StockPool *stk_pool){
    auto wks = m_doc.workbook().worksheet(work_sheet);
    
    auto end = wks.rowCount() -2;

    // 日期读入
    auto date_row = wks.row(m_row_pos-1);
    std::vector<XLCellValue> date_values = date_row.values();
    for (auto it=date_values.begin()+ m_column_pos - 1;it != date_values.end();it++) {
        auto type = it->typeAsString();
        std::string tmp = it->getString();
        // auto t2 =it->get<std::string>();
        stk_pool->m_dates.push_back(it->get<int>());
    }

    Stock *stock =nullptr;
    for (auto &row : wks.rows(m_row_pos,wks.rowCount() -2)) {
        //股票信息录入
        std::vector<XLCellValue> read_values = row.values();
        auto start_value = read_values.begin();
        auto end_value = start_value + m_column_pos - 2;

        //加入新股票，和其股票信息
        if (stock == nullptr || stock->m_stock_code != start_value->getString())
        {
            for (auto it = start_value; it != end_value; it++){
                if (it == start_value) {
                    //add stock and set stock code
                    stk_pool->addStockByCode(it->getString());

                    stock = stk_pool->getStockByCode(it->getString());
                    stock->m_stock_code = it->getString();
                } else {
                    stock->m_stock_info.emplace_back(it->getString());
                }
            }
        }

        // 获得股票数据名称
        std::string data_name = (start_value + m_column_pos - 2)->getString();

        start_value = start_value + m_column_pos - 1;

        int idx=0;
        //股票数据录入
        std::string price;
        for (auto it = start_value;it != read_values.end(); it++) {
            //for debuging
            // auto price = it->getString();
            // idx++;

            if (it->getString() != "#DIV/0!") {
                price = it->getString();
            }
            stock->addNewData(data_name,std::stod(price));
        }

    }
}

//init
#ifdef _WIN32
std::string DataReader::m_path = "D:/coding/codes/quantum/quantum_data/";
#elif __APPLE__
std::string DataReader::m_path = "/Users/liruixiang/codes/quantum/quantum_data/";
#elif __linux__
std::string DataReader::m_path = "/home/lrx/codes/quantum/quantum_data/";
// std::string DataReader::m_path = "/media/lrx/新加卷1/coding/codes/quantum/quantum_data/";
#endif

// std::string DataReader::m_path = "/media/lrx/新加卷1/coding/codes/quantum_data/";

int DataReader::m_row_pos = 3;
int DataReader::m_column_pos = 4;
