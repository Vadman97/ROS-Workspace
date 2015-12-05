#include "multimodal/receiveMsg.h"

ReceiveMsg::ReceiveMsg()
{

}

ReceiveMsg::~ReceiveMsg()
{

}

void ReceiveMsg::messageCallback(const kinect_bridge2::KinectBodies &msg)
{
    for (size_t body_idx = 0; body_idx < msg.bodies.size(); ++body_idx)
    {
        const auto & body = msg.bodies[body_idx];
        if (body.is_tracked)
        {
            std::cout << "Body: " << body_idx << " Lean X: " << body.lean.x;
            std::cout << " Lean Y: " << body.lean.y << std::endl;
        }
    }
}