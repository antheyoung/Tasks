#include <iostream>
#include <opencv2/opencv.hpp>
#include "pnp.h"
#include "exchange.h"

using namespace std;
using namespace cv;

int main()
{
    VideoCapture capture;
    VideoWriter writer;
    capture.open("../兑换槽识别测试0.avi");
    capture.open("../兑换槽识别测试1.avi");
    // writer.open("识别结果0.avi", capture.get(CAP_PROP_FOURCC), 30, Size(capture.get(CAP_PROP_FRAME_WIDTH), capture.get(CAP_PROP_FRAME_HEIGHT)), true);
    writer.open("识别结果1.avi", capture.get(CAP_PROP_FOURCC), 30, Size(capture.get(CAP_PROP_FRAME_WIDTH), capture.get(CAP_PROP_FRAME_HEIGHT)), true);
    if (!capture.isOpened())
    {
        cout << "can not find ......" << endl;
        return -1;
    }
    Mat src;
    while (capture.read(src))
    {
        // 进行兑换槽识别
        Exchange my_exchange;
        my_exchange.find_corners(src);
        my_exchange.draw_contour(src);
        my_exchange.get_center(src);
        // 获取兑换槽的四个角点进行排序
        vector<Point2f> my_corners;
        my_exchange.get_corners(my_corners);
        // 使用solvepnp进行计算
        pnp pnp_message;
        get_pnpmessage(src, my_corners, &pnp_message);

        imshow("src", src);
        char key = waitKey(30);
        if (key == 27)
        {
            break;
        }
    }
    capture.release();
    destroyAllWindows();
    return 0;
}