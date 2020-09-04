/*
 * 教程来源:
 *        https://www.codeleading.com/article/32522512080/
 *
 * realsense获取影像到opencv显示流程讲解:
 *        https://makerpro.cc/2019/11/3d-sensir-how-to-catch-the-streaming-video-of-intel-realsense-in-to-opencv/
 *
 */

#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>

#define JIAJIA
//#define COUT_FPS

using namespace std;
using namespace cv;
using namespace rs2;


int main()
{
    colorizer color_map;
    pipeline pipe;      //构建一个设备的管道,容纳获取到的图像
    config cfg;         //使用非默认配置文件创建配置以配置管道
    cfg.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30);    //将所需的流添加到配置realsense
    cfg.enable_stream(RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, 30);
    pipe.start(cfg);    //指示管道使用请求的配置开始流式传输

    while(1)
    {
        frameset frames;                            // 放下几个第一帧以使自动曝光稳定
        frames = pipe.wait_for_frames();            // 等待所有配置的流生成一个帧
        frame color_frame = frames.get_color_frame(); //获取每个帧
        frame depth_frame = frames.get_depth_frame().apply_filter(color_map);

        const int depth_w=depth_frame.as<rs2::video_frame>().get_width();
        const int depth_h=depth_frame.as<rs2::video_frame>().get_height();
        const int color_w=color_frame.as<rs2::video_frame>().get_width();
        const int color_h=color_frame.as<rs2::video_frame>().get_height();//        Mat color(Size(640, 480), CV_8UC3, (void*)color_frame.get_data(), Mat::AUTO_STEP);        //从彩色图像创建OpenCV矩阵

        Mat color(Size(color_w, color_h), CV_8UC3, (void*)color_frame.get_data(), Mat::AUTO_STEP);        //从彩色图像创建OpenCV矩阵
        Mat depth(Size(depth_w,depth_h), CV_8UC3,(void*)depth_frame.get_data(),Mat::AUTO_STEP);

        imshow("depth_frame", depth);
        imshow("color_frame", color);


        int key = waitKey(1);
        if(char(key) == 27)break;

    }
    return 0;
}
