#include <iostream>                    // for standard I/O
#include <string>                      // for strings
#include <iomanip>                     // for controlling float print precision
#include <sstream>                     // string to number conversion
#include <opencv2/imgproc/imgproc.hpp> // Gaussian Blur
#include <opencv2/core/core.hpp>       // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/highgui/highgui.hpp> // OpenCV window I/O
#include <opencv2/imgproc/imgproc_c.h>

#include <opencv2\video\background_segm.hpp>
#include <opencv2\opencv.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include <math.h>
#include <ctime>
#include <Windows.h>

using namespace cv;
using namespace std;

/*
多种模式
mode = 0 主界面
mode = 1 画板
mode = 2 识别图像
mode = 3 自拍 人脸截图
mode = 4 鼠标动作

mode 0 主界面
三种模式
向右 进入画板画图 ->mode 1
拳头 进入人脸识别 ->mode 3
手掌 进入鼠标动作 ->mode 4

mode 1 画板
画轨迹
向右 进入识别图像 ->mode 2
拳头 画轨迹
手掌 清空画板 重新画

mode 2 识别图像
将画出的轨迹拟合 估计形状并输出结果
向右 返回主界面 ->mode 0
拳头 将结果加载入队列 用于鼠标动作
手掌 返回mode 1 不满意重新画 / 继续添加结果载入队列

识别向右来切换模式 默认顺序为mode 0 -> mode 1 -> mode 2

mode 3 自拍 人脸识别
识别人脸然后可以选择截图
向右 返回主界面 ->mode 0
右手掌 将脸部截图保存至文件夹

mode 4 光标动作
识别提前存储的动作(图形) 根据存储的不同的数字 进行不同的动作
Tri--1
Squa--2
Rect--3
Pentagon--4
Circle--5

向右 下一个动作
1 控制光标动作时控制光标

*/

// define 定义
CascadeClassifier Rdirection_Cascade; //识别向右
CascadeClassifier Ldirection_Cascade; //识别向左
CascadeClassifier Rpalm_Cascade;      //识别右手掌
CascadeClassifier Lpalm_Cascade;      //识别左手掌
CascadeClassifier Fist_Cascade;       //识别拳头
CascadeClassifier Face_Cascade;       //识别人脸

Mat img;  //摄像头获取的图像
Mat show; //识别之后的图像

vector<Rect> fists;
vector<Rect> rdirections;
vector<Rect> rpalms;
vector<Rect> faces;
vector<vector<int>> centers;
queue<int> movements;

int mode;
int Rdirection_Count;
int Fist_Count;
int Rpalm_Count;
int Recognization_Count;
int Face_Photo_Count;

int shape2move;
/*
Tri--1
Squa--2
Rect--3
Pentagon--4
Circle--5
*/

POINT p;

//形状判断函数
void getContours(Mat imgDil, Mat img, Mat revise)
{

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    findContours(imgDil, contours, hierarchy, 0, 2);
    // drawContours(img, contours, -1, Scalar(255, 0, 255), 2); //-1 means all

    for (int i = 0; i < contours.size(); i++)
    {
        string objectType;
        int area = contourArea(contours[i]);
        cout << area << endl;

        vector<vector<Point>> conPoly(contours.size());
        vector<Rect> boundRect(contours.size());

        if (area > 1000)
        {
            float peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i], 0.038 * peri, true);
            drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
            // cout << conPoly[i].size() << endl;
            boundRect[i] = boundingRect(conPoly[i]);
            rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);

            int objCor = (int)conPoly[i].size();
            cout << "The numbers of angles" << objCor << endl;
            if (objCor == 3)
            {
                objectType = "Tri";
                shape2move = 1;
                drawContours(revise, conPoly, i, Scalar(255, 0, 255), 2);
            }
            else if (objCor == 4)
            {
                float aspRatio = (float)boundRect[i].width / boundRect[i].height;
                cout << aspRatio << endl;
                if (aspRatio > 0.8 && aspRatio < 1.2)
                {
                    objectType = "Square";
                    shape2move = 2;
                    drawContours(revise, conPoly, i, Scalar(255, 0, 255), 2);
                }
                else
                {
                    objectType = "Rect";
                    shape2move = 3;
                    drawContours(revise, conPoly, i, Scalar(255, 0, 255), 2);
                }
            }
            else if (objCor == 5)
            {
                objectType = "Pentagon";
                shape2move = 4;
                drawContours(revise, conPoly, i, Scalar(255, 0, 255), 2);
            }
            else if (objCor >= 7)
            {
                objectType = "Circle";
                shape2move = 5;
                drawContours(revise, conPoly, i, Scalar(255, 0, 255), 2);
            }

            putText(img, objectType, {boundRect[i].x, boundRect[i].y - 5}, FONT_HERSHEY_PLAIN, 1, Scalar(0, 69, 255), 1.5);
        }
    }
}

int main()
{
    //调用摄像头
    VideoCapture cap(0);

    //载入拳头模型
    Fist_Cascade.load("own_project/fist.xml");
    if (Fist_Cascade.empty())
    {
        std::cout << "fist.xml file not loaded" << endl;
    }

    //载入向右模型
    Rdirection_Cascade.load("own_project/right.xml");
    if (Rdirection_Cascade.empty())
    {
        std::cout << "right.xml file not loaded" << endl;
    }

    //载入右手掌模型
    Rpalm_Cascade.load("own_project/rpalm.xml");
    if (Rpalm_Cascade.empty())
    {
        std::cout << "rpalm.xml file not loaded" << endl;
    }

    //载入人脸模型
    Face_Cascade.load("own_project/haarcascade_frontalface_alt.xml");
    if (Face_Cascade.empty())
    {
        std::cout << "haarcascade_frontalface_alt.xml file not loaded" << endl;
    }

    Mat imgdraw(480, 640, CV_8UC3, Scalar(255, 255, 255));
    Mat revise(480, 640, CV_8UC3, Scalar(255, 255, 255));
    Mat Imgdraw_y;
    Mat Image_y;
    Mat imgCropFace_y;

    //初始化参数
    mode = 0;
    Rdirection_Count = 0;
    Fist_Count = 0;
    Rpalm_Count = 0;
    Recognization_Count = 0;
    Face_Photo_Count = 0;
    shape2move = 0;

    while (true)
    {
        cap.read(img);

        Fist_Cascade.detectMultiScale(img, fists, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, cv::Size(30, 30));             //识别拳头
        Rdirection_Cascade.detectMultiScale(img, rdirections, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, cv::Size(30, 30)); //识别向右
        Rpalm_Cascade.detectMultiScale(img, rpalms, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, cv::Size(30, 30));           //识别右掌
        Face_Cascade.detectMultiScale(img, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, cv::Size(30, 30));             //识别人脸

        //模式0 开始界面
        if (mode == 0)
        {
            //识别右向
            for (int i = 0; i < rdirections.size(); i++)
            {
                //识别右向 用粉色长方形框起来
                rectangle(img, rdirections[i].tl(), rdirections[i].br(), Scalar(203, 192, 255), 3);
            }
            //识别拳头
            for (int i = 0; i < fists.size(); i++)
            {
                //识别拳头 用紫色长方形框起来
                rectangle(img, fists[i].tl(), fists[i].br(), Scalar(255, 0, 255), 3);
            }
            //识别右手掌
            for (int i = 0; i < rpalms.size(); i++)
            {
                //识别右手掌 用蓝色长方形框起来
                rectangle(img, rpalms[i].tl(), rpalms[i].br(), Scalar(230, 216, 173), 3);
            }

            //识别到右向 则Rdirection_Count++
            //然后判断次数进入mode 1
            if (rdirections.size() != 0)
            {
                Rdirection_Count++;
                std::cout << "Rdirection_Count: " << Rdirection_Count << endl;
            }
            if (Rdirection_Count == 15) //识别到一定次数后 转换成mode 1:画轨迹
            {
                mode = 1;
                Rdirection_Count = 0; //清空Rdirection_Count 便于下一次识别
            }

            //识别到拳头 则Fist_Count++
            //然后判断次数进入mode 3
            if (fists.size() != 0)
            {
                Fist_Count++;
                std::cout << "Fist_Count: " << Fist_Count << endl;
            }
            if (Fist_Count == 15) //识别到一定次数后 转换成mode 3:人脸识别
            {
                mode = 3;
                Fist_Count = 0; //清空Fist_Count 便于下一次识别
            }

            //识别到右手掌 则Rpalm_Count++
            //然后判断次数进入mode 4
            if (rpalms.size() != 0)
            {
                Rpalm_Count++;
                std::cout << "Rpalm_Count: " << Rpalm_Count << endl;
            }
            if (Rpalm_Count == 15) //识别到一定次数后 转换成mode 4:鼠标动作
            {
                mode = 4;
                Rpalm_Count = 0; //清空Rpalm_Count 便于下一次识别
            }

            flip(img, Image_y, 1); //将图像沿y轴翻转，即镜像
            putText(Image_y, "show your hand", Point(200, 50), FONT_HERSHEY_PLAIN, 2, Scalar(0, 255, 0), 3);
            imshow("Img", Image_y);
            moveWindow("Img", 100, 100);
        }

        //模式1 画轨迹
        if (mode == 1)
        {

            //画轨迹部分 img
            for (int i = 0; i < fists.size(); i++)
            {
                //识别拳头 用紫色长方形框起来
                rectangle(img, fists[i].tl(), fists[i].br(), Scalar(255, 0, 255), 3);

                //找到长方体中心点
                Point point;
                point.x = (fists[i].tl().x + fists[i].br().x) * 0.5;
                point.y = (fists[i].tl().y + fists[i].br().y) * 0.5;

                //显示中心点
                circle(img, point, 5, Scalar(0, 69, 255), FILLED);
                //存点坐标
                centers.push_back({point.x, point.y, i});

                // cout << "x:" << point.x << " y: " << point.y << endl;
                // if (centers.size() == 0)
                // {
                //     centers.push_back({point.x, point.y, i});
                // }
                // else if (sqrt((point.x - centers[centers.size()-1][0])^2+(point.y - centers[centers.size()-1][1])^2) < 70 )
                // {
                //     centers.push_back({point.x, point.y, i});
                // }
            }

            //轨迹显示 imgdraw
            for (int i = 1; i < centers.size(); i++)
            {
                //画轨迹 输出到 imgdraw显示
                line(imgdraw, Point(centers[i][0], centers[i][1]), Point(centers[i - 1][0], centers[i - 1][1]), Scalar(255, 0, 0), 5);
            }

            //识别右向
            for (int i = 0; i < rdirections.size(); i++)
            {
                //识别右向 用粉色长方形框起来
                rectangle(img, rdirections[i].tl(), rdirections[i].br(), Scalar(203, 192, 255), 3);
            }
            //识别右手掌
            for (int i = 0; i < rpalms.size(); i++)
            {
                //识别右手掌 用蓝色长方形框起来
                rectangle(img, rpalms[i].tl(), rpalms[i].br(), Scalar(230, 216, 173), 3);
            }

            //向右识别判断
            if (rdirections.size() != 0) //识别到向右 则Rdirection_Count++
            {
                Rdirection_Count++;
                std::cout << "Rdirection_Count: " << Rdirection_Count << endl;
            }
            if (Rdirection_Count == 15) //识别到一定次数后 转换成mode 2:识别图像
            {
                mode = 2;
                Rdirection_Count = 0; //清空 便于下一次识别
            }

            //右手掌识别判断
            if (rpalms.size() != 0) //识别到向右 则Rdirection_Count++
            {
                Rpalm_Count++;
                std::cout << "Rpalm_Count: " << Rpalm_Count << endl;
            }
            if (Rpalm_Count == 15) //清空画板
            {
                centers.clear(); //清空 centers 里面的点 再次画图
                // cout << "size of centers:" << centers.size() << endl;
                rectangle(imgdraw, Point(0, 0), Point(640, 480), Scalar(255, 255, 255), FILLED);
                Rpalm_Count = 0; //清空 便于下一次识别
            }

            flip(img, Image_y, 1);       //将图像沿y轴翻转，即镜像
            flip(imgdraw, Imgdraw_y, 1); //将图像沿y轴翻转，即镜像

            putText(Image_y, "draw your shape", Point(200, 50), FONT_HERSHEY_PLAIN, 2, Scalar(0, 255, 0), 3);

            // imshow("Image", img);
            // imshow("draw", imgdraw);
            imshow("Img", Image_y);       //摄像头图像
            imshow("Imgdraw", Imgdraw_y); //画的图

            moveWindow("Img", 100, 100);
            moveWindow("Imgdraw", 800, 50);
        }

        //模式2 识别图像
        if (mode == 2)
        {
            //如果没有话则重画
            if (centers.size() <= 2)
            {
                mode = 1;
                cout << "No Point! Back to Mode 1" << endl;
            }
            else
            {
                //识别图像
                if (Recognization_Count == 0)
                {
                    // 连接起始点和终点 封闭图形便于识别形状
                    line(imgdraw, Point(centers[0][0], centers[0][1]), Point(centers[centers.size() - 1][0], centers[centers.size() - 1][1]), Scalar(255, 0, 0), 5);

                    flip(imgdraw, show, 1);
                    // Processing 预处理
                    Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;
                    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));

                    cvtColor(show, imgGray, COLOR_BGR2GRAY);          //灰度图像
                    GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0); //高斯模糊
                    Canny(imgBlur, imgCanny, 25, 75);
                    dilate(imgCanny, imgDil, kernel);

                    getContours(imgDil, show, revise);

                    Recognization_Count++;
                }

                //识别右向
                for (int i = 0; i < rdirections.size(); i++)
                {
                    //识别右向 用粉色长方形框起来
                    rectangle(img, rdirections[i].tl(), rdirections[i].br(), Scalar(203, 192, 255), 3);
                }
                //识别拳头
                for (int i = 0; i < fists.size(); i++)
                {
                    //识别拳头 用紫色长方形框起来
                    rectangle(img, fists[i].tl(), fists[i].br(), Scalar(255, 0, 255), 3);
                }
                //识别右手掌
                for (int i = 0; i < rpalms.size(); i++)
                {
                    //识别右手掌 用蓝色长方形框起来
                    rectangle(img, rpalms[i].tl(), rpalms[i].br(), Scalar(230, 216, 173), 3);
                }

                //识别到右向 则Rdirection_Count++
                if (rdirections.size() != 0)
                {
                    Rdirection_Count++;
                    std::cout << Rdirection_Count << endl;
                }
                //识别到拳头 则Fist_Count++
                if (fists.size() != 0)
                {
                    Fist_Count++;
                    std::cout << "Fist_Count: " << Fist_Count << endl;
                }
                //识别到右手掌 则Rpalm_Count++
                if (rpalms.size() != 0)
                {
                    Rpalm_Count++;
                    std::cout << "Rpalm_Count: " << Rpalm_Count << endl;
                }

                flip(img, Image_y, 1);

                string size = "queue size: " + to_string(movements.size());
                putText(Image_y, size, Point(300, 50), FONT_HERSHEY_PLAIN, 2, Scalar(0, 255, 255), 3);

                putText(show, "Recogniztion", Point(200, 50), FONT_HERSHEY_PLAIN, 2, Scalar(0, 255, 0), 3);
                imshow("Img", Image_y);
                imshow("final", show);
                imshow("Revise", revise);

                //如果认为识别的图形符合要求
                //拳头
                //将图形结果 int 存入队列
                if (Fist_Count == 15)
                {
                    if (shape2move != 0)
                    {
                        movements.push(shape2move);
                        cout << "queue.size: " << movements.size() << endl;
                    }

                    // movement.push_back( int );

                    Fist_Count = 0; //清空Count

                    //初始化参数
                    Rpalm_Count = 0;
                    Rdirection_Count = 0;
                }

                //如果认为识别的图形不符合要求
                //或者想要继续添加结果载入队列
                //右手掌
                //返回mode 1 重新画(不返回mode 0)
                if (Rpalm_Count == 15)
                {
                    mode = 1;
                    Rpalm_Count = 0; //清空 便于下一次识别

                    //初始化参数
                    Rdirection_Count = 0;
                    Fist_Count = 0;
                    Recognization_Count = 0;
                    shape2move = 0;

                    //清空imgs
                    rectangle(img, Point(0, 0), Point(640, 480), Scalar(255, 255, 255), FILLED);
                    rectangle(imgdraw, Point(0, 0), Point(640, 480), Scalar(255, 255, 255), FILLED);
                    rectangle(Image_y, Point(0, 0), Point(640, 480), Scalar(255, 255, 255), FILLED);
                    rectangle(Imgdraw_y, Point(0, 0), Point(640, 480), Scalar(255, 255, 255), FILLED);
                    rectangle(show, Point(0, 0), Point(640, 480), Scalar(255, 255, 255), FILLED);
                    rectangle(revise, Point(0, 0), Point(640, 480), Scalar(255, 255, 255), FILLED);

                    //清空vectors
                    fists.clear();
                    rdirections.clear();
                    rpalms.clear();
                    centers.clear();

                    destroyWindow("final");
                    destroyWindow("Revise");
                }

                //右向计数
                //识别到一定次数后 转换成mode 0
                if (Rdirection_Count == 15)
                {
                    mode = 0;
                    Rdirection_Count = 0; //清空 便于下一次识别

                    //初始化参数
                    Rpalm_Count = 0;
                    Recognization_Count = 0;
                    shape2move = 0;

                    //清空imgs
                    rectangle(img, Point(0, 0), Point(640, 480), Scalar(255, 255, 255), FILLED);
                    rectangle(imgdraw, Point(0, 0), Point(640, 480), Scalar(255, 255, 255), FILLED);
                    rectangle(Image_y, Point(0, 0), Point(640, 480), Scalar(255, 255, 255), FILLED);
                    rectangle(Imgdraw_y, Point(0, 0), Point(640, 480), Scalar(255, 255, 255), FILLED);
                    rectangle(show, Point(0, 0), Point(640, 480), Scalar(255, 255, 255), FILLED);
                    rectangle(revise, Point(0, 0), Point(640, 480), Scalar(255, 255, 255), FILLED);

                    //清空vectors
                    fists.clear();
                    rdirections.clear();
                    rpalms.clear();
                    centers.clear();

                    //关闭窗口
                    destroyAllWindows();
                }
            }
        }

        //模式3 人脸识别自拍
        if (mode == 3)
        {
            //防止把长方形框截入照片中
            Mat imgCopy = img.clone();

            //识别人脸
            for (int i = 0; i < faces.size(); i++)
            {
                //识别人脸 用黄色长方形框起来
                rectangle(img, Point(faces[i].tl().x - 50, faces[i].tl().y - 50), faces[i].br(), Scalar(0, 255, 255), 3);
            }
            //识别右手掌
            for (int i = 0; i < rpalms.size(); i++)
            {
                //识别右手掌 用蓝色长方形框起来
                rectangle(img, rpalms[i].tl(), rpalms[i].br(), Scalar(230, 216, 173), 3);
            }
            //识别右向
            for (int i = 0; i < rdirections.size(); i++)
            {
                //识别右向 用粉色长方形框起来
                rectangle(img, rdirections[i].tl(), rdirections[i].br(), Scalar(203, 192, 255), 3);
            }

            //识别到右手掌 则Rpalm_Count++
            //然后判断次数进行截图保存
            if (rpalms.size() != 0)
            {
                Rpalm_Count++;
                std::cout << "Rpalm_Count: " << Rpalm_Count << endl;
            }
            if (Rpalm_Count == 15) //识别到一定次数后 截图保存
            {
                for (int i = 0; i < faces.size(); i++)
                {
                    Mat imgCropFace = imgCopy(faces[i]);
                    flip(imgCropFace, imgCropFace_y, 1); //反转
                    imwrite("own_project/face_photos/face_" + to_string(Face_Photo_Count) + "_" + to_string(i) + ".png", imgCropFace_y);
                    Face_Photo_Count++;
                }

                Rpalm_Count = 0; //清空Rpalm_Count 便于下一次识别
            }

            flip(img, Image_y, 1); //将图像沿y轴翻转，即镜像

            putText(Image_y, "face detection", Point(200, 50), FONT_HERSHEY_PLAIN, 2, Scalar(0, 255, 0), 3);

            imshow("Img", Image_y);
            moveWindow("Img", 100, 100);

            //向右识别判断
            //识别到向右 则Rdirection_Count++
            if (rdirections.size() != 0) //识别到向右 则Rdirection_Count++
            {
                Rdirection_Count++;
                std::cout << "Rdirection_Count: " << Rdirection_Count << endl;
            }
            //识别到一定次数后 转换成mode 0
            if (Rdirection_Count == 15)
            {
                mode = 0;
                Rdirection_Count = 0;

                //初始化参数
                Rpalm_Count = 0;
                faces.clear();

                //关闭窗口
                destroyAllWindows();
            }
        }

        //模式4 光标动作
        if (mode == 4)
        {
            if (movements.size() != 0)
            {
                if (movements.front() == 1)
                {

                    //画轨迹部分 img
                    for (int i = 0; i < fists.size(); i++)
                    {
                        //识别拳头 用紫色长方形框起来
                        rectangle(img, fists[i].tl(), fists[i].br(), Scalar(255, 0, 255), 3);

                        //找到长方体中心点
                        Point point;
                        point.x = (fists[i].tl().x + fists[i].br().x) * 0.5;
                        point.y = (fists[i].tl().y + fists[i].br().y) * 0.5;

                        //显示中心点
                        circle(img, point, 5, Scalar(0, 69, 255), FILLED);
                        //存点坐标
                        centers.push_back({point.x, point.y, i});
                    }

                    //识别右向
                    for (int i = 0; i < rdirections.size(); i++)
                    {
                        //识别右向 用粉色长方形框起来
                        rectangle(img, rdirections[i].tl(), rdirections[i].br(), Scalar(203, 192, 255), 3);
                    }
                    //识别右手掌
                    for (int i = 0; i < rpalms.size(); i++)
                    {
                        //识别右手掌 用蓝色长方形框起来
                        rectangle(img, rpalms[i].tl(), rpalms[i].br(), Scalar(230, 216, 173), 3);
                    }

                    flip(img, Image_y, 1); //将图像沿y轴翻转，即镜像

                    string size = "queue size: " + to_string(movements.size());
                    putText(Image_y, size, Point(300, 50), FONT_HERSHEY_PLAIN, 2, Scalar(0, 255, 255), 3);

                    imshow("Img", Image_y); //摄像头图像
                    moveWindow("Img", 100, 100);

                    for (int i = 1; i < centers.size(); i++)
                    {
                        //鼠标控制移动
                        SetCursorPos(p.x + (-centers[i][0] + centers[i - 1][0]) / 2, p.y + (centers[i][1] - centers[i - 1][1]) / 2);
                        GetCursorPos(&p);
                    }
                    cout << "1光标移动" << endl;

                                        //向右识别判断
                    if (rdirections.size() != 0) //识别到向右 则Rdirection_Count++
                    {
                        Rdirection_Count++;
                        std::cout << "Rdirection_Count: " << Rdirection_Count << endl;
                    }
                    if (Rdirection_Count == 15) //识别到一定次数后 转换成mode
                    {
                        mode = 4;
                        Rdirection_Count = 0; //清空 便于下一次识别
                        movements.pop();
                        centers.clear();
                    }
                    //右手掌识别判断
                    if (rpalms.size() != 0) //识别到向右 则Rdirection_Count++
                    {
                        Rpalm_Count++;
                        std::cout << "Rpalm_Count: " << Rpalm_Count << endl;
                    }
                    if (Rpalm_Count == 15) //清空画板
                    {
                        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0); //模拟鼠标键按下
                        Sleep(10);                                     //要留给某些应用的反应时间
                        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);  //模拟鼠标键抬起
                        Rpalm_Count = 0; 
                    }
                }
                if (movements.front() == 2)
                {
                    keybd_event(VK_LWIN, 0, 0, 0);
                    keybd_event(VK_LSHIFT, 0, 0, 0);
                    keybd_event(83, 0, 0, 0);
                    keybd_event(VK_LWIN, 0, 2, 0);
                    keybd_event(VK_LSHIFT, 0, 2, 0);
                    keybd_event(83, 0, 2, 0); //快速截图
                    cout << "2截图" << endl;
                    movements.pop();
                }
                if (movements.front() == 3)
                {
                    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0); //模拟鼠标键按下
                    Sleep(10);                                     //要留给某些应用的反应时间
                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);   //模拟鼠标键抬起
                    cout << "3单击" << endl;
                    movements.pop();
                }
                if (movements.front() == 4)
                {
                    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0); //模拟鼠标键按下
                    Sleep(10);                                     //要留给某些应用的反应时间
                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);   //模拟鼠标键抬起
                    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0); //模拟鼠标键按下
                    Sleep(10);                                     //要留给某些应用的反应时间
                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);   //模拟鼠标键抬起
                    cout << "4双击" << endl;
                    movements.pop();
                }
                if (movements.front() == 5)
                {
                    system("C:\\Windows\\system32\\osk.exe"); //打开键盘
                    cout << "5虚拟键盘" << endl;
                    movements.pop();
                }
            }
            else
            {
                cout << "No Movement in queue" << endl;
                mode = 0;
                destroyAllWindows();
            }
        }

        waitKey(25);
    }
    return 0;
}