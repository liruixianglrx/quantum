// // main.cpp
// #include <Python.h>
// #include <iostream>
// #include <string>
// using namespace std;
// int main(int argc, char *argv[]) {
//   // 初始化python解释器.C/C++中调用Python之前必须先初始化解释器
//   std::wstring PythonPath = L"D:\\coding\\anaconda\\python.exe";
//   std::wstring PythonHome = L"";
//   Py_SetPythonHome(PythonHome.c_str());

  
//   Py_Initialize();
  
//   PyObject *name,*my_module,*func,*callfunc,*args;

//   name = PyUnicode_FromString ((char*)"scrpit");
  
//   my_module = PyImport_Import(name);
//   func = PyObject_GetAttrString(my_module,(char*)"fun1");
//   callfunc =  PyObject_CallObject(func,NULL);
//   double fun1_out = PyFloat_AsDouble(callfunc);
//   // 执行一个简单的执行python脚本命令
//   // PyRun_SimpleString("print('hello world python')\n");
//   // 撤销Py_Initialize()和随后使用Python/C API函数进行的所有初始化
//   Py_Finalize();

//   cout<<"out come is "<< fun1_out<<endl;
//   return 0;
// }

// // g++ ./1.cpp -L D:\coding\anacaonda\libs -lpython312 -ID:\coding\anacaonda\include