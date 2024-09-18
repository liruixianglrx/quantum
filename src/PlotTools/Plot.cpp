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

        Py_Initialize();
        PyRun_SimpleString("import sys");
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
    void plotYValueWithColor(const std::vector<double> &y,const std::vector<double> &color){
        std::vector<double> x;
        for (int i=0;i<y.size();i++) {
            x.push_back(i+1);
        }

        cleanUp();
        std::ofstream file(m_data_file);
        for (size_t i = 0; i < x.size(); ++i) {
            file << x[i] << " " << y[i] <<" "<<color[i]<< std::endl;
        }
        file.close();

        Py_Initialize();
        PyRun_SimpleString("import sys");
        #ifdef __linux__
        PyRun_SimpleString("sys.path.append('/home/lrx/codes/quantum/src/PlotTools')");
        #elif __APPLE__
        PyRun_SimpleString("sys.path.append('/Users/liruixiang/codes/quantum/src/PlotTools')");
        #endif
        PyRun_SimpleString("import matplotlib");

        PyObject* pModule = PyImport_ImportModule("Plot"); 
        PyObject* pFunc = PyObject_GetAttrString(pModule, "PlotYValueWithColor");
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