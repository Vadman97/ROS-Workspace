#include "multimodal/receiveMsg.h"

int main(int argc, char **argv)
{
  // Set up ROS.
  //string is name of node
  ros::init(argc, argv, "multimodal");
  ros::NodeHandle nh;

  int rate = 30;

  // Create a new NodeExample object.
  ReceiveMsg *rxMsg = new ReceiveMsg();

  // Create a subscriber.
  // Name the topic, message queue, callback function with class name, and object containing callback function.
  ros::Subscriber sub_message = nh.subscribe("/kinect_client/bodies", 1000, &ReceiveMsg::messageCallback, rxMsg);

  // Tell ROS how fast to run this node.
  ros::Rate r(rate);

  // Main loop.
  while (nh.ok())
  {
    // std::cout << "SPIN" << std::endl;
    ros::spinOnce();
    r.sleep();
  }

  return 0;
}
