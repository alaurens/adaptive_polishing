#include "adaptive_polishing.h"

// #include "ros/ros.h"
// #include <vector>


int main(int argc, char **argv)
{
  ros::init(argc, argv, "adaptive_polishing_node");

  ros::NodeHandle nh;
  double frequency = 250.0;


  // Parameters
  std::string input_topic_name;
  std::string output_topic_name;
  std::string output_filtered_topic_name;

  //trajectory parameters
  std::vector<double> CenterRotation;
  double radius;
  double RotationSpeed;
  double ConvergenceRate;

  int my_int_param;
  std::vector<double> my_vec_param;


   if (!nh.getParam("input_topic_name", input_topic_name))   {
    ROS_ERROR("Couldn't retrieve the topic name for the input. ");
    // return -1;
  }

  if (!nh.getParam("output_topic_name", output_topic_name))   {
    ROS_ERROR("Couldn't retrieve the topic name for the output. ");
    // return -1;
  }

  if (!nh.getParam("output_filtered_topic_name", output_filtered_topic_name))   {
    ROS_ERROR("Couldn't retrieve the topic name for the filtered output. ");
    // return -1;
  }

  if (!nh.getParam("CenterRotation", CenterRotation))   {
    ROS_ERROR("Couldn't retrieve the center of rotation. ");
    // return -1;
  }

  if (!nh.getParam("radius", radius))   {
    ROS_ERROR("Couldn't retrieve the radius of the rotation. ");
    // return -1;
  }

  if (!nh.getParam("RotationSpeed", RotationSpeed))  {
    ROS_ERROR("Couldn't retrieve the rotation speed.");
    // return -1;
  }

  if (!nh.getParam("ConvergenceRate", ConvergenceRate)) {
    ROS_ERROR("Couldn't retrieve the convergence speed. ");
    // return -1;
  }

  ROS_INFO("Starting the Motion generator... and guess what? doing nothing!");

  Adaptive_polishing my_adaptive_polishing(
    nh,
    frequency,
    input_topic_name,
    output_topic_name,
    output_filtered_topic_name,
    CenterRotation,
    radius,
    RotationSpeed,
    ConvergenceRate);

  if (!my_adaptive_polishing.Init()) {
    return -1;
  }
  else {
    my_adaptive_polishing.Run();
  }


  return 0;
}