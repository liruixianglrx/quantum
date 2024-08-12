#include "DataReader.h"

DataReader::DataReader(const std::string &file_name){
    // setPath("D:/coding/codes/quantum_data");
    // setTimePos("D2");
    // setRowPos(2);
    m_path += file_name+".xlsx";
    // /Users/liruixiang/quantum/src/t.xlsx
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
    
    for (auto &row : wks.rows(m_row_pos,wks.rowCount() -2)) {
        Stock *stock;

        //股票信息录入
        std::vector<XLCellValue> read_values = row.values();
        auto start_value = read_values.begin();
        auto end_value = start_value + m_row_pos-1;

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

        // 获得股票数据名称
        std::string data_name = (start_value + m_row_pos -1)->getString();

        start_value = start_value + m_row_pos;
        //股票数据录入
        for (auto it = start_value;it != read_values.end(); it++) {
            auto price = it->getString();
            stock->addNewData(data_name,std::stod(it->getString()));
        }

    }
}

//init
#ifdef _WIN32
std::string DataReader::m_path = "D:/coding/codes/quantum_data/";
#elif __APPLE__
std::string DataReader::m_path = "/Users/liruixiang/quantum_data/";
#endif

int DataReader::m_row_pos = 3;
int DataReader::m_column_pos = 4;
