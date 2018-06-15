#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Author: Ozer Ozkahraman (ozkahramanozer@gmail.com)
# Date: 2018-06-14

from __future__ import print_function

import rospy
import actionlib

from sorohack_tree.msg import BTAction, BTGoal, BTFeedback

import actionlib_states
from actionlib_states import state_to_str


def feedback_cb(fb):
    print('node status:', fb.feedback.bt_status)

if __name__=='__main__':
    rospy.init_node('BT_client')
    client = actionlib.SimpleActionClient('action_test', BTAction)
    fb_subs = rospy.Subscriber('/action_test/feedback', BTFeedback, feedback_cb)

    print('waiting for server')
    client.wait_for_server()

    goal = BTGoal()
    goal.bt_action_goal = "Goal is this"
    client.send_goal(goal)
    client.wait_for_result(rospy.Duration.from_sec(5.0))

    r = rospy.Rate(5)
    while True:
        state = client.get_state()
        print('current state:', state_to_str(state))
        if state == actionlib_states.SUCCEEDED:
            break
        r.sleep()

    print('action result:',client.get_result())


