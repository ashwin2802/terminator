#include <terminator/client.h>
#include <cstdlib>

int main(int argc, char **argv){

    ros::init(argc, argv, "client");

    // number of command line arguments must be only 2
    if(argc != 2){
        ROS_INFO("Usage: client SIG");
        return 1;
    }

    int signal = atoi(argv[1]);     // obtain value of signal from argument

    ros::NodeHandle nh;
    call(nh, signal);   // service call

    return 0;
}
