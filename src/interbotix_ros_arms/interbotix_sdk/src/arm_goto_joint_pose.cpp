#include "interbotix_sdk/arm_obj.h"
#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <ros/package.h>
#include <cstdlib>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <cmath>
#include <tf/tf.h>
#include <tf/transform_listener.h>
#include <std_msgs/Header.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PointStamped.h>
#include <sensor_msgs/JointState.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/PointCloud2.h>
#include <interbotix_sdk/JointCommands.h>

using namespace cv;
using namespace std;

interbotix_sdk::JointCommands joint_pose;

int main( int argc, char** argv )
{
    ros::init(argc, argv, "arm_goto_joint_pose");
    ros::NodeHandle n;
    double home[8] = {0.12425244599580765, -0.4724660813808441, -1.2732040882110596, 0.8666991591453552, 0.010737866163253784, 1.1873011589050293, 0.03640443919564078, -0.03640443919564078},
	   pick[8] = {0.016873789951205254, 0.010737866163253784, -0.699495255947113, -0.7056311964988708, 0.015339808538556099, -0.004601942375302315, 0.019429268134630993, -0.019429268134630993},
	   v_goal[9] = {1.4894953966140747, -0.7731263637542725, -0.3436117172241211, -0.05062136799097061, -0.3681553900241852, -0.03528155758976936, 0.004601942375302315, 0.028597034058107578, -0.028597034058107578},
   	   v_home[9] = {1.4894953966140747, -0.47860202193260193, -1.1535536050796509, -0.023009711876511574, 0.826815664768219, -0.03681553900241852, 0.004601942375302315, 0.028597034058107578, -0.028597034058107578},
	   drop[8] = {0.10124273598194122, -0.7623884677886963, -0.3405437469482422, -0.3834952116012573, 0.013805827125906944, 1.1873011589050293, 0.03640443919564078, -0.03640443919564078};
    vector<double> home_array(home,home+8),pick_array(pick,pick+8),v_goal_array(v_goal,v_goal+9),v_home_array(v_home,v_home+9),drop_array(drop,drop+8);

    //ros::Publisher joint_pose_pub = n.advertise<interbotix_sdk::JointCommands>("/wx200/joint/commands", 0);
    ros::Publisher joint_pose_pub = n.advertise<interbotix_sdk::JointCommands>("/vx300s/joint/commands", 0);

    ros::Duration(1.5).sleep();
    joint_pose.cmd = v_home_array;
    ROS_INFO("OK");
    ros::Duration(2.5).sleep();
    joint_pose_pub.publish(joint_pose);

    joint_pose.cmd = v_goal_array;
    ROS_INFO("OK");
    ros::Duration(2.5).sleep();
    joint_pose_pub.publish(joint_pose);
/*
    joint_pose.cmd = pick_array;
    ROS_INFO("OK");
    ros::Duration(2.5).sleep();
    joint_pose_pub.publish(joint_pose);

    joint_pose.cmd = goal_array;
    ROS_INFO("OK");
    ros::Duration(2.5).sleep();
    joint_pose_pub.publish(joint_pose);

    joint_pose.cmd = place_array;
    ROS_INFO("OK");
    ros::Duration(2.5).sleep();
    joint_pose_pub.publish(joint_pose);
*/

    ros::spinOnce();
    return 0;
}
