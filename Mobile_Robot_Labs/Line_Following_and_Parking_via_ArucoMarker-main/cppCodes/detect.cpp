/** MIT License
Copyright (c) 2017 Sudarshan Raghunathan
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *
 *@copyright Copyright 2017 Sudarshan Raghunathan
 *@file   detect.cpp
 *@author Sudarshan Raghunathan
 *@brief  Ros Nod to subscribe to turtlebot images and perform image processing to detect line
 */
#include <cv_bridge/cv_bridge.h>
#include <cstdlib>
#include <string>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"
#include "ros/ros.h"
#include "ros/console.h"
#include "linedetect.hpp"
#include "line_follower_turtlebot/pos.h"
#include <opencv2/aruco/charuco.hpp>
#include "opencv2/imgproc.hpp"
#include <iostream>
#include "geometry_msgs/PoseStamped.h"
#include <vector>



using namespace cv;
using namespace std;

/**
 *@brief Main function that reads image from the turtlebot and provides direction to move using image processing
 *@param argc is the number of arguments of the main function
 *@param argv is the array of arugments
 *@return 0
*/

// void LineDetect::imageCallback(const sensor_msgs::CompressedImagePtr& msg) {
//   cv_bridge::CvImagePtr cv_ptr;
//   try {
//     cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
//     this->img = cv_ptr->image;
//     cv::waitKey(30);
//   }
//   catch (cv_bridge::Exception& e) {
//     ROS_ERROR("Could not convert from '' to 'bgr8'.");
//   }
// }

_Float64 aru_pose[7];

// void aruCallback(const geometry_msgs::PoseStampedPtr& msg){
//     aru_pose[0]=msg->pose.position.x;
//     aru_pose[1]=msg->pose.position.y;
//     aru_pose[2]=msg->pose.position.z;
// }

void aruCallback(const geometry_msgs::PoseStamped & msg){
    // ROS_INFO("Image pose: x:%0.6f, y:%0.6f",msg.pose.position.x,msg.pose.position.y);
    aru_pose[0] = msg.pose.position.x;
    aru_pose[1] = msg.pose.position.y;
    aru_pose[2] = msg.pose.position.z;
    aru_pose[3] = msg.pose.orientation.w;
    aru_pose[4] = msg.pose.orientation.x;
    aru_pose[5] = msg.pose.orientation.y;
    aru_pose[6] = msg.pose.orientation.z; 
};


// int find_aru(){
//     if(aru_pose[0]==1&&aru_pose[1]==1){
//         //not find arucode
//         return 1;
//     }else{
//         //find the arucode
//         return 0;
//     }
// };




int main(int argc, char **argv) {
    // Initializing node and object
    ros::init(argc, argv, "detection");

    aru_pose[0] = 1;
    aru_pose[1] = 1;
    aru_pose[2] = 1;
    aru_pose[3] = 1;
    aru_pose[4] = 1;
    aru_pose[5] = 1;
    aru_pose[6] = 1; 

    ros::NodeHandle n;

    ros::NodeHandle aru;

    LineDetect det;
    det.aru_pose_ptr=&aru_pose[0];
    
    // Creating Publisher and subscriber
    ros::Subscriber sub = n.subscribe("/raspicam_node/image/compressed",
        1, &LineDetect::imageCallback, &det);

    ros::Subscriber sub_aru = aru.subscribe("/aruco_single/pose",1,&aruCallback);

    ros::Publisher dirPub = n.advertise<line_follower_turtlebot::pos>("direction", 1);
    line_follower_turtlebot::pos msg;

    while (ros::ok()) {
        if (!det.img.empty()) {
            // if(find_aru()==1){
            //     // not find arucode
            //     // Perform image processing
            //     det.img_filt = det.Gauss(det.img);
            //     msg.direction = det.colorthresh(det.img_filt);
            //     // Publish direction message
            //     dirPub.publish(msg);
            // }else{
            //     // find arucode, and now start parking
            //     msg.direction = det.parking();
            //     dirPub.publish(msg);
            //     // msg.direction=det.stop();
            //     // dirPub.publish(msg);
            // }

            
            // Perform image processing
            det.img_filt = det.Gauss(det.img);
            msg.direction = det.colorthresh(det.img_filt);
            // Publish direction message
            dirPub.publish(msg);
        }
        ros::spinOnce();          
    }
    	
    cv::destroyWindow("Turtlebot View");
}
