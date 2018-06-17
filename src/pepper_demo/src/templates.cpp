// =============================================================================
// 1: JOINT SPACE Trajectory
// =============================================================================

// Planning to a joint-space goal (part of the official tutorial, WORKS)
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//
// To start, we'll create an pointer that references the current robot's state.
// // RobotState is the object that contains all the current position/velocity/acceleration data.
  const robot_state::JointModelGroup* joint_model_group =
      move_group->getCurrentState()->getJointModelGroup("left_arm");
moveit::core::RobotStatePtr current_state = move_group->getCurrentState();
moveit::planning_interface::MoveGroupInterface::Plan my_plan;
moveit::planning_interface::MoveItErrorCode success;

// Next get the current set of joint values for the group.
std::vector<double> joint_group_positions;
current_state->copyJointGroupPositions(joint_model_group, joint_group_positions);

// Now, let's modify one of the joints, plan to the new joint space goal and visualize the plan.
joint_group_positions[0] += 0.05;  // radians
joint_group_positions[1] += 0.08;
move_group->setJointValueTarget(joint_group_positions);

success = (move_group->plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
ROS_INFO_NAMED("tutorial", "Visualizing plan 2 (joint space goal) %s", success ? "" : "FAILED");
sleep(5.0);
move_group->move();
sleep(5.0);
ROS_INFO_NAMED("this part works","Now for cartesian planning");
