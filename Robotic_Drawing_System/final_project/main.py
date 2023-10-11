import sys
import rospy
import time
import math
import numpy as np

import actionlib

from kortex_driver.srv import *
from kortex_driver.msg import *

import example_waypoint_action_client
import path_planning



if __name__ == "__main__":
    picture = path_planning.main()
    num_points = 0
    for i in range(len(picture)):
        for j in range(len(picture[i])):
            picture[i][j] = picture[i][j]/3000
            picture[i][j][0] = picture[i][j][0]+0.4
            num_points = num_points + 1
    # print(picture)
    # print(num_points)
    # new_picture = picture[0:1][0:10][:]
    # print(new_picture)
    # print(len(new_picture[0])) 

    ex = example_waypoint_action_client.ExampleWaypointActionClient()
    ex.main(picture)

# def draw(picture_points):
#     for i in range(len(picture_points)):
#         for j in range(len(picture_points[i])):
#             picture_points[i][j] = picture_points[i][j]/3000
#             picture_points[i][j][0] = picture_points[i][j][0]+0.4
    
#     ex = example_waypoint_action_client.ExampleWaypointActionClient()
#     ex.main(picture_points)       