#!/usr/bin/env python

import rospy
import smach
import actionlib


import cv2
from cv2 import aruco

# Brings in the .action file and messages used by the move base action
from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal
from actionlib_msgs.msg import *  
from geometry_msgs.msg import Pose, Point, Quaternion

from sensor_msgs.msg import CompressedImage
from cv_bridge import CvBridge

from turtlebot3_msgs.msg import Sound
import time
import os


aruco_number = 0
# Define a target directory
locations = dict()  
# Need to get the Coodirates of 4 points 
# locations['p1.5'] = Pose(Point(1.409, -2.135, 0.0), Quaternion(0.000, 0.000, -0.789, 0.615))    
locations['p1.5'] = Pose(Point(1.478, -2.056, 0.0), Quaternion(0.000, 0.000, -0.789, 0.615)) 
locations['p2'] = Pose(Point(-0.331, 0.876, 0.0), Quaternion(0.000, 0.000, -0.184, 0.983))     
locations['p3'] = Pose(Point(-3.273, -1.884, 0.0), Quaternion(0.000, 0.000, 0.528, 0.849))    
locations['p4'] = Pose(Point(-0.494, -4.959, 0.0), Quaternion(0.000, 0.000, -0.797, 0.604))
locations['p1.8'] = Pose(Point(0.367, -1.010, 0.0), Quaternion(0.000, 0.000, -0.792, 0.694)) 
locations['p1'] = Pose(Point(2.552, -2.214, 0.0), Quaternion(0.000, 0.000, -0.907, 0.420)) 


key_locations = ['p1.5','p2','p3','p4','p1.8','p1']

class ARcodeDetector:
    def __init__(self):
        self.bridge = CvBridge()
        self.image_sub = rospy.Subscriber("/raspicam_node/image/compressed",CompressedImage,self.img_callback)

    
    def img_callback(self,msg):
        image = self.bridge.compressed_imgmsg_to_cv2(msg, desired_encoding='passthrough')
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
               
        
        aruco_dict = aruco.Dictionary_get(aruco.DICT_ARUCO_ORIGINAL)
        parameters =  aruco.DetectorParameters_create()
        corners, ids, rejectedImgPoints = aruco.detectMarkers(gray,
                                                            aruco_dict,
                                                            parameters=parameters)
        aruco.drawDetectedMarkers(image, corners,ids)
        
        
        if not(ids is None):
            global aruco_number
            aruco_number = ids[0][0]
            # print("ccc")
            # print(aruco_number)
            
        cv2.imshow("windows",image)
        cv2.waitKey(1)

class FourTargets(smach.State):
    def __init__(self):
        smach.State.__init__(self, outcomes=['finish_4targets'])

    def execute(self, userdata):
        rospy.loginfo('Executing state FourTargets')
        client = actionlib.SimpleActionClient('move_base',MoveBaseAction)
        client.wait_for_server()
        
        goal = MoveBaseGoal()
        goal.target_pose.header.frame_id = "map"
        goal.target_pose.header.stamp = rospy.Time.now()
        
        global aruco_number,locations,key_locations
        
        for i in range(len(locations)):         
            goal.target_pose.pose = locations[key_locations[i]]
            # print(locations[key_locations[i]])
                    
            rospy.loginfo("Going to: " + str(i))
                   
            # Sends the goal to the action server.
            client.send_goal(goal)
                    
            # wait = client.wait_for_result(rospy.Duration(time[i]))
            wait = client.wait_for_result()
                    
            if not wait:
                rospy.logerr("Action server not available!")
                rospy.signal_shutdown("Action server not available!")
        
        # Waits for the server to finish performing the action.
        wait = client.wait_for_result()
        # If the result doesn't arrive, assume the Server is not available
        if not wait:
            rospy.logerr("Action server not available!")
            rospy.signal_shutdown("Action server not available!")
        else:
            rospy.loginfo("Finish!")
            
        return 'finish_4targets'        
        
    
class Go2Pn(smach.State):
    def __init__(self):
        smach.State.__init__(self, outcomes=['reach_Pn'])

    def execute(self, userdata):
        rospy.loginfo('Executing state Go2Pn')
        
        # first recieve the aruco_number, and go to the relative point n
        
        client = actionlib.SimpleActionClient('move_base',MoveBaseAction)
        client.wait_for_server()
        
        goal = MoveBaseGoal()
        goal.target_pose.header.frame_id = "map"
        goal.target_pose.header.stamp = rospy.Time.now()
        
        global aruco_number,locations,key_locations
        
        # buzzer = rospy.Publisher("/sound",Sound,queue_size=10)
        # time.sleep(2)
        # rospy.loginfo(str(aruco_number))
        # rate = rospy.Rate(10)
        # # rospy.loginfo("buzzer!!!!!")
        # msg = Sound()
        # for i in range(aruco_number):
        # buzzer.publish(msg)
        #     # rospy.loginfo("buzzer!")
        #     rate.sleep()
            
        if aruco_number==2:
            # go to p2
            # print(aruco_number)
            goal.target_pose.pose = locations[key_locations[1]]
            rospy.loginfo("Going to: p2")
            
            client.send_goal(goal)
            wait = client.wait_for_result()
            if not wait:
                rospy.logerr("Action server not available!")
                rospy.signal_shutdown("Action server not available!")
                 
        elif aruco_number==3:
            # print(aruco_number)
            goal.target_pose.pose = locations[key_locations[2]]
            rospy.loginfo("Going to: p3")
            
            client.send_goal(goal)
            wait = client.wait_for_result()
            if not wait:
                rospy.logerr("Action server not available!")
                rospy.signal_shutdown("Action server not available!")
                # return 
            # return 'reach_Pn'
        else:
            # print(aruco_number)
            goal.target_pose.pose = locations[key_locations[3]]
            rospy.loginfo("Going to: p4")
            
            client.send_goal(goal)
            wait = client.wait_for_result()
            if not wait:
                rospy.logerr("Action server not available!")
                rospy.signal_shutdown("Action server not available!")
        
        return 'reach_Pn'


class Go2P1(smach.State):
    def __init__(self):
        smach.State.__init__(self, outcomes=['reach_P1'])

    def execute(self, userdata):
        rospy.loginfo('Executing state Go2P1')
        client = actionlib.SimpleActionClient('move_base',MoveBaseAction)
        client.wait_for_server()
        
        goal = MoveBaseGoal()
        goal.target_pose.header.frame_id = "map"
        goal.target_pose.header.stamp = rospy.Time.now()
        
        global aruco_number,locations,key_locations
        
        goal.target_pose.pose = locations[key_locations[4]]
        rospy.loginfo("Going to: p1.8")
            
        client.send_goal(goal)
        wait = client.wait_for_result()
        if not wait:
            rospy.logerr("Action server not available!")
            rospy.signal_shutdown("Action server not available!")
            
        goal.target_pose.pose = locations[key_locations[5]]
        rospy.loginfo("Going to: p1")
        
        client.send_goal(goal)
        wait = client.wait_for_result()
        if not wait:
            rospy.logerr("Action server not available!")
            rospy.signal_shutdown("Action server not available!")
        
        # go back to p1 from pn
        
        return 'reach_P1'
    
    
class Go2P1_5(smach.State):
    def __init__(self):
        smach.State.__init__(self, outcomes=['reach_P1_5'])

    def execute(self, userdata):
        rospy.loginfo('Executing state Go2P1_5')
        client = actionlib.SimpleActionClient('move_base',MoveBaseAction)
        client.wait_for_server()
        
        goal = MoveBaseGoal()
        goal.target_pose.header.frame_id = "map"
        goal.target_pose.header.stamp = rospy.Time.now()
        
        global aruco_number,locations,key_locations
        goal.target_pose.pose = locations[key_locations[0]]
        rospy.loginfo("Going to: p1_5")
            
        client.send_goal(goal)
        
        # buzzer = rospy.Publisher("/sound",Sound,queue_size=10)
        # # time.sleep(1)
        # if(aruco_number!=0):
        #     for i in range(aruco_number):
        #     # rospy.init_node('taker',anonymous=True)
        #         msg = Sound()
        #         buzzer.publish(msg)
        #     rospy.loginfo("buzzer")
        
        wait = client.wait_for_result()
        
        
                
        if not wait:
            rospy.logerr("Action server not available!")
            rospy.signal_shutdown("Action server not available!")
        
        # go back to p1 from pn
        
        return 'reach_P1_5'    
    
def buzzer(num):
    buzzer = rospy.Publisher("/sound",Sound,queue_size=10)
    count=0
    while(count<2):
        msg = Sound()
        buzzer.publish(msg)
        rospy.loginfo("buzzer")
        time.sleep(1)
        count=count+1

class Buzzer(smach.State):
    def __init__(self):
        smach.State.__init__(self, outcomes=['Buzzer_over'])

    def execute(self, userdata):
        rospy.loginfo('Executing state Buzzer')
        
        global aruco_number
        buzzer = rospy.Publisher("/sound",Sound,queue_size=10)
        # time.sleep(1)
        rospy.loginfo(str(aruco_number))
        msg = Sound()
        if(aruco_number!=0):
            for i in range(aruco_number):
            # rospy.init_node('taker',anonymous=True)
                buzzer.publish(msg)
                rospy.loginfo("buzzer")
                time.sleep(1)
                
        # buzzer(aruco_number)
        time.sleep(2)
        return 'Buzzer_over'  
    
if __name__ == "__main__":
    rospy.init_node('smach_example_state_machine')


    # Create a SMACH state machine
    sm = smach.StateMachine(outcomes=['over'])

    # Open the container
    with sm:
        # Add states to the container
        smach.StateMachine.add('FourTargets', FourTargets(), 
                               transitions={'finish_4targets':'Go2P1_5'
                                            })
        smach.StateMachine.add('Go2P1_5', Go2P1_5(), 
                               transitions={'reach_P1_5':'Buzzer'})
        smach.StateMachine.add('Buzzer',Buzzer(),
                               transitions={'Buzzer_over':'Go2Pn'})
        smach.StateMachine.add('Go2Pn', Go2Pn(), 
                               transitions={'reach_Pn':'Go2P1'})
        smach.StateMachine.add('Go2P1', Go2P1(), 
                               transitions={'reach_P1':'over'})
        
        
    # rospy.init_node('ARUCO_Detector')
    arc = ARcodeDetector()
    
    # intro_server = IntrospectionServer()

    # Execute SMACH plan
    outcome = sm.execute()
    
    rospy.spin()
    
    # intro_server.stop()
    