#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <sys/types.h>
#include <signal.h>  
#include <unistd.h>

void SendSignal(const std_msgs::Int32::ConstPtr& msg)
{
    int signal_types[] = {SIGINT, SIGTERM, SIGILL, SIGALRM, SIGABRT};

    for(int signal_index=0; signal_index<5; signal_index++) {
        int use_signal = signal_types[signal_index];
        int pid = msg->data;
        std::cout << "Used signal is: " << use_signal << std::endl; 
        kill(pid, use_signal);
        usleep(10000); // delay to check whether the program is closed or not
              
        if (kill(pid, 0) != 0){
            std::cout<<"exiting"<<std::endl;
            std::exit(0);
        }
    } 
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "pid_subscriber");
    ros::NodeHandle node;
    ros::Subscriber sub = node.subscribe("pid", 2, SendSignal);
    ros::spin();
    
    return 0;
}
