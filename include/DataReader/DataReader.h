#ifndef DATAREADER_H
#define DATAREADER_H

#include <string>
#include "OpenXLSX.hpp"
#include "StockPool.h"

using namespace OpenXLSX;
/* Write your declarations here */
class DataReader
{
private:
    // path that stores the file
    static std::string m_path;
    // opened excel
    OpenXLSX::XLDocument m_doc;
    // 数据起始行
    static int m_row_pos,m_column_pos;
public:
    DataReader(/* args */){};
    ~DataReader(){m_doc.close();};

    //open a datasource with file name
    DataReader(const std::string &file_name);

    // set the path that contains the file
    static void setPath(const std::string &path);

    // set the start_pos
    static void setStartPos(const int row_pos,const int column_pos);

    void readDataFromWorksheet(const std::string &work_sheet,StockPool *stk_pool);
};

#endif // DATAREADER_H