#include <ros/ros.h>
#include <iostream>
#include <tf/tf.h>
#include <tf/transform_listener.h>
#include <tf/transform_datatypes.h>
#include <tf_conversions/tf_eigen.h>
#include <eigen_conversions/eigen_msg.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseStamped.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <Eigen/Core>





int main(int argc, char** argv){

    ros::init(argc, argv, "move_group_interface_tutorial");
    ros::NodeHandle node_handle;
    ros::AsyncSpinner spinner(1);
    spinner.start();

  	moveit::planning_interface::MoveGroupInterface *move_group;
    move_group = new moveit::planning_interface::MoveGroupInterface("left_arm");
    move_group-> setPlannerId("RRTConnectkConfigDefault");
    move_group-> setPlanningTime(30);
    // move_group-> setGoalTolerance(0.1);

    geometry_msgs::PoseStamped current_pose = move_group->getCurrentPose();
    std::cout << current_pose.pose.position << '\n';
    std::cout << current_pose.pose.orientation << '\n';
    std::cout << current_pose.header.frame_id << '\n';
// ============================================================================
// 1. As in fts_calib
// ============================================================================
    // geometry_msgs::Pose pose1;
    // pose1.position.x = 0.564465;
    // pose1.position.y = 0.00153;
    // pose1.position.z = 0.468386;
    // // pose1.orientation.x = current_pose.pose.orientation.x;
    // // pose1.orientation.y = current_pose.pose.orientation.y;
    // // pose1.orientation.z = current_pose.pose.orientation.z;
    // // pose1.orientation.w = current_pose.pose.orientation.w;
    //
    // geometry_msgs::PoseStamped pose2;
    // pose2.pose = pose1;
    // pose2.header.frame_id = move_group->getEndEffectorLink().c_str();
    // pose2.header.stamp = ros::Time::now();
    //
    // move_group->setPoseTarget(pose2);
    // move_group->move();

// // ============================================================================
// // 2. Trying only joint positions
// // ============================================================================
//     std::vector<double> j_values;
//     j_values.resize(3);
//     j_values[0] = 0.00;
//     j_values[1] = 0.00;
//     j_values[2] = 0.00;
//
//     move_group->setJointValueTarget(j_values);
//
//     //Motion plan from current location to custom position
// moveit::planning_interface::MoveGroupInterface::Plan my_plan;
// moveit::planning_interface::MoveItErrorCode success = move_group->plan(my_plan);
// // ROS_INFO("Visualizing Plan %s",success?"":"FAILED");
// /* Sleep to give RViz time to visualize the plan. */
// sleep(5.0);
//
// moveit_msgs::MoveItErrorCodes error_codes;
// if (success == true)
// {
// ROS_INFO("Planning To Move");
// error_codes = move_group->move();
// ROS_INFO("%d", error_codes.val);
// }

  // Planning to a joint-space goal
  // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  //
  // Let's set a joint space goal and move towards it.  This will replace the
  // pose target we set above.
  //
  // To start, we'll create an pointer that references the current robot's state.
  // RobotState is the object that contains all the current position/velocity/acceleration data.
    const robot_state::JointModelGroup* joint_model_group =
        move_group->getCurrentState()->getJointModelGroup("left_arm");
  moveit::core::RobotStatePtr current_state = move_group->getCurrentState();
  moveit::planning_interface::MoveGroupInterface::Plan my_plan;
  moveit::planning_interface::MoveItErrorCode success;
  //
  // Next get the current set of joint values for the group.
  std::vector<double> joint_group_positions;
  current_state->copyJointGroupPositions(joint_model_group, joint_group_positions);

  // Now, let's modify one of the joints, plan to the new joint space goal and visualize the plan.
  joint_group_positions[0] += 0.1;  // radians
  joint_group_positions[1] += 0.2;
  move_group->setJointValueTarget(joint_group_positions);

  success = (move_group->plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
  ROS_INFO_NAMED("tutorial", "Visualizing plan 2 (joint space goal) %s", success ? "" : "FAILED");
  sleep(5.0);
  move_group->move();
  return 0;
}


































// /* Author: Sachin Chitta, Dave Coleman, Mike Lautman */
// #include <moveit/move_group_interface/move_group_interface.h>
// #include <moveit/planning_scene_interface/planning_scene_interface.h>
//
// #include <moveit_msgs/DisplayRobotState.h>
// #include <moveit_msgs/DisplayTrajectory.h>
//
// #include <moveit_msgs/AttachedCollisionObject.h>
// #include <moveit_msgs/CollisionObject.h>
//
// #include <moveit_visual_tools/moveit_visual_tools.h>
// #include <ros/ros.h>
// #include <geometry_msgs/PoseStamped.h>
// #include <geometry_msgs/Point.h>
// #include <geometry_msgs/Quaternion.h>
// #include <geometry_msgs/Pose.h>
//
//
// int main(int argc, char** argv)
// {
//   ros::init(argc, argv, "move_group_interface_tutorial");
//   ros::NodeHandle node_handle;
//   ros::AsyncSpinner spinner(1);
//   spinner.start();
//
//   // BEGIN_TUTORIAL
//   //
//   // Setup
//   // ^^^^^
//   //
//   // MoveIt! operates on sets of joints called "planning groups" and stores them in an object called
//   // the `JointModelGroup`. Throughout MoveIt! the terms "planning group" and "joint model group"
//   // are used interchangably.
//   static const std::string PLANNING_GROUP = "left_arm";
//
//   // The :move_group_interface:`MoveGroup` class can be easily
//   // setup using just the name of the planning group you would like to control and plan for.
//   //TODO force torque calib uses *new*
//   moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP);
//   move_group.setPlannerId("RRTkConfigDefault");
//   move_group.setGoalTolerance(0.1);
//   move_group.setNumPlanningAttempts(50);
//   move_group.setPlanningTime(20);
//
//   // We will use the :planning_scene_interface:`PlanningSceneInterface`
//   // class to add and remove collision objects in our "virtual world" scene
//   // moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
//
//   // Raw pointers are frequently used to refer to the planning group for improved performance.
//   const robot_state::JointModelGroup* joint_model_group =
//       move_group.getCurrentState()->getJointModelGroup(PLANNING_GROUP);
//   // Visualization
//   // ^^^^^^^^^^^^^
//   //
//   // The package MoveItVisualTools provides many capabilties for visualizing objects, robots,
//   // and trajectories in RViz as well as debugging tools such as step-by-step introspection of a script
//   // namespace rvt = rviz_visual_tools;
//   // moveit_visual_tools::MoveItVisualTools visual_tools("base_link");
//   // visual_tools.deleteAllMarkers();
//   //
//   // // Remote control is an introspection tool that allows users to step through a high level script
//   // // via buttons and keyboard shortcuts in RViz
//   // visual_tools.loadRemoteControl();
//   //
//   // // RViz provides many types of markers, in this demo we will use text, cylinders, and spheres
//   // Eigen::Affine3d text_pose = Eigen::Affine3d::Identity();
//   // text_pose.translation().z() = 1.75;
//   // visual_tools.publishText(text_pose, "MoveGroupInterface Demo", rvt::WHITE, rvt::XLARGE);
//   //
//   // // Batch publishing is used to reduce the number of messages being sent to RViz for large visualizations
//   // visual_tools.trigger();
//   //
//   // // Getting Basic Information
//   // // ^^^^^^^^^^^^^^^^^^^^^^^^^
//   //
//   // We can print the name of the reference frame for this robot.
//   ROS_INFO_NAMED("tutorial", "planning time is %f", move_group.getPlanningTime());
//   ROS_INFO_NAMED("tutorial", "Reference frame: %s", move_group.getPlanningFrame().c_str());
//
//   // We can also print the name of the end-effector link for this group.
//   ROS_INFO_NAMED("tutorial", "End effector link: %s", move_group.getEndEffectorLink().c_str());
//   // ROS_INFO_NAMED("tutorial", "Planner: %s, %s", move_group.getPlannerParams().c_str())
//
//   geometry_msgs::PoseStamped robot_pose;
//   robot_pose = move_group.getCurrentPose();
//
//   geometry_msgs::Pose current_position;
//   current_position = robot_pose.pose;
//
//   /*Retrive position and orientation */
//   geometry_msgs::Point exact_pose = current_position.position;
//   geometry_msgs::Quaternion exact_orientation = current_position.orientation;
//
//   ROS_INFO("Reference frame : %s",move_group.getPlanningFrame().c_str());
//   ROS_INFO("Reference frame : %s",move_group.getEndEffectorLink().c_str());
//
//   std::cout<<"Robot position : "<<exact_pose.x<<"\t"<<exact_pose.y<<"\t"<<exact_pose.z<<std::endl;
//   std::cout<<"Robot Orientation : "<<exact_orientation.x<<"\t"<<exact_orientation.y<<"\t"<<exact_orientation.z<<"\t"<<exact_orientation.w<<std::endl;
//
//   // Start the demo
//   // ^^^^^^^^^^^^^^^^^^^^^^^^^
//   // visual_tools.prompt("Press 'next' in the RvizVisualToolsGui window to start the demo");
//
//   // Planning to a Pose goal
//   // ^^^^^^^^^^^^^^^^^^^^^^^
//   // We can plan a motion for this group to a desired pose for the
//   // end-effector.
//   // geometry_msgs::PoseStamped target_pose1 = robot_pose;
//   geometry_msgs::Pose target_pose1 = current_position;
//   // target_pose1.orientation.w = 1.0;
//   // target_pose1.orientation.x = -0.4057;
//   // target_pose1.orientation.y = -0.0479;
//   // target_pose1.orientation.z = -0.01;
//   target_pose1.position.x = 0.038;
//   target_pose1.position.y = 0.28025;
//   target_pose1.position.z = 0.1;
//   // target_pose1.header.frame_id = move_group.getEndEffectorLink().c_str();
//   // target_pose1.header.stamp = ros::Time::now();
//   move_group.setPoseTarget(target_pose1, "l_wrist");
//   // move_group.setPositionTarget(exact_pose.x+0.15, exact_pose.y+0.02, exact_pose.z, "l_wrist");
//   move_group.move();
//
//   // Now, we call the planner to compute the plan and visualize it.
//   // Note that we are just planning, not asking move_group
//   // to actually move the robot.
//   // moveit::planning_interface::MoveGroupInterface::Plan my_plan;
//   // move_group.execute(my_plan);
//   // bool success = (move_group.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
//   //
//   // ROS_INFO_NAMED("tutorial", "Visualizing plan 1 (pose goal) %s", success ? "" : "FAILED");
//
//   // Visualizing plans
//   // ^^^^^^^^^^^^^^^^^
//   // // We can also visualize the plan as a line with markers in RViz.
//   // ROS_INFO_NAMED("tutorial", "Visualizing plan 1 as trajectory line");
//   // visual_tools.publishAxisLabeled(target_pose1, "pose1");
//   // visual_tools.publishText(text_pose, "Pose Goal", rvt::WHITE, rvt::XLARGE);
//   // visual_tools.publishTrajectoryLine(my_plan.trajectory_, joint_model_group);
//   // visual_tools.trigger();
//   // // visual_tools.prompt("Press 'next' in the RvizVisualToolsGui window to continue the demo");
//   //
//   // // Moving to a pose goal
//   // // ^^^^^^^^^^^^^^^^^^^^^
//   // //
//   // // Moving to a pose goal is similar to the step above
//   // // except we now use the move() function. Note that
//   // // the pose goal we had set earlier is still active
//   // // and so the robot will try to move to that goal. We will
//   // // not use that function in this tutorial since it is
//   // // a blocking function and requires a controller to be active
//   // // and report success on execution of a trajectory.
//   //
//   // /* Uncomment below line when working with a real robot */
//   // /* move_group.move() */
//   //
//   // // Planning to a joint-space goal
//   // // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//   // //
//   // // Let's set a joint space goal and move towards it.  This will replace the
//   // // pose target we set above.
//   // //
//   // // To start, we'll create an pointer that references the current robot's state.
//   // // RobotState is the object that contains all the current position/velocity/acceleration data.
//   // moveit::core::RobotStatePtr current_state = move_group.getCurrentState();
//   // //
//   // // Next get the current set of joint values for the group.
//   // std::vector<double> joint_group_positions;
//   // current_state->copyJointGroupPositions(joint_model_group, joint_group_positions);
//   //
//   // // Now, let's modify one of the joints, plan to the new joint space goal and visualize the plan.
//   // joint_group_positions[0] = -1.0;  // radians
//   // move_group.setJointValueTarget(joint_group_positions);
//   //
//   // success = (move_group.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
//   // ROS_INFO_NAMED("tutorial", "Visualizing plan 2 (joint space goal) %s", success ? "" : "FAILED");
//   //
//   // // Visualize the plan in RViz
//   // visual_tools.deleteAllMarkers();
//   // visual_tools.publishText(text_pose, "Joint Space Goal", rvt::WHITE, rvt::XLARGE);
//   // visual_tools.publishTrajectoryLine(my_plan.trajectory_, joint_model_group);
//   // visual_tools.trigger();
//   // // visual_tools.prompt("Press 'next' in the RvizVisualToolsGui window to continue the demo");
//   //
//   // // Planning with Path Constraints
//   // // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//   // //
//   // // Path constraints can easily be specified for a link on the robot.
//   // // Let's specify a path constraint and a pose goal for our group.
//   // // First define the path constraint.
//   // moveit_msgs::OrientationConstraint ocm;
//   // ocm.link_name = "Tibia";
//   // ocm.header.frame_id = "base_link";
//   // ocm.orientation.w = 1.0;
//   // ocm.absolute_x_axis_tolerance = 0.1;
//   // ocm.absolute_y_axis_tolerance = 0.1;
//   // ocm.absolute_z_axis_tolerance = 0.1;
//   // ocm.weight = 1.0;
//   //
//   // // Now, set it as the path constraint for the group.
//   // moveit_msgs::Constraints test_constraints;
//   // test_constraints.orientation_constraints.push_back(ocm);
//   // move_group.setPathConstraints(test_constraints);
//   //
//   // // We will reuse the old goal that we had and plan to it.
//   // // Note that this will only work if the current state already
//   // // satisfies the path constraints. So, we need to set the start
//   // // state to a new pose.
//   // robot_state::RobotState start_state(*move_group.getCurrentState());
//   // geometry_msgs::Pose start_pose2;
//   // start_pose2.orientation.w = 1.0;
//   // start_pose2.position.x = 0.55;
//   // start_pose2.position.y = -0.05;
//   // start_pose2.position.z = 0.8;
//   // start_state.setFromIK(joint_model_group, start_pose2);
//   // move_group.setStartState(start_state);
//   //
//   // // Now we will plan to the earlier pose target from the new
//   // // start state that we have just created.
//   // move_group.setPoseTarget(target_pose1);
//   //
//   // // Planning with constraints can be slow because every sample must call an inverse kinematics solver.
//   // // Lets increase the planning time from the default 5 seconds to be sure the planner has enough time to succeed.
//   // move_group.setPlanningTime(10.0);
//   //
//   // success = (move_group.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
//   // ROS_INFO_NAMED("tutorial", "Visualizing plan 3 (constraints) %s", success ? "" : "FAILED");
//   //
//   // // Visualize the plan in RViz
//   // visual_tools.deleteAllMarkers();
//   // visual_tools.publishAxisLabeled(start_pose2, "start");
//   // visual_tools.publishAxisLabeled(target_pose1, "goal");
//   // visual_tools.publishText(text_pose, "Constrained Goal", rvt::WHITE, rvt::XLARGE);
//   // visual_tools.publishTrajectoryLine(my_plan.trajectory_, joint_model_group);
//   // visual_tools.trigger();
//   // visual_tools.prompt("next step");
//   //
//   // // When done with the path constraint be sure to clear it.
//   // move_group.clearPathConstraints();
//   //
//   // // Cartesian Paths
//   // // ^^^^^^^^^^^^^^^
//   // // You can plan a Cartesian path directly by specifying a list of waypoints
//   // // for the end-effector to go through. Note that we are starting
//   // // from the new start state above.  The initial pose (start state) does not
//   // // need to be added to the waypoint list but adding it can help with visualizations
//   // std::vector<geometry_msgs::Pose> waypoints;
//   // waypoints.push_back(start_pose2);
//   //
//   // geometry_msgs::Pose target_pose3 = start_pose2;
//   //
//   // target_pose3.position.z += 0.2;
//   // waypoints.push_back(target_pose3);  // up
//   //
//   // target_pose3.position.y -= 0.1;
//   // waypoints.push_back(target_pose3);  // left
//   //
//   // target_pose3.position.z -= 0.2;
//   // target_pose3.position.y += 0.2;
//   // target_pose3.position.x -= 0.2;
//   // waypoints.push_back(target_pose3);  // down and right
//   //
//   // // Cartesian motions are frequently needed to be slower for actions such as approach and retreat
//   // // grasp motions. Here we demonstrate how to reduce the speed of the robot arm via a scaling factor
//   // // of the maxiumum speed of each joint. Note this is not the speed of the end effector point.
//   // move_group.setMaxVelocityScalingFactor(0.1);
//   //
//   // // We want the Cartesian path to be interpolated at a resolution of 1 cm
//   // // which is why we will specify 0.01 as the max step in Cartesian
//   // // translation.  We will specify the jump threshold as 0.0, effectively disabling it.
//   // // Warning - disabling the jump threshold while operating real hardware can cause
//   // // large unpredictable motions of redundant joints and could be a safety issue
//   // moveit_msgs::RobotTrajectory trajectory;
//   // const double jump_threshold = 0.0;
//   // const double eef_step = 0.01;
//   // double fraction = move_group.computeCartesianPath(waypoints, eef_step, jump_threshold, trajectory);
//   // ROS_INFO_NAMED("tutorial", "Visualizing plan 4 (Cartesian path) (%.2f%% acheived)", fraction * 100.0);
//   //
//   // // Visualize the plan in RViz
//   // visual_tools.deleteAllMarkers();
//   // visual_tools.publishText(text_pose, "Joint Space Goal", rvt::WHITE, rvt::XLARGE);
//   // visual_tools.publishPath(waypoints, rvt::LIME_GREEN, rvt::SMALL);
//   // for (std::size_t i = 0; i < waypoints.size(); ++i)
//   //   visual_tools.publishAxisLabeled(waypoints[i], "pt" + std::to_string(i), rvt::SMALL);
//   // visual_tools.trigger();
//   // // visual_tools.prompt("Press 'next' in the RvizVisualToolsGui window to continue the demo");
//   //
//   // // Adding/Removing Objects and Attaching/Detaching Objects
//   // // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//   // //
//   // // Define a collision object ROS message.
//   // moveit_msgs::CollisionObject collision_object;
//   // collision_object.header.frame_id = move_group.getPlanningFrame();
//   //
//   // // The id of the object is used to identify it.
//   // collision_object.id = "box1";
//   //
//   // // Define a box to add to the world.
//   // shape_msgs::SolidPrimitive primitive;
//   // primitive.type = primitive.BOX;
//   // primitive.dimensions.resize(3);
//   // primitive.dimensions[0] = 0.4;
//   // primitive.dimensions[1] = 0.1;
//   // primitive.dimensions[2] = 0.4;
//   //
//   // // Define a pose for the box (specified relative to frame_id)
//   // geometry_msgs::Pose box_pose;
//   // box_pose.orientation.w = 1.0;
//   // box_pose.position.x = 0.4;
//   // box_pose.position.y = -0.2;
//   // box_pose.position.z = 1.0;
//   //
//   // collision_object.primitives.push_back(primitive);
//   // collision_object.primitive_poses.push_back(box_pose);
//   // collision_object.operation = collision_object.ADD;
//   //
//   // std::vector<moveit_msgs::CollisionObject> collision_objects;
//   // collision_objects.push_back(collision_object);
//   //
//   // // Now, let's add the collision object into the world
//   // ROS_INFO_NAMED("tutorial", "Add an object into the world");
//   // planning_scene_interface.addCollisionObjects(collision_objects);
//   //
//   // // Show text in RViz of status
//   // visual_tools.publishText(text_pose, "Add object", rvt::WHITE, rvt::XLARGE);
//   // visual_tools.trigger();
//   //
//   // // Wait for MoveGroup to recieve and process the collision object message
//   // // visual_tools.prompt("Press 'next' in the RvizVisualToolsGui window to once the collision object appears in RViz");
//   //
//   // // Now when we plan a trajectory it will avoid the obstacle
//   // move_group.setStartState(*move_group.getCurrentState());
//   // geometry_msgs::Pose another_pose;
//   // another_pose.orientation.w = 1.0;
//   // another_pose.position.x = 0.4;
//   // another_pose.position.y = -0.4;
//   // another_pose.position.z = 0.9;
//   // move_group.setPoseTarget(another_pose);
//   //
//   // success = (move_group.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
//   // ROS_INFO_NAMED("tutorial", "Visualizing plan 5 (pose goal move around cuboid) %s", success ? "" : "FAILED");
//   //
//   // // Visualize the plan in RViz
//   // visual_tools.deleteAllMarkers();
//   // visual_tools.publishText(text_pose, "Obstacle Goal", rvt::WHITE, rvt::XLARGE);
//   // visual_tools.publishTrajectoryLine(my_plan.trajectory_, joint_model_group);
//   // visual_tools.trigger();
//   // visual_tools.prompt("next step");
//   //
//   // // Now, let's attach the collision object to the robot.
//   // ROS_INFO_NAMED("tutorial", "Attach the object to the robot");
//   // move_group.attachObject(collision_object.id);
//   //
//   // // Show text in RViz of status
//   // visual_tools.publishText(text_pose, "Object attached to robot", rvt::WHITE, rvt::XLARGE);
//   // visual_tools.trigger();
//   //
//   // /* Wait for MoveGroup to recieve and process the attached collision object message */
//   // // visual_tools.prompt("Press 'next' in the RvizVisualToolsGui window to once the collision object attaches to the "
//   //                     // "robot");
//   //
//   // // Now, let's detach the collision object from the robot.
//   // ROS_INFO_NAMED("tutorial", "Detach the object from the robot");
//   // move_group.detachObject(collision_object.id);
//   //
//   // // Show text in RViz of status
//   // visual_tools.publishText(text_pose, "Object dettached from robot", rvt::WHITE, rvt::XLARGE);
//   // visual_tools.trigger();
//   //
//   // /* Wait for MoveGroup to recieve and process the attached collision object message */
//   // // visual_tools.prompt("Press 'next' in the RvizVisualToolsGui window to once the collision object detaches to the "
//   //                     // "robot");
//   //
//   // // Now, let's remove the collision object from the world.
//   // ROS_INFO_NAMED("tutorial", "Remove the object from the world");
//   // std::vector<std::string> object_ids;
//   // object_ids.push_back(collision_object.id);
//   // planning_scene_interface.removeCollisionObjects(object_ids);
//   //
//   // // Show text in RViz of status
//   // visual_tools.publishText(text_pose, "Object removed", rvt::WHITE, rvt::XLARGE);
//   // visual_tools.trigger();
//   //
//   // /* Wait for MoveGroup to recieve and process the attached collision object message */
//   // visual_tools.prompt("Press 'next' in the RvizVisualToolsGui window to once the collision object disapears");
//
//   // END_TUTORIAL
//
//   ros::shutdown();
//   return 0;
// }
