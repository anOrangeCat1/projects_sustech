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
*@file linedetect.cpp
*@author Sudarshan Raghunathan
*@brief  Class linedetect's function definitions
*/
#include "linedetect.hpp"
#include <cv_bridge/cv_bridge.h>
#include <cstdlib>
#include <string>
#include <opencv2/highgui/highgui.hpp>
#include "ros/ros.h"
#include "opencv2/opencv.hpp"
#include "ros/console.h"
#include "line_follower_turtlebot/pos.h"

void LineDetect::imageCallback(const sensor_msgs::CompressedImagePtr& msg) {
  cv_bridge::CvImagePtr cv_ptr;
  try {
    cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    img = cv_ptr->image;
    cv::waitKey(30);
  }
  catch (cv_bridge::Exception& e) {
    ROS_ERROR("Could not convert from '' to 'bgr8'.");
  }
}

cv::Mat LineDetect::Gauss(cv::Mat input) {
  cv::Mat output;
// Applying Gaussian Filter
  cv::GaussianBlur(input, output, cv::Size(3, 3), 0.1, 0.1);
  return output;
}


int LineDetect::colorthresh(cv::Mat input) {
  // Initializaing variables
  cv::Size s = input.size();
  std::vector<std::vector<cv::Point> > v;
  auto w = s.width;
  auto h = s.height;
  auto c_x = 0.0;
  // Detect all objects within the HSV range
  cv::cvtColor(input, LineDetect::img_hsv, CV_BGR2HSV);
  // LineDetect::LowerYellow = {20, 100, 100};
  // LineDetect::UpperYellow = {30, 255, 255};
  // LineDetect::LowerYellow = {0, 0, 221};
  // LineDetect::UpperYellow = {180, 30, 255};
  // in this case, yellow is black
  LineDetect::LowerYellow = {0, 0, 0};
  LineDetect::UpperYellow = {180, 255, 65};
  cv::inRange(LineDetect::img_hsv, LowerYellow,
   UpperYellow, LineDetect::img_mask);
  img_mask(cv::Rect(0, 0, w, 0.88*h)) = 0;
  // Find contours for better visualization
  cv::findContours(LineDetect::img_mask, v, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
  // If contours exist add a bounding
  // Choosing contours with maximum area
  if (v.size() != 0) {
  auto area = 0;
  auto idx = 0;
  auto count = 0;
  while (count < v.size()) {
    if (area < v[count].size()) {
       idx = count;
       area = v[count].size();
    }
    count++;
  }
  cv::Rect rect = boundingRect(v[idx]);
  cv::Point pt1, pt2, pt3;
  pt1.x = rect.x;
  pt1.y = rect.y;
  pt2.x = rect.x + rect.width;
  pt2.y = rect.y + rect.height;
  pt3.x = pt1.x+5;
  pt3.y = pt1.y-5;
  // Drawing the rectangle using points obtained
  rectangle(input, pt1, pt2, CV_RGB(255, 0, 0), 2);
  // Inserting text box
  cv::putText(input, "Line Detected", pt3,
    CV_FONT_HERSHEY_COMPLEX, 1, CV_RGB(255, 0, 0));
  }
  // Mask image to limit the future turns affecting the output

  img_mask(cv::Rect(0.73*w, 0, 0.27*w, h)) = 0;
  img_mask(cv::Rect(0, 0, 0.27*w, h)) = 0;
  imshow("img_mask2",img_mask);
  
  // Perform centroid detection of line
  cv::Moments M = cv::moments(LineDetect::img_mask);
  //imshow("mask",img_mask);
  if (M.m00 > 0) {
    cv::Point p1(M.m10/M.m00, M.m01/M.m00);
    cv::circle(LineDetect::img_mask, p1, 5, cv::Scalar(155, 200, 0), -1);
  }
  c_x = M.m10/M.m00;
  // Tolerance to chooise directions
  auto tol = 3;
  auto count = cv::countNonZero(img_mask);
  // Turn left if centroid is to the left of the image center minus tolerance
  // Turn right if centroid is to the right of the image center plus tolerance
  // Go straight if centroid is near image center

  if(aru_pose_ptr[0]==1){
    // ROS_INFO("Line Following");
    // not find arucode, line following
    if (c_x < w/2-tol) {
    LineDetect::dir = 0;
    } else if (c_x > w/2+tol) {
    LineDetect::dir = 2;
    } else {
    LineDetect::dir = 1;
    }
    // Search if no line detected
    if (count == 0) {
    // ROS_INFO("Searching!!!!");
    LineDetect::dir = 3;
    }
  }else{
    //ROS_INFO("Image pose: x:%0.6f, z:%0.6f,orientation.z:%0.6f",aru_pose_ptr[0],aru_pose_ptr[2],aru_pose_ptr[6]);
    // pose.x != 1 , which means finding the code, parking
    if(aru_pose_ptr[0]*aru_pose_ptr[0]+aru_pose_ptr[2]*aru_pose_ptr[2] < 0.17*0.17){
      //ROS_INFO("STOP!!!");
      // distance is small enough, stop parking
      LineDetect::dir = 4;
    }else{
      // position x -- [0] and orientation z -- [6]

      //[0]>0, turn right, [0]<0, turn left
      //[6]<0, turn right, [6]>0, turn left
      // distance is large, keep parking
      // dir==5, turn left; dir==6, turn right

      float orientation_z = 0.005;
      float position_x = 0.005;

      


      // if(aru_pose_ptr[6]<-orientation_z && aru_pose_ptr[0]>position_x){
      //   LineDetect::dir = 5;
      // }else if(aru_pose_ptr[6]>orientation_z && aru_pose_ptr[0]>position_x){
      //   LineDetect::dir = 5;
      // }else if((aru_pose_ptr[6]>orientation_z &&aru_pose_ptr[6]>orientation_z) && aru_pose_ptr[0]>0.02){
      //   LineDetect::dir = 5;  
      // }else if(aru_pose_ptr[6]>orientation_z && aru_pose_ptr[0]>position_x){
      //   LineDetect::dir = 6;
      // }else if(aru_pose_ptr[6]>orientation_z && aru_pose_ptr[0]>position_x){
      //   LineDetect::dir = 6;
      // }else if(aru_pose_ptr[6]>orientation_z && aru_pose_ptr[0]>position_x){
      //   LineDetect::dir = 6;
      // }else if(aru_pose_ptr[6]>orientation_z && aru_pose_ptr[0]>position_x){
      //   LineDetect::dir = 5;
      // }else if(aru_pose_ptr[6]>orientation_z && aru_pose_ptr[0]>position_x){
      //   LineDetect::dir = 6;
      // }else if(aru_pose_ptr[6]>orientation_z && aru_pose_ptr[0]>position_x){
      //   LineDetect::dir = 1;
      // }  



      // this!!!
      // if(aru_pose_ptr[6]>orientation_z){
      //   //left
      //   LineDetect::dir = 5;
      // }else if(aru_pose_ptr[6]< -orientation_z){
      //   //right
      //   LineDetect::dir = 6;
      // }else{
      //   if(aru_pose_ptr[0]>position_x){
      //     //right
      //     LineDetect::dir = 6;
      //   }else if(aru_pose_ptr[0]<-position_x){
      //     //left
      //     LineDetect::dir = 5;
      //   }else{
      //   LineDetect::dir = 7;
      // }}

      
        //only consider position.x
      if(aru_pose_ptr[0]>position_x){
        //turn right
        LineDetect::dir = 6;
      }else if(aru_pose_ptr[0]<-position_x){
        //turn left
        LineDetect::dir = 5;
      }else{
        //go straight
        LineDetect::dir = 7;
      }
        
      

      
      
      
      





























      // if(aru_pose_ptr[6]>0.03){
      //   //turn right
      //   //ROS_INFO("position.x>0.02");
      //   LineDetect::dir = 5;
      // }else if(aru_pose_ptr[6]<-0.03){
      //   //turn left
      //   //ROS_INFO("position.x<-0.02");
      //   LineDetect::dir = 6;
      // }else{
      //   //ROS_INFO("x is ok");
      //   if(aru_pose_ptr[0]>0.02){
      //   // turn left
      //   //ROS_INFO("000");
      //   LineDetect::dir = 5;
      //   }else if(aru_pose_ptr[0]<-0.02){
      //   // turn right
      //   //ROS_INFO("222");
      //   LineDetect::dir = 6;
      //   }else{
      //   // go straight
      //   //ROS_INFO("111");
      //   LineDetect::dir = 1;
      //   }
      // }

      
    }
    
  }
  // Output images viewed by the turtlebot
  cv::namedWindow("Turtlebot View");
  imshow("Turtlebot View", input);
  return LineDetect::dir;
}

// 320 240

// int LineDetect::stop(){
//   return LineDetect::dir = 4;
// }

// int LineDetect::parking(){
//   // ROS_INFO("z:%0.6f",aru_pose_ptr[6]);
//   // Judge the distance, and if the distance is smaller than 0.05m, stop the robot
//   if(aru_pose_ptr[0]*aru_pose_ptr[0]+aru_pose_ptr[2]*aru_pose_ptr[2] < 0.05*0.05){
//     // distance is small, stop
//     LineDetect::dir = 4;
//   }else{
//     // parking
//     if(aru_pose_ptr[6]>0){
//       // turn left
//       LineDetect::dir == 0;
//     }else if(aru_pose_ptr[6]<0){
//       // turn right
//       LineDetect::dir == 2;
//     }else{
//       // go straight
//       LineDetect::dir == 1;
//     }
//   }
  

//   return LineDetect::dir;
// }
