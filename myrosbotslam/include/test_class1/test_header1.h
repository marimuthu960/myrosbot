
// include this file in "test_class.cpp"

// here's a good trick--should always do this with header files:
// create a unique mnemonic for this header file, so it will get included if needed,
// but will not get included multiple times
#ifndef TURTLESIM_CLEAN_CLASS1_H_
#define TURTLESIM_CLEAN_CLASS1_H_

//some generically useful stuff to include...
#include <ros/ros.h>
#include "geometry_msgs/Twist.h"

// define a class, including a constructor, member variables and member functions
class mainclass
{

private:

    ros::NodeHandle nh; // we will need this, to pass between "main" and constructor


    //ros::Subscriber minimal_subscriber_;
    //ros::ServiceServer minimal_service_;
    ros::Publisher velocity_publisher;
    //double val_from_subscriber_; //example member variable: better than using globals; convenient way to pass data from a subscriber to other member functions

    //void subscriberCallback(const std_msgs::Float32& message_holder); //prototype for callback of example subscriber

    //bool serviceCallback(example_srv::simple_bool_service_messageRequest& request, example_srv::simple_bool_service_messageResponse& response);


public:


//passing variable constructor
    mainclass(ros::NodeHandle* nodehandle); //"main" will need to instantiate a ROS nodehandle, then pass it to the constructor

//our methods
    void move(double speed, double distance, bool direction,double *current_distance,double* startingtime);
    void mainloop();

	
};
#endif
