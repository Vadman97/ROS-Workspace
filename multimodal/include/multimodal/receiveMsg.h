// ROS includes.
#include "ros/ros.h"
#include "ros/time.h"

// Custom message includes. Auto-generated from msg/ directory.
#include "kinect_bridge2/KinectBodies.h"


class ReceiveMsg
{
public:
    ReceiveMsg();
    ~ReceiveMsg();

    void messageCallback(const kinect_bridge2::KinectBodies &msg);
    
};