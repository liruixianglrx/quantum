<!-- 依赖库 -->
sudo apt-get install libblas-dev liblapack-dev gfortran为了matplotlib-cpp
git 地址 git@github.com:troldal/OpenXLSX.git


<!-- this is doc for OpenXLSX -->

<!-- 文件创建 demo1-->
XLDocument doc;
doc.create("./Demo01.xlsx");
auto wks = doc.workbook().worksheet("Sheet1");

<!-- 单元值获取和接受 -->
wks.cell("A1").value() = 3.14159265358979323846;
double tmp = wks.cell("A1").value();

XLCellValue A1 = wks.cell("A1").value();
A1.set<int>(10);
auto tmp = A1.get<int>();

<!-- 返回该单元类型 -->
A1.typeAsString()

<!-- 公式处理 demo2 -->
wks.cell("B2").formula() = "SQRT(B1)";

<!-- range处理 demo5-->
<!-- OpenXLSX 定义了两个常量：MAX_ROWS 是工作表中的最大行数，MAX_COLS 是最大列数。 -->
<!-- 'range()' 方法接受两个 XLCellReference 对象，一个用于左上角的单元格， -->
auto rng = wks.range(XLCellReference("A1"), XLCellReference(OpenXLSX::MAX_ROWS, 8));
for (auto& cell : rng) cell.value()=10;

<!-- accumulate 函数： -->
#include <numeric> 
std::accumulate(first,last,init,binary_op)

<!-- rows处理 demo06-->
for (auto& row : wks.rows(OpenXLSX::MAX_ROWS)) 返回每一行
    rows.values = vector<>

<!-- rows得到每个cell -->
for (auto& row : wks.rows(OpenXLSX::MAX_ROWS)) 
        for (auto cell: row.cells(8)) cell.value() = distr(generator);

cells是个迭代器，cells().begin() cells().end()

<!-- 向标准数据结构转换 -->
<!-- 转换为 std::vector<XLCellValue> -->
    for (auto& row : wks.rows()) {
        for (auto& value : std::vector<XLCellValue>(row.values())) {
            cout << value << " ";
        }
        cout << endl;
    }
<!-- 转换为 基础类型 -->
    for (auto& value : std::vector<int>(wks.row(1).values())) cout << value << " ";
    cout << endl;