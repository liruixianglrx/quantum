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
    static std::vector <std::string> m_ADFT_result;
    static double m_pvalue;
    // 将数组写入文件
    static bool writeArrayToFile(const std::vector<double>& arr);

    // 等待Python程序返回结果
    static bool waitForPythonCompletion(std::vector<std::string> &ans);

    // 完事清理
    static void cleanUp();
    
    static bool m_has_inited;
public:
    ADFTest(/* args */){};
    ~ADFTest(){};
    // static double m_pvalue;
    // 判断stationary
    static bool isStationary();

    static void setPValue(double p);
    static bool startTest(const std::vector<double> & arr);
    static std::string getResultByIndex(int idx);
};

#endif // ADFTEST_H