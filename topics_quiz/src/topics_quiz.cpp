#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>

// Import all the necessary ROS libraries and import the Int32 message from the
// std_msgs package

float frontDist, leftDist, rightDist;

void ParseMessage(const sensor_msgs::LaserScan::ConstPtr& msg)
{
    frontDist = msg->ranges[360];
    leftDist = msg->ranges[719];
    rightDist = msg->ranges[0];
    ros::spinOnce();
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "topic_quiz");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 10);
    ros::Subscriber sub = nh.subscribe("/kobuki/laser/scan", 1000, ParseMessage);
    
    ros::Rate loop_rate(100);
    geometry_msgs::Twist forward, rightTurn, leftTurn, stop;
    forward.linear.x = 0.25f;
    rightTurn.angular.z = 0.25f;
    leftTurn.angular.z = 0.25f;

    while(ros::ok())
    {
        if (frontDist > 1) { pub.publish(forward); }
        else { pub.publish(leftTurn); }

        if (rightDist < 1) { pub.publish(leftTurn); }
        if (leftDist < 1) { pub.publish(rightTurn); }

        ros::spinOnce();
        //loop_rate.sleep();
    }

    ros::spin();
    return 0;
}