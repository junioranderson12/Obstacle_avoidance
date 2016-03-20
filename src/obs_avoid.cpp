#include <ros/ros.h>
//#include <std_msgs/String.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>

ros::Publisher twist_pub;
//std_msgs::Float32 msg_sonar;
geometry_msgs::Twist velocidade;

//Assim que o subscritor receber uma mensagem ela será impressa
void sonar_callback(const std_msgs::Float32ConstPtr &msg)
{
    //ROS_INFO("Received: %s", msg->data.c_str());
    std::cout << "Received: " << msg->data << std::endl;
    if (msg->data != 0){
        velocidade.linear.x = 0;
        velocidade.angular.z = 1;
    }
    else{
        velocidade.linear.x = 0.2;
        velocidade.angular.z = 0; 
    }
    //msg_counter.data = counter;
    //pub.publish(msg_counter);
    twist_pub.publish(velocidade);
}

int main(int argc, char **argv)
{
    //Inicializa o ROS
    ros::init(argc,argv,"obstacle_avoidance");
    
    //Cria o nó
    ros::NodeHandle node;
    
    //Define um subscritor definindo o tópico "ros_World"
    //Tamanho do buffer = 1 e função a ser chamada ao receber uma
    //mensagem será callback
    ros::Subscriber sonar_sub = node.subscribe("/vrep/vehicle/frontSonar", 1, sonar_callback);
    
    //pub = node.advertise <std_msgs::Int32>("ros_world/counter",1);
    // Declare topic to be published
    twist_pub = node.advertise <geometry_msgs::Twist>("obstacle/twist",1);
    //Faz o ROS ficar rodando o tempo todo
    ros::spin();  
}