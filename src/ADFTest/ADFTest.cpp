#include "ADFTest.h"
#include "Python.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdio>

#include <array>

bool ADFTest::writeArrayToFile(const std::vector<double>& arr){
    std::ofstream outfile(m_data_file);
    if (outfile.is_open()) {
        for (const auto& val : arr) {
            outfile << val << "\n";
        }
        outfile.close();
        std::cout << "Array written to file: " << m_data_file << std::endl;
    } else {
        std::cerr << "Unable to open file for writing: " << m_data_file << std::endl;
        return false;
    }
    return true;
}

bool ADFTest::waitForPythonCompletion(std::vector<std::string> &ans){
    std::cout << "Waiting for ADF to complete processing..." << std::endl;
    while (true) {
        std::ifstream infile(m_data_file);
        std::string line;
        bool completed = false;
        while (std::getline(infile, line)) {
            if (line == m_data_start_flag) {
                while (line != m_completion_flag) {
                    std::getline(infile, line);
                    ans.push_back(line);
                }

                ans.pop_back();
                completed = true;
                break;
            }
        }
        infile.close();
        if (completed) {
            std::cout << "ADF processing complete. Resuming C++ execution." << std::endl;
            break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));  // 每秒检查一次
    }

    return true;
}

void ADFTest::cleanUp(){
     if (std::remove(m_data_file.c_str()) != 0) {
        std::perror("Error deleting file"); // 输出错误信息
    }
}

// std::string exec(const char* cmd) {
//     std::array<char, 128> buffer;
//     std::string result;
//     std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
//     if (!pipe) {
//         throw std::runtime_error("popen() failed!");
//     }
//     while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
//         result += buffer.data();
//     }
//     return result;
// }


bool ADFTest::startTest(const std::vector<double> & arr){
    cleanUp();
    m_ADFT_result.clear();

    if (!writeArrayToFile(arr)) {
        std::cout<<"\nADF Test ERROR : CAN NOT WRITE TO FILE\n";
        return false;
    }


    // TODO:当一系列时，每次都要import太耗时
    // TODO:PYTHON解释器类
    if (!m_has_inited){
        Py_Initialize();
        PyRun_SimpleString("import numpy as np");
        PyRun_SimpleString("import sys");
        PyRun_SimpleString("sys.path.append('/Users/liruixiang/quantum_env/lib/python3.12/site-packages')");
        // PyRun_SimpleString("from statsmodels.tsa.stattools import adfuller");
        PyRun_SimpleString("import statsmodels");
        #ifdef __linux__
        PyRun_SimpleString("sys.path.append('/home/lrx/codes/quantum/src/ADFTest')");
        #elif __APPLE__
        PyRun_SimpleString("sys.path.append('/Users/liruixiang/codes/quantum/src/ADFTest')");
        #endif
        m_has_inited=true;
    }

    PyObject* pModule = NULL;
    PyObject* pFunc = NULL;
    PyObject* pArg = NULL;

    pModule = PyImport_ImportModule("ADFTest"); 
    pFunc = PyObject_GetAttrString(pModule, "ProcessData");
    pArg = Py_BuildValue("(s)", m_data_file.c_str()); 
    // pModule = PyImport_ImportModule("mytest"); 
    // pFunc = PyObject_GetAttrString(pModule, "Hello");
    // pArg = Py_BuildValue("(s)", m_data_file.c_str()); 

    PyObject_Call(pFunc, pArg, NULL);

    // Py_Finalize();

    if (!waitForPythonCompletion(m_ADFT_result)) {
        std::cout<<"\nADF Test ERROR : NO RESULT\n";
        return false;
    }

    cleanUp();

    return true;
}; 

bool ADFTest::isStationary(){
    return (std::stod(m_ADFT_result[1]) < m_pvalue);
}

void ADFTest::setPValue(double p) {
    m_pvalue = p;
}

 std::string ADFTest::getResultByIndex(int idx){
    return m_ADFT_result[idx];
 }
// python D:/coding/codes/quantum/src/ADFTest/ADFTest.py

//init
#ifdef _WIN32
std::string DataReader::m_path = "D:/coding/codes/quantum/src/ADFTest/data.txt";
#elif __APPLE__
std::string ADFTest::m_data_file = "/Users/liruixiang/codes/quantum/src/ADFTest/data.txt";
#elif __linux__
std::string ADFTest::m_data_file = "/home/lrx/codes/quantum/src/ADFTest/data.txt";
#endif

std::string ADFTest::m_data_start_flag = "DATA_START";
std::string ADFTest::m_completion_flag = "PROCESSING_COMPLETE";
std::vector <std::string> ADFTest::m_ADFT_result{};
double ADFTest::m_pvalue = 0.05;
bool ADFTest::m_has_inited = false;
// std::string ADFTest::m_python_file_path = "D:/coding/codes/quantum/src/ADFTest/ADFTest.py";