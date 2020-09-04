## 一,API说明
１．imshow() 在指定的窗口中显示图像
　　　头文件：#include <opencv2/highgui.hpp>
　　　函数原型：void cv::imshow(const String &winname,　　InputArray  mat) 
　　　　　　　　　　　　　参数１：现实的窗口名
　　　　　　　　　　　　　参数２：需要显示的图像

２．waitkey(int delay=0) 不断刷新图像，频率时间为delay ,单位是ｍｓ

3． mat 是一个图像容器类，也是一个一般矩阵类      
    https://blog.csdn.net/ahafg/article/details/49309765
