#include "OpenXLSX.hpp"
#include <string.h>
#include "DateTime.h"
#include "DataReader.h"
using namespace OpenXLSX;
using namespace std;

int main() {
    cout<<"ok";
    // XLDocument doc;
    // std::string path = "./Demo07.xlsx";
    // doc.create(path);
    // auto wks = doc.workbook().worksheet("Sheet1");
    // for (auto& row : wks.rows(6)) {
    //     for (auto cell: row.cells(8)) cell.value() = 66;

    //     // XLRow 类提供了 'cells()' 方法。它提供了行中单元格的开始和结束迭代器。
    //     // 通过迭代单元格，可以按通常方式读取和写入值。
    // }
    // cout << "正在保存电子表格 ..." << endl;
    // doc.save();
    // doc.close();

    // doc.open(path);
    // doc.close();

    // path = "./t.xlsx";
    // doc.open(path);
    // doc.close();

    DataReader dr("./t");
    StockPool stk_pool;

    dr.readDataFromWorksheet("Sheet1",&stk_pool);
    return 0;
}