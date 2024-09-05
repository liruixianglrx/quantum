import numpy as np
import os
import contextlib
from statsmodels.tsa.stattools import adfuller

def ProcessData(filePath):
    with open(filePath, 'r') as f:
        data = [float(line.strip()) for line in f]

    with open('output.txt', 'w') as f:
        with contextlib.redirect_stdout(f):
            print("This will be written to output.txt")

    if os.path.exists('output.txt'):
        os.remove('output.txt')
    
    result = adfuller(data,2)
    # print("ADF result data :",result)

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
