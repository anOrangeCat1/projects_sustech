## WYXMJL-Line_Following_and_Parking_via_ArucoMarker
This is the lab4 resource for EE346.

We aim to achieve lane following and parking via the detection of aruco marker.

This work was done with the help of Prof.Zhang and all TAs.

Team numbers: WYX, MJL.

# Steps:


## 1. Clone the source codes

    cd ~/catkin_ws/src
  
    git clone git@github.com:MJLNSN/WYXMJL-Line_Following_and_Parking_via_ArucoMarker.git
  
## 2. Connect the turtlebot to pc

    ssh pi@192.168.3.29
  
    raspberrypi (password) 
  
## 3. Catkin make the package

    cd ~/catkin_ws
  
    catkin_make
 
## 4. Launch the nodes
  1. Launch the roscore **(in PC Terminal)**
  
    roscore 
  
  2. Launch the camera on SBC **(in raspberry pi Terminal)**
  
    roslaunch raspicam_node camerav2_410x308_30fps.launch 
  
  3. Set up communication between the PC and SBC **(in raspberry pi Terminal)**
  
    roslaunch turtlebot3_bringup turtlebot3_robot.launch 
  
  4. Launch the /aruco_single/pose node (to get the pose of aruco marker) **(in PC Terminal)**
  
    cd ~/catkin_ws/src/lab4 
  
    roslaunch aruco_marker_finder.launch
   
  5. Run the line_follower_turtlebot codes by launching lf2.launch file **(in PC Terminal)**
  
    cd ~/catkin_ws/src/line_follower_turtlebot 
  
    roslaunch lf2.launch 
  
  
  


# Result:
 
https://user-images.githubusercontent.com/96321798/201013405-2ef27cb2-c660-4184-bb64-7e05dd6786ca.mp4
