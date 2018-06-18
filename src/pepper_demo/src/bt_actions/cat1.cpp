#include <ros/ros.h>
#include <iostream>
#include <tf/tf.h>
#include <tf/transform_listener.h>
#include <tf/transform_datatypes.h>
#include <tf_conversions/tf_eigen.h>
#include <eigen_conversions/eigen_msg.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseStamped.h>
#include <shape_msgs/SolidPrimitive.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <Eigen/Core>
#include <moveit_msgs/CollisionObject.h>


int main(int argc, char** argv){

//// Ros-related initialization

  ros::init(argc, argv, "cat1");
  ros::NodeHandle node_handle;
  ros::AsyncSpinner spinner(1);
  spinner.start();
  moveit::planning_interface::MoveGroupInterface *move_group;
  moveit::planning_interface::PlanningSceneInterface planning_scene_interface;

//// Setting up the move group

  move_group = new moveit::planning_interface::MoveGroupInterface("left_arm");
  move_group-> setPlannerId("PRMstarkConfigDefault");
  move_group-> setPlanningTime(30);
  move_group-> setGoalTolerance(0.05);
  move_group->setMaxVelocityScalingFactor(0.5);
  ROS_INFO_NAMED("cat1", "Reference frame: %s", move_group->getPlanningFrame().c_str());
  geometry_msgs::PoseStamped current_pose = move_group->getCurrentPose();
  std::cout << current_pose.pose.position << '\n';
  std::cout << current_pose.pose.orientation << '\n';
  std::cout << current_pose.header.frame_id << '\n';

//// Setting up the table

  moveit_msgs::CollisionObject collision_object, collision_object2;
  collision_object.header.frame_id = move_group->getPlanningFrame();
  collision_object2.header.frame_id = "base_link";
  collision_object.id = "table";
  collision_object2.id = "owl";

  shape_msgs::SolidPrimitive primitive, primitive2;
  primitive.type = primitive.BOX;
  primitive.dimensions.resize(3);
  primitive.dimensions[0] = 1.4;
  primitive.dimensions[1] = 0.75;
  primitive.dimensions[2] = 0.70;

  geometry_msgs::Pose box_pose;
  box_pose.orientation.w = 0.7071;
  box_pose.orientation.x = 0.0;
  box_pose.orientation.y = 0.0;
  box_pose.orientation.z = 0.7071;
  box_pose.position.x = 0.6;
  box_pose.position.y = 0.2;
  box_pose.position.z = 0.4;

  collision_object.primitives.push_back(primitive);
  collision_object.primitive_poses.push_back(box_pose);
  collision_object.operation = collision_object.ADD;

  std::vector<moveit_msgs::CollisionObject> collision_objects;
  collision_objects.push_back(collision_object);
  planning_scene_interface.addCollisionObjects(collision_objects);


//// Setting up the trajectory to follow, assuming the arms are hanging on the side

  std::vector<geometry_msgs::Pose> waypoints;
  current_pose = move_group->getCurrentPose(); //update it
  waypoints.push_back(current_pose.pose);

  geometry_msgs::Pose target_pose = current_pose.pose ;
  // target_pose.position.x = 0.35;
  target_pose.position.y = 0.12;
  target_pose.position.z = 0.8;
  waypoints.push_back(target_pose);

  // target_pose.position.y = 0.3506;
  // waypoints.push_back(target_pose);
  moveit_msgs::RobotTrajectory trajectory;
  const double jump_threshold = 0.0;
  const double eef_step = 0.001;
  double fraction = move_group->computeCartesianPath(waypoints, eef_step, jump_threshold, trajectory);
  ROS_INFO_NAMED("cat1", "Visualizing plan 4 (Cartesian path) (%.2f%% achieved)", fraction * 100.0);
  sleep(5.0);
  moveit::planning_interface::MoveGroupInterface::Plan plan;
  plan.trajectory_ = trajectory;
  move_group->execute(plan);
  sleep(5.0);

  current_pose = move_group->getCurrentPose();
  std::cout << current_pose.pose.position << '\n';
  std::cout << current_pose.pose.orientation << '\n';
return 0;
}
