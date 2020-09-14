#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include <topic_subscriber_pkg/Age.h>

// Import all the necessary ROS libraries and import the Int32 message from the
// std_msgs package

int main(int argc, char** argv)
{
    ros::init(argc, argv, "topic_publisher");
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<topic_subscriber_pkg::Age>("age", 1000);

    topic_subscriber_pkg::Age msg;
    msg.years = 1997;
    msg.months = 7;
    msg.days = 14;

    pub.publish(msg);
    ros::spinOnce();

    return 0;
}