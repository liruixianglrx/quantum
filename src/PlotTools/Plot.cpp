#include <iostream>
#include <fstream>
#include "Python.h"
#include "Plot.h"

namespace plot{
    #ifdef _WIN32
    std::string m_data_file = "D:/coding/codes/quantum/src/PlotTools/plot_data.txt";
    #elif __APPLE__
    std::string m_data_file = "/Users/liruixiang/codes/quantum/src/PlotTools/plot_data.txt";
    #elif __linux__
    std::string m_data_file = "/home/lrx/codes/quantum/src/PlotTools/plot_data.txt";
    #endif


    void plotYValue(const std::vector<double> &y){
        std::vector<double> x;
        for (int i=0;i<y.size();i++) {
            x.push_back(i+1);
        }

        cleanUp();
        std::ofstream file(m_data_file);
        for (size_t i = 0; i < x.size(); ++i) {
            file << x[i] << " " << y[i] << std::endl;
        }
        file.close();

        #ifdef __linux__
        PyRun_SimpleString("sys.path.append('/home/lrx/codes/quantum/src/PlotTools')");
        #elif __APPLE__
        PyRun_SimpleString("sys.path.append('/Users/liruixiang/codes/quantum/src/PlotTools')");
        #endif
        PyRun_SimpleString("import matplotlib");

        PyObject* pModule = PyImport_ImportModule("Plot"); 
        PyObject* pFunc = PyObject_GetAttrString(pModule, "PlotYValue");
        PyObject* pArg = Py_BuildValue("(s)", m_data_file.c_str());
        PyObject_Call(pFunc, pArg, NULL);
        cleanUp();
    }


    void plotRolling(const std::vector<double> &y, int window){
        std::vector<double> x;
        for (int i=0;i<y.size()-window+1;i++) {
            x.push_back(i+1);
        }

        cleanUp();
        std::vector<double> averages;  
        double windowSum = 0.0;

        // 确保window不大于y的大小  
        if (window > y.size()) {  
            std::cout << "Error: Window size is larger than the array size." << std::endl;  
            return ; // 可以选择返回一个空vector或者抛出一个异常  
        }  
  
        // 初始化窗口并计算初始窗口的和  
        for (int i = 0; i < window; ++i) {  
            windowSum += y[i];  
        }  

        // 添加第一个窗口的平均值  
        averages.push_back(windowSum / window);  
    
        // 滑动窗口，更新平均值  
        for (int i = window; i < y.size(); ++i) {  
            // 移除窗口最左边的元素  
            windowSum -= y[i - window];  
            // 加上新进入窗口的元素  
            windowSum += y[i];  
            // 计算新的平均值并添加到结果中  
            averages.push_back(windowSum / window);  
        }  

        std::ofstream file(m_data_file);
        
        for (size_t i = 0; i < x.size(); ++i) {
            file << x[i] << " " << averages[i] << std::endl;
        }
        file.close();

        #ifdef __linux__
        PyRun_SimpleString("sys.path.append('/home/lrx/codes/quantum/src/PlotTools')");
        #elif __APPLE__
        PyRun_SimpleString("sys.path.append('/Users/liruixiang/codes/quantum/src/PlotTools')");
        #endif
        PyRun_SimpleString("import matplotlib");

        PyObject* pModule = PyImport_ImportModule("Plot"); 
        PyObject* pFunc = PyObject_GetAttrString(pModule, "PlotYValue");
        PyObject* pArg = Py_BuildValue("(s)", m_data_file.c_str());
        PyObject_Call(pFunc, pArg, NULL);
        cleanUp();
    }

    void cleanUp(){
        if (std::remove(m_data_file.c_str()) != 0) {
            std::perror("Error deleting file"); // 输出错误信息
        }
    }
}