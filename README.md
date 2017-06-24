# Software-Plagiarism-Detection

## 结构

### costflow_alg.h/cpp

费用流算法实现

### detector.h/cpp

检测器基类Detector，用于比较两个工程/文件的区别

### detector_file.h/cpp

检测器基类的单文件检测派生类，比较两个文件的区别

### detector_project.h/cpp

检测器基类的工程检测派生类，用于比较两个工程的区别

### file.h/cpp

文件基类，内含文件读取操作

### monitor.h/cpp

工程检测类的派生类，用于监测比较算法的进度输出到界面

### plagirism_detector_widget.h/cpp

Qt窗口的派生类，实现用户界面

### project.h/cpp

工程基类，内含工程文件读取操作

### strategies_file.h/cpp

文件判重算法类，计算单文件相似度

### strategies_project.h/cpp

工程判重算法类，计算工程相似度
