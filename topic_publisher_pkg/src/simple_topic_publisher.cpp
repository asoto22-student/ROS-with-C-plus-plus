#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include <std_msgs/Int32.h>

// Import all the necessary ROS libraries and import the Int32 message from the
// std_msgs package

int main(int argc, char **argv) {
  ros::init(argc, argv, "topic_publisher");
  ros::NodeHandle nh;

  // ros::Publisher pub = nh.advertise<std_msgs>("count", 1000);
  ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  ros::Rate loop_rate(2);

  // std_msgs::Int32 count;
  // count.data = 0;

  geometry_msgs::Twist var;
  var.linear.x = 0.25;
  var.angular.z = 0.25;

  int loop = 0;

  while (ros::ok()) {
    pub.publish(var);
    ros::spinOnce();
    loop_rate.sleep();
    loop++;
    if (loop > 50) {
      break;
    }
  }

  var.linear.x = 0;
  var.angular.z = 0;
  pub.publish(var);

  return 0;
}