// This header defines the standard RO classes.
#include <ros/ros.h>

int main(int argc, char **argv){

    // Initialize the ROS system.
    ros::init(argc, argv, "turtle_crazy");

    // Establish this program as a ROS node.
    ros::NodeHandle nh;

    // Send some output as a log message
    for(int i=0; i<7; i++){
	    system("rostopic pub -1 /turtle1/cmd_vel geometry_msgs/Twist -- '{linear: {x: 1.1, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 1.0}}'");
    }
    return 0;
}
