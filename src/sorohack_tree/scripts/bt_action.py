#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Author: Ozer Ozkahraman (ozkahramanozer@gmail.com)
# Date: 2018-06-14

from __future__ import print_function

import rospy
import actionlib
import os

from sorohack_tree.msg import BTAction, BTFeedback, BTResult


class BT_Action:
    def __init__(self, name):
        self.action_server = actionlib.SimpleActionServer(name, BTAction, self.execute_cb, False)
        self.action_server.start()
        self.name = name

        self.feedback = BTFeedback()
        self.result = BTResult()

    def execute_cb(self, goal):
        rospy.loginfo(self.name+' received goal: '+goal.bt_action_goal)

        # actual action
        r = rospy.Rate(1)
        for i in range(10):
            # check preempting
            if self.action_server.is_preempt_requested():
                rospy.loginfo(self.name+ ' is preempted!')
                self.action_server.set_preempted()
                return

            # let the tree know we are running
            self.tree_feedback('RUNNING')


            # work
            print(i)
            if i == 4:
                print("OHMAHFUCKINGGOD")
                os.system("rosrun pepper_demo move_bitch")

            r.sleep()

        # work done successfully
        self.result.bt_status = 'SUCCESS'
        rospy.loginfo(self.name+' completed successfully')
        self.action_server.set_succeeded(self.result)

        # let the tree know we are done
        self.tree_feedback('SUCCESS')

    def tree_feedback(self, s):
        self.feedback.bt_status = s
        self.action_server.publish_feedback(self.feedback)





if __name__=='__main__':
    rospy.init_node('BT_Server')
    a = BT_Action('action_test')
    rospy.spin()
