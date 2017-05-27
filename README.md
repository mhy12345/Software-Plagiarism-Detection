# Software-Plagiarism-Detection

##结构

###detector.cpp/h

Detector 基类，无意义

FileDetector 检测两个文件的相关性

ProjectDetector 检测两个工程的相关性

###file.cpp/h
PFile 处理单个文件，内含文件指纹提取算法

###project.cpp/h
PProject 处理单个工程，内含工程目录读取算法

###cost_flow.cpp/h
CostFlow 费用流算法类

##继承