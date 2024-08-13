#ifndef ADFTEST_H
#define ADFTEST_H

#include <string>
#include <vector>
/* Write your declarations here */
class ADFTest
{
private:
    static std::string m_data_file;
    static std::string m_data_start_flag;
    static std::string m_completion_flag;
    static std::string m_python_file_path;
    // 将数组写入文件
    static bool writeArrayToFile(const std::vector<double>& arr);

    // 等待Python程序返回结果
    static bool waitForPythonCompletion(std::vector<std::string> &ans);

    // 完事清理
    static void cleanUp();
public:
    ADFTest(/* args */){};
    ~ADFTest(){};

    static bool startTest(const std::vector<double> & arr,std::vector<std::string> &ans);
};

#endif // ADFTEST_H