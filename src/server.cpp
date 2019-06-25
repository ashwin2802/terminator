#include <ros/ros.h>
#include <std_msgs/Int64.h>
#include <executor/signal.h>

#define exit flag == -1
#define run flag == 1

int flag = 1;   // execution flag variable

                /*  run publishers and subscribers when flag is 1,
                    stop publishers and subscribers when flag is 0,
                    kill the node when flag is -1.                  */

int data = 0;   // data variable

// handle service call
bool process(executor::signal::Request &req, executor::signal::Response &res){
    
    // process request
    switch(req.signal){

        /* set flag and respond successful 
            if signal from call is -1, 0 or 1 */

        case -1:    
        case 0:
        case 1: flag = req.signal; 
                res.success = true; 
                break;

        /* leave flag unchanged and respond unsuccessful 
                    if signal from call is not -1, 0 or 1 */

        default: res.success = false; 
                 break;

    }
    return true;    // request processed successfully
}

// subscriber callback
void callback(const std_msgs::Int64& msg){

    // retrieve data if flag is 1, else pass through
    if(run){

        data = msg.data;    // update data variable
        // ROS_INFO("%d", data); // (debug) echo data from subscriber

    }
    return;
}

int main(int argc, char **argv){

    ros::init(argc, argv, "server");    // initialize server
    ros::NodeHandle nh;

    ros::ServiceServer server = nh.advertiseService("execute", process);  // server object
    ros::Subscriber sub = nh.subscribe("input", 10, callback);           // data subscriber
    ros::Publisher pub = nh.advertise<std_msgs::Int64>("output", 10);   // data publisher
    
    ros::Rate pubRate(10);  // publish rate
    std_msgs::Int64 msg;    // message object

    // execution loop
    while(ros::ok() && !(exit))
    {
        // publish messages if flag is 1, else pass through
        if(run){
            
            msg.data = data;    // add data to message
            pub.publish(msg);   // publish message
            pubRate.sleep();    // control message rate

        }

        ros::spinOnce();    // update callback and check for service calls
    }
    return 0;
}