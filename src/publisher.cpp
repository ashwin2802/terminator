#include <ros/ros.h>
#include <std_msgs/Int64.h>

int data = 0;   // data variable

int main(int argc, char **argv){

    ros::init(argc, argv, "publisher");    // initialize data publisher
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<std_msgs::Int64>("input", 10);    // publisher object
    ros::Rate pubRate(10);  // define publish rate
    std_msgs::Int64 msg;    // message object

    // execution loop
    while(ros::ok())
    {
        msg.data = data++;  // add data to message
        pub.publish(msg);   // publish the message
        if(data > (int)10E4) data = 0;  // reset when value gets large
        pubRate.sleep();    // control message rate
    }

    return 0;
}