#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>

ros::Publisher twist_pub;

geometry_msgs::Twist v;

void sonarcallback(const std_msgs::Float32ConstPtr &msg){
    
    std::cout << "Recebi: " << msg->data << std::endl;
    
    if(msg->data == 0){
        v.linear.x = 5;
        v.angular.z = 0;
    }
    else{
        v.linear.x = -1;
        v.angular.z = 3;
    }
    
    twist_pub.publish(v);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "simple_avoidance");
    
    ros::NodeHandle node;
    
    twist_pub = node.advertise<geometry_msgs::Twist>("Velocity", 1);
    
    ros::Subscriber sonar_sub = node.subscribe("/vrep/vehicle/frontSonar", 1, sonarcallback);
    
    ros::spin();
    
    return 0;
}