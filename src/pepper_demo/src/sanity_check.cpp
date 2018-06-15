#include <ros/ros.h>
#include <moveit/move_group_interface/move_group_interface.h>
// #include <iostream>
// #include <memory>
#include <moveit/robot_model/robot_model.h>
#include <moveit/robot_trajectory/robot_trajectory.h>
#include <moveit/trajectory_processing/iterative_time_parameterization.h>


int main(int argc, char** argv)
{
  ros::init(argc, argv, "oh_mah_gahd");
  ros::AsyncSpinner spinner(1);
  spinner.start();

  moveit::planning_interface::MoveGroupInterface group("left_arm");
  group.setRandomTarget();
  group.move();

  return 0;
}
