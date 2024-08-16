import numpy as np
from statsmodels.tsa.stattools import adfuller

def ProcessData(filePath):
    print(filePath)
    with open(filePath, 'r') as f:
        data = [float(line.strip()) for line in f]
    
    # 假设这里是处理数据的部分
    # processed_data = [x * 2 for x in data]
    print("ADF TESTING!!!!!")
    result = adfuller(data,2)
    print(result)

    # 修改文件内容，通知C++程序继续执行
    with open(filePath, 'a') as f:
        f.write("DATA_START\n")
        f.write(str(result[0])+"\n")
        f.write(str(result[1])+"\n")
        f.write(str(result[2])+"\n")
        f.write(str(result[3])+"\n")
        f.write("PROCESSING_COMPLETE\n")

def Hello(s):
    print("hello man")
    print(s)
