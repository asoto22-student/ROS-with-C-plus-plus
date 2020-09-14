#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include <std_msgs/Int32.h>

// Import all the necessary ROS libraries and import the Int32 message from the
// std_msgs package

int main(int argc, char **argv)
{
  ros::init(argc, argv, "topic_publisher"); // Initiate a Node named 'topic_publisher'
  ros::NodeHandle nh;

  ros::Publisher pub = nh.advertise<geometry_msgs::Twist>(
      "cmd_vel", 1000);   // Create a Publisher object, that will // publish on
                          // the /counter topic messages of type Int32
  ros::Rate loop_rate(2); // Set a publish rate of 2 Hz

  std_msgs::Int32 count; // Create a variable of type Int32
  count.data = 0;        // Initialize 'count' variable

  geometry_msgs::Twist var;
  geometry_msgs::Vector3 movement;
  geometry_msgs::Vector3 stop;

  movement.x = 0.25;

  var.linear = movement;

  while (ros::ok()) // Create a loop that will go until someone stops the
                    // program execution
  {
    pub.publish(var); // Publish the message within the 'count' variable
    ros::spinOnce();
    loop_rate.sleep(); // Make sure the publish rate maintains at 2 Hz
                       // var.linear.x = 1; // Increment 'count' variable
  }

  var.linear = stop;
  pub.publish(var);

  return 0;
}