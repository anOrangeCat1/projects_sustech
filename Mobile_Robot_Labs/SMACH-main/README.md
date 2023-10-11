# WYXMJL-SMACH
This is the lab7 resource for EE346. Team numbers: WYX, MJL.

![6I_Z5)87WLJUTQR7W{`AP15](https://user-images.githubusercontent.com/96321798/212325447-f992348b-420d-4317-89fe-37a4f26a140e.jpg)

Trere are four points P1, P2, P3 and P4 on the map. The task starts from location P1, and the robot should successively move to P2, P3, P4 and back to P1 in that order before moving toward the ArUco marker to recognize the ID of the marker placed near the red triangle in the floor plan. The ArUco marker ID is a number n = 2, 3 or 4 and, uponrecognizing the ID, the robot should beep with the buzzer on TurtleBot3 n times, and then move to Pn before coming to a stop.

This work was done with the help of Prof.Zhang and all TAs.

Team numbers: WYX, MJL

# Details:

Here is the logic of our code.

## 1. Aruco Code Detection:

To recognize the aruco marker on the wall, we import aruco from cv2. 

The logic is to firstly define aruco_dict by usting the command 'aruco.Dictionary_get', while the type of aruco code is 'aruco.DICT_ARUCO_ORIGINAL'. 

Then we use the command 'aruco.drawDetectedMarkers(image, corners,ids)' to find the id of aruco marker.


## 2. Navigation

To navigate the robot to move to a certain point Pn, we mainly used the navigation function of move_base. So we first need to import it.

To execute the navigation function, we should send a goal to the robot, which is a 'pose'. We save all the poses in a dictionary called 'locations'. 

In the dictionary, except the point p1, p2, p3 and p4, two intermediate points p1.5 and p1.8 are added, making the move of robot smoother. With intermediate points, it'll take less time to move to the goal, and it's less likely for robot to make wrong decisions（For example, the robot may think itself unable to p2 and return to the origin point, while it actually could reach p2.)

## 3. Beep

After getting the id of aruco marker, we use 'Sound()' to beep.

The number of beeps is equal to the id of aruco marker.

## 4. SMACH

In this program, we use finite state machine. 

There are 5 states: FourTargets, Go2P1_5, Buzzer, Go2Pn, Go2P1 and over. The relationship is shown in the flow chart below.

![@Z~EI)6VGZ `GSMM(K7DDZB](https://user-images.githubusercontent.com/96321798/212324160-55d4e29d-023c-403b-9e52-0a0ea8ae685e.jpg)



# Steps:

To run the code, please follow the instruction.

## 1. Clone the source codes

    cd ~/catkin_ws/src
  
    git clone git@github.com/MJLNSN/WYXMJL-SAMTCH/blob/main/classroom_map.py
  
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
  
    python classroom_map.py
    
  
  
