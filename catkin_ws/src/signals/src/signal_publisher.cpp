#include <ros/ros.h>
#include <iostream> 
#include <csignal> 
#include <stdlib.h>
#include <ctime>
#include <std_msgs/Int32.h>
#include <unistd.h>

int chosen_type; //Global variable to use in signal handler
  
void signal_handler(int signal_num){ 

    if(signal_num == chosen_type){
        std::cout << "Interrupt signal is: " << signal_num << std::endl; 
        exit(signal_num);
    }

} 
  
int main (int argc, char **argv) {
    ros::init(argc, argv, "pid_publisher");
    ros::NodeHandle node;
    ros::Publisher pid_pub = node.advertise<std_msgs::Int32>("pid", 2);
    ros::Rate loop_rate(10);
    
    while (ros::ok()){
        std_msgs::Int32 msg;

        pid_t pid = getpid();
        msg.data = pid;

        pid_pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }    
    
    srand ( time(NULL) ); // change seed in order to get different rand_int
    int signal_types[] = {SIGINT, SIGTERM, SIGILL, SIGALRM, SIGABRT};
    int rand_int = rand() % 5;
    chosen_type = signal_types[rand_int];
    std::cout<<"chosen type is: " << chosen_type<<std::endl;
    
    return 0; 
}

