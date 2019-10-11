/**
 * Copyright (C) 2016-2019 Arne Peters - arne.peters@tum.de
 * Technische Universität München
 * Chair for Chair of Robotics, Artificial Intelligence and Real-time Systems
 * Fakultät für Informatik / I16, Boltzmannstraße 3, 85748 Garching bei München, Germany
 * https://www6.in.tum.de
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
 * following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 * disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 * following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SRC_IIWA_SIM_H
#define SRC_IIWA_SIM_H

#include <actionlib/client/simple_action_client.h>
#include <actionlib/server/simple_action_server.h>
#include <ros/ros.h>
#include <tf/transform_listener.h>

#include <iiwa_msgs/MoveAlongSplineAction.h>
#include <iiwa_msgs/MoveToCartesianPoseAction.h>
#include <iiwa_msgs/MoveToJointPositionAction.h>

#include <moveit_msgs/MoveGroupAction.h>

namespace iiwa_sim {
	/**
	 * The iiwa SimNode provides wrappers for MoveIt! actions to offer the same interfaces as the PTP action commands
	 * of the real robot when working with a simulated robot.
	 */
	class SimNode {
		public:
			/**
			 * Constructor
			 */
			SimNode();

			/**
			 * Destructor
			 */
			virtual ~SimNode();

			/**
			 * The nodes idle spin loop
			 */
			void spin();

			/**
			 * Stops the current goal, if any.
			 */
			void cancelCurrentGoal();

			/**
			 * Create a MoveIt! constraint message for a specific axis
			 * @param jointName
			 * @param angle
			 * @return
			 */
			moveit_msgs::JointConstraint getJointConstraint(const std::string& jointName, const double angle) const;

			/**
			 * Create a MoveIt! constraint message for a specific target position
			 * @param pose
			 * @return
			 */
			moveit_msgs::PositionConstraint getPositionConstraint(const geometry_msgs::PoseStamped& pose) const;

			/**
			 * Create a MoveIt! constraint message for a specific target orientation
			 * @param pose
			 * @return
			 */
			moveit_msgs::OrientationConstraint getOrientationConstraint(const geometry_msgs::PoseStamped& pose) const;

			/**
			 * Goal callback for move_to_joint_position action
			 */
			void moveToJointPositionGoalCB();

			/**
			 * Goal callback for move_to_cartesian_pose action
			 */
			void moveToCartesianPoseGoalCB();

			/**
			 * Goal callback for move_to_cartesian_pose_lin action
			 */
			void moveToCartesianPoseLinGoalCB();

			/**
			 * Goal reached callback for MoveIt!'s move_group action
			 * @param state
			 * @param result
			 */
			void moveGroupResultCB(const actionlib::SimpleClientGoalState& state, const moveit_msgs::MoveGroupResultConstPtr& result);

			/**
			 * Creates a MoveIt! move_group goal based on a target joint configuration
			 * @param goal
			 * @return
			 */
			moveit_msgs::MoveGroupGoal toMoveGroupGoal(const iiwa_msgs::MoveToJointPositionGoal::ConstPtr goal);

			/**
			 * Creates a MoveIt! move_group goal based on a Cartesian target pose
			 * @param goal
			 * @return
			 */
			moveit_msgs::MoveGroupGoal toMoveGroupGoal(const iiwa_msgs::MoveToCartesianPoseGoal::ConstPtr goal);

			/**
			 * Creates a MoveIt! move_group goal for a linear motion based on a Cartesian target pose
			 * @param goal
			 * @param startPose: Current pose of the end effector
			 * @return
			 */
			moveit_msgs::MoveGroupGoal toMoveGroupGoal(const iiwa_msgs::MoveToCartesianPoseGoal::ConstPtr goal, const geometry_msgs::PoseStamped& startPose);

			/**
			 * Initializes a goal for a move_group action without goal or trajectory constraints
			 * @param header
			 * @return
			 */
			moveit_msgs::MoveGroupGoal getBlankMoveItGoal(const std_msgs::Header& header) const;

			/**
			 * Interpolates two poses
			 * @param p1: First pose
			 * @param p2: Second pose
			 * @param w: Weight of p2 (0 >= w >=1).
			 * @return
			 */
			static tf::Pose interpolatePoses(const tf::Pose& p1, const tf::Pose& p2, const double w);

			/**
			 * Create a vector of waypoints on a straight line from p1 to p2
			 * @param p1: start pose (not part of trajectory)
			 * @param p2: target pose (part of trajectory)
			 * @param stepSize: distance between waypoints
			 * @return
			 */
			static std::vector<geometry_msgs::Pose> interpolateLinear(const geometry_msgs::Pose& p1, const geometry_msgs::Pose& p2, const double stepSize);

		protected:
			ros::NodeHandle _nh;
			tf::TransformListener _tfListener;

			// Action servers
			actionlib::SimpleActionServer<iiwa_msgs::MoveToJointPositionAction> _moveToJointPositionServer;
			actionlib::SimpleActionServer<iiwa_msgs::MoveToCartesianPoseAction> _moveToCartesianPoseServer;
			actionlib::SimpleActionServer<iiwa_msgs::MoveToCartesianPoseAction> _moveToCartesianPoseLinServer;

			// Action client
			actionlib::SimpleActionClient<moveit_msgs::MoveGroupAction> _moveGroupClient;
			int _moveGroupSeq = 1;

			// MoveIt! parameters
			std::string _moveGroup = "iiwa";
			int _numPlanningAttempts = 10;
			int _allowedPlanningTime = 5.0;
			int _maxVelocityScalingFactor = 1.0;
			int _maxAccelerationScalingFactor = 1.0;

			// Other parameters
			std::string _eeFrame = "iiwa_link_ee";
			double _stepSize = 0.001;
	};
}

#endif //SRC_IIWA_SIM_H