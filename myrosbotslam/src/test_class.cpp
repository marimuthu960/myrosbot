
//wsn, Feb 2015
//illustrates how to use classes to make ROS nodes
// constructor can do the initialization work, including setting up subscribers, publishers and services
// can use member variables to pass data from subscribers to other member functions

// can test this function manually with terminal commands, e.g. (in separate terminals):
// rosrun basic1 example_ros_class
// rostopic echo exampleMinimalPubTopic
// rostopic pub -r 4 exampleMinimalSubTopic std_msgs/Float32 2.0
// rosservice call exampleMinimalService 1


// this header incorporates all the necessary #include files and defines the class "ExampleRosClass"

#include "test_class/test_header.h"
using namespace std;

//CONSTRUCTOR:  this will get called whenever an instance of this class is created
// want to put all dirty work of initializations here
// odd syntax: have to pass nodehandle pointer into constructor for constructor to build subscribers, etc
mainclass::mainclass(ros::NodeHandle* nodehandle):nh(*nodehandle)
{ // constructor
    ROS_INFO("in class constructor of ExampleRosClass");

    //i=0.1;


    //initializeSubscribers(); // package up the messy work of creating subscribers; do this overhead in constructor

    ROS_INFO("Initializing Publishers");
    velocity_publisher= nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);

    //initializeServices();

    //initialize variables here, as needed

    
    // can also do tests/waits to make sure all required services, topics, etc are alive
}

//member helper function to set up subscribers;
// note odd syntax: &ExampleRosClass::subscriberCallback is a pointer to a member function of ExampleRosClass
// "this" keyword is required, to refer to the current instance of ExampleRosClass

/*void ExampleRosClass::initializeSubscribers()
{
    ROS_INFO("Initializing Subscribers");
    minimal_subscriber_ = nh_.subscribe("exampleMinimalSubTopic", 1, &ExampleRosClass::subscriberCallback,this);  
    // add more subscribers here, as needed
}*/

//member helper function to set up services:
// similar syntax to subscriber, required for setting up services outside of "main()"

/*void ExampleRosClass::initializeServices()
{
    ROS_INFO("Initializing Services");
    minimal_service_ = nh_.advertiseService("exampleMinimalService",
                                                   &ExampleRosClass::serviceCallback,
                                                   this);  
    // add more services here, as needed
}*/

//member helper function to set up publishers;





// a simple callback function, used by the example subscriber.
// note, though, use of member variables and access to minimal_publisher_ (which is a member method)

/*void ExampleRosClass::subscriberCallback(const std_msgs::Float32& message_holder) {
    // the real work is done in this callback function
    // it wakes up every time a new message is published on "exampleMinimalSubTopic"

    val_from_subscriber_ = message_holder.data; // copy the received data into member variable, so ALL member funcs of ExampleRosClass can access it
    ROS_INFO("myCallback activated: received value %f",val_from_subscriber_);
    std_msgs::Float32 output_msg;
    val_to_remember_ += val_from_subscriber_; //can use a member variable to store values between calls; add incoming value each callback
    output_msg.data= val_to_remember_;
    // demo use of publisher--since publisher object is a member function
    minimal_publisher_.publish(output_msg); //output the square of the received value; 
}*/


//member function implementation for a service callback function
/*bool ExampleRosClass::serviceCallback(example_srv::simple_bool_service_messageRequest& request, example_srv::simple_bool_service_messageResponse& response) {
    ROS_INFO("service callback activated");
    response.resp = true; // boring, but valid response info
    return true;
}*/


void mainclass:: move(double speed, double distance, bool direction, double *current_distance,double *t0)
{

    double time=0;
    geometry_msgs::Twist vel_msg;
    if (direction)
        vel_msg.linear.x = std::abs(speed);
    else
        vel_msg.linear.x = -std::abs(speed);
    vel_msg.linear.y = 0;
    vel_msg.linear.z = 0;
    // set a random angular velocity in the y-axis
    vel_msg.angular.x = 0;
    vel_msg.angular.y = 0;
    vel_msg.angular.z = 0;

    if (*t0 ==0.0){
    double mytime= ros::Time::now().toSec();
    *t0 = mytime;
    //double current_distance = 0.0;
    }

    if(*current_distance<=distance)
    {
        velocity_publisher.publish(vel_msg);
        double t1 = ros::Time::now().toSec();
        *current_distance = speed * (t1 - *t0);
        time= t1 - *t0;
        cout <<"current distance :" << *current_distance <<endl;
        cout <<"Time :" << time <<endl;
        ros::spinOnce();

    }
    else if (*current_distance>distance) {
    vel_msg.linear.x = 0;
    velocity_publisher.publish(vel_msg);
    }

    //cout <<"Final distance :" << current_distance <<endl;
    //cout <<"Timet :" << time <<endl;
    //cout <<"constructor value checking:" << i <<endl;


}


void mainclass:: mainloop(){

    ros::Rate loop_rate(10);
    double currentdistance=0.0;
    double t0=0.0;
    ROS_INFO("Cleaner Started");
    while(ros::ok()){
        mainclass::move(2.0, 5.0, 1,&currentdistance,&t0);
        loop_rate.sleep();
    }

}


int main(int argc, char** argv)
{
    // ROS set-ups:
    ros::init(argc, argv, "test_class"); //node name

    ros::NodeHandle nh; // create a node handle; need to pass this to the class constructor

    ROS_INFO("main: instantiating an object of type ExampleRosClass");

    //instantiate an object and pass in pointer to nodehandle for constructor to use
    mainclass m(&nh);

    m.mainloop();

    return 0;
}

