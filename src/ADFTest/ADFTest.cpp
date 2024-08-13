#include "ADFTest.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdio>

#include <memory>
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
    std::cout << "Waiting for Python to complete processing..." << std::endl;
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
            std::cout << "Python processing complete. Resuming C++ execution." << std::endl;
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

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}


bool ADFTest::startTest(const std::vector<double> & arr,std::vector<std::string> &ans){\
    cleanUp();

    if (!writeArrayToFile(arr)) {
        std::cout<<"\nADF Test ERROR : CAN NOT WRITE TO FILE\n";
        return false;
    }

    std::string cmd = "python " + m_python_file_path;
    exec(cmd.c_str());
    // int result = system(cmd.c_str());
    // if (result != 0) {
    //     std::cout<<"\nADF Test ERROR : EXEC ERROR\n";
    //     return false;
    // }

    if (!waitForPythonCompletion(ans)) {
        std::cout<<"\nADF Test ERROR : NO RESULT\n";
        return false;
    }

    // cleanUp();

    return true;
}; 
// python D:/coding/codes/quantum/src/ADFTest/ADFTest.py

std::string ADFTest::m_data_file = "./data.txt";
std::string ADFTest::m_data_start_flag = "DATA_START";
std::string ADFTest::m_completion_flag = "PROCESSING_COMPLETE";
std::string ADFTest::m_python_file_path = "D:/coding/codes/quantum/src/ADFTest/ADFTest.py";