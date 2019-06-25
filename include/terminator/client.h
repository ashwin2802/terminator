#include <ros/ros.h>
#include <terminator/signal.h>

void call(ros::NodeHandle nh, int signal){
    
    ros::ServiceClient client = nh.serviceClient<terminator::signal>("terminate");  // service client to call service

    terminator::signal srv;           // service object to send request
    srv.request.signal = signal;    // feed signal into request

    if(client.call(srv)){   // if service call returns 1

        if(srv.response.success){   // if response returns true
        
            ROS_INFO("%s", "Service called successfully");
        }
        else{       // if response returns false

            ROS_INFO("%s", "Signal was ignored, the value must be -1, 0 or 1");
        }
    }
    else{          // if service call fails to return 1

        ROS_INFO("%s", "Failed to call service!");
    }

    return;
}
