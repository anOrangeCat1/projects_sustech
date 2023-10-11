## WYXMJL-Navigation_and_Parking 
This is the lab6 resource for EE346.

We aim to achieve fout-point navigation and parking via the detection of aruco marker.

This work was done with the help of Prof.Zhang and all TAs.

Team numbers: WYX, MJL.

# Steps:


## 1. Clone the source codes

    cd ~/catkin_ws/src
  
    git clone git@github.com:WYXMJL-Navigation_and_Parking_via_ArucoMarker.git
  
## 2. Connect the turtlebot to pc

    ssh pi@192.168.3.29
  
    raspberrypi (password) 
  
 
## 3. Launch the nodes and run the program
  1. Launch the roscore **(in PC Terminal)**
  
    roscore 
  
  2. Launch the camera on SBC **(in raspberry pi Terminal)**
  
    roslaunch raspicam_node camerav2_410x308_30fps.launch 
  
  3. Set up communication between the PC and SBC **(in raspberry pi Terminal)**
  
    roslaunch turtlebot3_bringup turtlebot3_robot.launch 
  
  4. Launch the /aruco_single/pose node (to get the pose of aruco marker) **(in PC Terminal)**
  
    cd ~/catkin_ws/src/lab6 
  
    roslaunch aruco_marker_finder.launch
    
  5. Launch the map and locolizate the turtlebot in rviz **(in PC Terminal)**
  
    export TURTLEBOT3_MODEL=burger
    
    roslaunch turtlebot3_navigation turtlebot3_navigation.launch map_file:=$HOME/map.yaml
    
   
  6. Run the four_targets_navigation.py codes **(in PC Terminal)**
  
    python four_targets_navigation.py
    
  
  
