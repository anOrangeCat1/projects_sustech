#!/usr/bin/env python3
###
# KINOVA (R) KORTEX (TM)
#
# Copyright (c) 2021 Kinova inc. All rights reserved.
#
# This software may be modified and distributed 
# under the terms of the BSD 3-Clause license.
#
# Refer to the LICENSE file for details.
#
###

import sys
import rospy
import time
import math

import actionlib

from kortex_driver.srv import *
from kortex_driver.msg import *

circle_points = [[144, 108], [154, 108], [146, 109], [156, 109], [140, 110], [150, 110], 
          [160, 110], [138, 111], [148, 111], [158, 111], [133, 112], [143, 112], 
          [153, 112], [163, 112], [133, 113], [143, 113], [165, 113], [132, 114], 
          [163, 114], [127, 115], [164, 115], [125, 116], [166, 116], [124, 117], 
          [169, 117], [124, 118], [173, 118], [126, 119], [120, 120], [175, 120], 
          [123, 121], [180, 121], [176, 122], [121, 123], [117, 124], [182, 124], 
          [179, 125], [120, 126], [117, 127], [114, 128], [185, 128], [185, 129], 
          [184, 130], [184, 131], [183, 132], [115, 133], [113, 134], [111, 135], 
          [110, 136], [189, 136], [189, 137], [189, 138], [188, 139], [188, 140], 
          [188, 141], [188, 142], [188, 143], [189, 144], [189, 145], [189, 146], 
          [189, 147], [189, 148], [189, 149], [189, 150], [189, 151], [189, 152], 
          [189, 153], [189, 154], [189, 155], [187, 156], [113, 157], [113, 158], 
          [113, 159], [113, 160], [113, 161], [112, 162], [112, 163], [112, 164], 
          [111, 165], [111, 166], [188, 166], [187, 167], [185, 168], [183, 169], 
          [117, 170], [116, 171], [116, 172], [115, 173], [184, 173], [181, 174], 
          [122, 175], [119, 176], [182, 176], [178, 177], [124, 178], [121, 179], 
          [178, 179], [126, 180], [121, 181], [174, 181], [127, 182], [176, 182], 
          [132, 183], [125, 184], [166, 184], [127, 185], [164, 185], [128, 186], 
          [138, 186], [169, 186], [136, 187], [158, 187], [168, 187], [139, 188], 
          [149, 188], [159, 188], [169, 188], [142, 189], [152, 189], [162, 189], 
          [141, 190], [151, 190], [161, 190], [145, 191], [155, 191], [147, 192]]

real_circle_points = []

rect_points = [[1,0],[1,1],[0,1],[0,0],[1,0]]
real_rect_points = []

test_points = [[ 0.31 , 0.10666666666666667 ],
[ 0.31 , 0.11 ],
[ 0.31 , 0.11333333333333334 ],
[ 0.31 , 0.11666666666666667 ],
[ 0.31 , 0.12000000000000001 ],
[ 0.30666666666666664 , 0.12333333333333334 ],
[ 0.31 , 0.12666666666666668 ],
[ 0.3133333333333333 , 0.12666666666666668 ],
[ 0.31666666666666665 , 0.12666666666666668 ],
[ 0.32 , 0.12666666666666668 ],
[ 0.3233333333333333 , 0.12333333333333334 ],
[ 0.3233333333333333 , 0.12000000000000001 ],
[ 0.3233333333333333 , 0.11666666666666667 ],
[ 0.32 , 0.11333333333333334 ],
[ 0.31666666666666665 , 0.11333333333333334 ],
[ 0.3133333333333333 , 0.11 ]]

for i in range(len(circle_points)):
    real_circle_points.append([circle_points[i][0]/1000+0.3,circle_points[i][1]/1000])

for i in range(len(rect_points)):
    real_rect_points.append([rect_points[i][0]/30+0.4,rect_points[i][1]/30+0.1])

class ExampleWaypointActionClient:
    def __init__(self):
        try:
            rospy.init_node('example_waypoint_action_python')

            self.HOME_ACTION_IDENTIFIER = 2

            # Get node params
            self.robot_name = rospy.get_param('~robot_name', "my_gen3_lite")
            self.degrees_of_freedom = rospy.get_param("/" + self.robot_name + "/degrees_of_freedom", 6)
            self.is_gripper_present = rospy.get_param("/" + self.robot_name + "/is_gripper_present", True)

            rospy.loginfo("Using robot_name " + self.robot_name + " , robot has " + str(self.degrees_of_freedom) + " degrees of freedom and is_gripper_present is " + str(self.is_gripper_present))

            # Init the action topic subscriber
            self.action_topic_sub = rospy.Subscriber("/" + self.robot_name + "/action_topic", ActionNotification, self.cb_action_topic)
            self.last_action_notif_type = None

            # Init the services
            clear_faults_full_name = '/' + self.robot_name + '/base/clear_faults'
            rospy.wait_for_service(clear_faults_full_name)
            self.clear_faults = rospy.ServiceProxy(clear_faults_full_name, Base_ClearFaults)

            read_action_full_name = '/' + self.robot_name + '/base/read_action'
            rospy.wait_for_service(read_action_full_name)
            self.read_action = rospy.ServiceProxy(read_action_full_name, ReadAction)

            execute_action_full_name = '/' + self.robot_name + '/base/execute_action'
            rospy.wait_for_service(execute_action_full_name)
            self.execute_action = rospy.ServiceProxy(execute_action_full_name, ExecuteAction)

            activate_publishing_of_action_notification_full_name = '/' + self.robot_name + '/base/activate_publishing_of_action_topic'
            rospy.wait_for_service(activate_publishing_of_action_notification_full_name)
            self.activate_publishing_of_action_notification = rospy.ServiceProxy(activate_publishing_of_action_notification_full_name, OnNotificationActionTopic)
        
            get_product_configuration_full_name = '/' + self.robot_name + '/base/get_product_configuration'
            rospy.wait_for_service(get_product_configuration_full_name)
            self.get_product_configuration = rospy.ServiceProxy(get_product_configuration_full_name, GetProductConfiguration)
        except:
            self.is_init_success = False
        else:
            self.is_init_success = True

    def cb_action_topic(self, notif):
        self.last_action_notif_type = notif.action_event

    def wait_for_action_end_or_abort(self):
        while not rospy.is_shutdown():
            if (self.last_action_notif_type == ActionEvent.ACTION_END):
                rospy.loginfo("Received ACTION_END notification")
                return True
            elif (self.last_action_notif_type == ActionEvent.ACTION_ABORT):
                rospy.loginfo("Received ACTION_ABORT notification")
                return False
            else:
                time.sleep(0.01)

    def FillCartesianWaypoint(self, new_x, new_y, new_z, new_theta_x, new_theta_y, new_theta_z, blending_radius):
        cartesianWaypoint = CartesianWaypoint()

        cartesianWaypoint.pose.x = new_x
        cartesianWaypoint.pose.y = new_y
        cartesianWaypoint.pose.z = new_z
        cartesianWaypoint.pose.theta_x = new_theta_x
        cartesianWaypoint.pose.theta_y = new_theta_y
        cartesianWaypoint.pose.theta_z = new_theta_z
        cartesianWaypoint.reference_frame = CartesianReferenceFrame.CARTESIAN_REFERENCE_FRAME_BASE
        cartesianWaypoint.blending_radius = blending_radius
       
        return cartesianWaypoint

    def example_subscribe_to_a_robot_notification(self):
        # Activate the publishing of the ActionNotification
        req = OnNotificationActionTopicRequest()
        rospy.loginfo("Activating the action notifications...")
        try:
            self.activate_publishing_of_action_notification(req)
        except rospy.ServiceException:
            rospy.logerr("Failed to call OnNotificationActionTopic")
            return False
        else:
            rospy.loginfo("Successfully activated the Action Notifications!")

        rospy.sleep(1.0)
        return True

    def example_clear_faults(self):
        try:
            self.clear_faults()
        except rospy.ServiceException:
            rospy.logerr("Failed to call ClearFaults")
            return False
        else:
            rospy.loginfo("Cleared the faults successfully")
            rospy.sleep(2.5)
            return True

    def example_home_the_robot(self):
        # The Home Action is used to home the robot. It cannot be deleted and is always ID #2:
        self.last_action_notif_type = None
        req = ReadActionRequest()
        req.input.identifier = self.HOME_ACTION_IDENTIFIER
        try:
            res = self.read_action(req)
        except rospy.ServiceException:
            rospy.logerr("Failed to call ReadAction")
            return False
        # Execute the HOME action if we could read it
        else:
            # What we just read is the input of the ExecuteAction service
            req = ExecuteActionRequest()
            req.input = res.output
            rospy.loginfo("Sending the robot home...")
            try:
                self.execute_action(req)
            except rospy.ServiceException:
                rospy.logerr("Failed to call ExecuteAction")
                return False
            else:
                return self.wait_for_action_end_or_abort()

    def example_cartesian_waypoint_action(self,picture):
        self.last_action_notif_type = None

        client = actionlib.SimpleActionClient('/' + self.robot_name + '/cartesian_trajectory_controller/follow_cartesian_trajectory', kortex_driver.msg.FollowCartesianTrajectoryAction)

        client.wait_for_server()

        goal = FollowCartesianTrajectoryGoal()

        config = self.get_product_configuration()

        if config.output.model == ModelId.MODEL_ID_L31:
            h = 0.0665
        
            for i in range(len(picture)):
                goal.trajectory.append(self.FillCartesianWaypoint(picture[i][0][0],  picture[i][0][1],  h+0.05,  
                                                                  math.radians(90), 0, math.radians(90), 0))
                for j in range(len(picture[i])):
                    goal.trajectory.append(self.FillCartesianWaypoint(picture[i][j][0],  picture[i][j][1],  h,  
                                                                      math.radians(90), 0, math.radians(90), 0))
                goal.trajectory.append(self.FillCartesianWaypoint(picture[i][-1][0],  picture[i][-1][1],  h+0.05,  
                                                                  math.radians(90), 0, math.radians(90), 0))

        else:
            goal.trajectory.append(self.FillCartesianWaypoint(0.7,  0.0,   0.5,  math.radians(90), 0, math.radians(90), 0))
            goal.trajectory.append(self.FillCartesianWaypoint(0.7,  0.0,   0.33, math.radians(90), 0, math.radians(90), 0.1))
            goal.trajectory.append(self.FillCartesianWaypoint(0.7,  0.48,  0.33, math.radians(90), 0, math.radians(90), 0.1))
            goal.trajectory.append(self.FillCartesianWaypoint(0.61, 0.22,  0.4,  math.radians(90), 0, math.radians(90), 0.1))
            goal.trajectory.append(self.FillCartesianWaypoint(0.7,  0.48,  0.33, math.radians(90), 0, math.radians(90), 0.1))
            goal.trajectory.append(self.FillCartesianWaypoint(0.63, -0.22, 0.45, math.radians(90), 0, math.radians(90), 0.1))
            goal.trajectory.append(self.FillCartesianWaypoint(0.65, 0.05,  0.45, math.radians(90), 0, math.radians(90), 0))

        # Call the service
        rospy.loginfo("Sending goal(Cartesian waypoint) to action server...")
        try:
            client.send_goal(goal)
        except rospy.ServiceException:
            rospy.logerr("Failed to send goal.")
            return False
        else:
            client.wait_for_result()
            return True
    

    def main(self,picture):
        # For testing purposes
        success = self.is_init_success
        try:
            rospy.delete_param("/kortex_examples_test_results/waypoint_action_python")
        except:
            pass

        if success:
            #*******************************************************************************
            # Make sure to clear the robot's faults else it won't move if it's already in fault
            success &= self.example_clear_faults()
            #*******************************************************************************
            
            #*******************************************************************************
            # Activate the action notifications
            success &= self.example_subscribe_to_a_robot_notification()
            #*******************************************************************************

            #*******************************************************************************
            # Move the robot to the Home position with an Action
            success &= self.example_home_the_robot()
            #*******************************************************************************

            #*******************************************************************************
            # Example of Cartesian waypoint using an action client
            success &= self.example_cartesian_waypoint_action(picture=picture)
            rospy.sleep(0.5)
            #*******************************************************************************

            #*******************************************************************************
            # Move back the robot to the Home position with an Action
            success &= self.example_home_the_robot()
            #*******************************************************************************

        # For testing purposes
        rospy.set_param("/kortex_examples_test_results/waypoint_action_python", success)

        if not success:
            rospy.logerr("The example encountered an error.")


# if __name__ == "__main__":
#     ex = ExampleWaypointActionClient()
#     ex.main()
