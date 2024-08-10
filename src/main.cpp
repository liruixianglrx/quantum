#include <OpenXLSX.hpp>
#include "tmp.h"
#include "tmp2.h"

using namespace OpenXLSX;

int main() {

    XLDocument doc;
    doc.create("Spreadsheet.xlsx");
    auto wks = doc.workbook().worksheet("Sheet1");

    wks.cell("A1").value() = "Hello, OpenXLSX!";

    doc.save();
    a();
    b();
    return 0;
}