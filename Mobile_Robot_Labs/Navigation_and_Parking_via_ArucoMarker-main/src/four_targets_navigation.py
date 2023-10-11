#!/usr/bin/env python
# license removed for brevity

import rospy

# Brings in the SimpleActionClient
import actionlib

import cv2
from cv2 import aruco

# Brings in the .action file and messages used by the move base action
from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal
from actionlib_msgs.msg import *  
from geometry_msgs.msg import Pose, Point, Quaternion

import aruco_test


def movebase_client():
    # Define a target directory
    locations = dict()  
    # Need to get the Coodirates of 4 points 
    locations['p1.5'] = Pose(Point(1.128, 2.41, 0.0), Quaternion(0.000, 0.000, -0.789, 0.615))
    
    locations['p2'] = Pose(Point(-0.457, -0.122, 0.0), Quaternion(0.000, 0.000, -0.184, 0.983))  
    locations['p2.5'] = Pose(Point(2.678, 0.908, 0.0), Quaternion(0.000, 0.000, -0.059, 0.998))
    
    locations['p3'] = Pose(Point(3.380, -1.494, 0.0), Quaternion(0.000, 0.000, 0.528, 0.849))
    
    locations['p4'] = Pose(Point(4.638, 2.364, 0.0), Quaternion(0.000, 0.000, -0.797, 0.604))
    
    locations['p1'] = Pose(Point(0.815, 3.864, 0.0), Quaternion(0.000, 0.000, -0.805, 0.592)) 
    locations['p5'] = Pose(Point(0.907, 3.195, 0.0), Quaternion(0.000, 0.000, -0.792, 0.694)) 
    
    key_locations = ['p1.5','p2','p3','p4','p1','p5']
    # key_locations = ['p5']
    # time = [20,15,30,40,40,40,40]
    
    goal_states = ['PENDING', 'ACTIVE', 'PREEMPTED',   
                       'SUCCEEDED', 'ABORTED', 'REJECTED',  
                       'PREEMPTING', 'RECALLING', 'RECALLED',  
                       'LOST'] 
    
    # Create an action client called "move_base" with action definition file "MoveBaseAction"
    client = actionlib.SimpleActionClient('move_base',MoveBaseAction)
 
    # Waits until the action server has started up and started listening for goals.
    client.wait_for_server()
    

    # Creates a new goal with the MoveBaseGoal constructor
    goal = MoveBaseGoal()
    goal.target_pose.header.frame_id = "map"
    goal.target_pose.header.stamp = rospy.Time.now()
    
    # p1
    # position: 
    #   x: 0.754427228702
    #   y: 3.77546022759
    #   z: 0.0
    # orientation: 
    #   x: 0.0
    #   y: 0.0
    #   z: -0.828556732943
    #   w: 0.559905117225
    
    
    # p1.5
    
    
    # p2
    # pose: 
    # position: 
    #   x: -0.470151016469
    #   y: -0.0611694299608
    #   z: 0.0
    # orientation: 
    #   x: 0.0
    #   y: 0.0
    #   z: -0.217798471224
    #   w: 0.975993763265

    
    
    # p3
    # position: 
    #   x: 3.27957227636
    #   y: -1.49787762844
    #   z: 0.0
    # orientation: 
    #   x: 0.0
    #   y: 0.0
    #   z: 0.594422636632
    #   w: 0.804152802059

    
    
    # p4
    # position: 
    #   x: 4.67116693191
    #   y: 2.37766026672
    #   z: 0.0
    # orientation: 
    #   x: 0.0
    #   y: 0.0
    #   z: -0.750287422576
    #   w: 0.661111778389
    
    
    
    for i in range(len(locations)):
        # if i == 1:
        #     print("go straight!")
        #     goal.target_pose.pose.position.x = 0.3
        #     goal.target_pose.pose.orientation.w = 0
        #     client.send_goal(goal)
        #     # wait = client.wait_for_result(rospy.Duration(time[i]))
        #     wait = client.wait_for_result()
        
        # if i == 1:
        #     print("go straight!")
        #     v.linear.x = 0.3
        #     time.sleep(1)
        #     v.linear.x = 0
            
        # else:           
        goal.target_pose.pose = locations[key_locations[i]]
        print(locations[key_locations[i]])
                
        rospy.loginfo("Going to: " + str(i))
                
                
        # Sends the goal to the action server.
        client.send_goal(goal)
                
        # wait = client.wait_for_result(rospy.Duration(time[i]))
        wait = client.wait_for_result()
                
        if not wait:
            rospy.logerr("Action server not available!")
            rospy.signal_shutdown("Action server not available!")
                
        state = client.get_state()
        if state == GoalStatus.SUCCEEDED:
        # key_list = list(test.keys())[list(test.values()).index(i)]
            rospy.loginfo("arrive: "+key_locations[i])
            rospy.loginfo("State:" + str(state)) 
        else:  
            rospy.loginfo("Goal failed with error code" +str(goal_states[state])) 

    
    # Waits for the server to finish performing the action.
    wait = client.wait_for_result(rospy.Duration(30))
    # If the result doesn't arrive, assume the Server is not available
    if not wait:
        rospy.logerr("Action server not available!")
        rospy.signal_shutdown("Action server not available!")
    else:
    # Result of executing the action
        return client.get_result()  


def aruco_park():
    pass

# If the python node is executed as main process (sourced directly)
if __name__ == '__main__':
    try:
        # Initializes a rospy node to let the SimpleActionClient publish and subscribe
        rospy.init_node('movebase_client_py')
        result = movebase_client()
        if result:
            rospy.loginfo("Goal execution done!")
            # print("aaa")
            aruco = aruco_test.ARcodeDetector()
            # print("park over")
            rospy.spin()
        
        
    except rospy.ROSInterruptException:
        rospy.loginfo("Navigation test finished.")
        