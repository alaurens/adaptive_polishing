#ifndef __ATTRACTOR_DS_H__
#define __ATTRACTOR_DS_H__

#include <string.h>
#include <sstream>

#include "MotionGenerator.h"

#include "geometry_msgs/Pose2D.h"
#include "geometry_msgs/Pose.h"
#include "std_msgs/Int32.h"
#include "adaptive_polishing/attractor_msg.h"

#include "MathLib.h"
#include <vector>

#include <dynamic_reconfigure/server.h>
#include <adaptive_polishing/attractor_paramsConfig.h>

class AttractorDS : public MotionGenerator {

private:

	struct Parameter{
		double val;
		bool adapt;
		double min;
		double max;
	};

	ros::Publisher pub_attractor_info_;
	adaptive_polishing::attractor_msg msg_attractor_info_;
	
	//publisher and msg to publish the cycle target when it is adapting
	geometry_msgs::Pose msg_attractor_target_;
	ros::Publisher pub_attractor_target_;

	//subscriber to listen to active node
	ros::Subscriber sub_active_node_;
	int nodeNum_;

	// Motion detail
	std::vector<Parameter> parameters_;
	double Convergence_Rate_;
	double Convergence_Rate_scale_;


	// Adaptation parameters
	double Grad_desc_step_; //step for numerical derivation
	double Grad_desc_epsilon_; // epsilon for state adaptation

	//dynamic reconfig setting
	dynamic_reconfigure::Server<adaptive_polishing::attractor_paramsConfig> dyn_rec_srv_;
	dynamic_reconfigure::Server<adaptive_polishing::attractor_paramsConfig>::CallbackType dyn_rec_f_;



public:
	AttractorDS(ros::NodeHandle &n,
			double frequency,
			std::string input_rob_pos_topic_name,
			std::string input_rob_vel_topic_name,
			std::string input_rob_acc_topic_name,
			std::string input_rob_force_topic_name,
			std::string input_active_node_topic_name,
			std::string output_vel_topic_name,
			std::string output_target_topic_name,
			std::string output_filtered_vel_topic_name,
			std::vector<double> parameters,
			std::vector<double> min_parameters,
			std::vector<double> max_parameters,
			std::vector<double> adaptable_parameters,
			double ConvergenceRate,
			bool adaptable,
			int nodeNum = 0
	);

private:

	void DynCallback(adaptive_polishing::attractor_paramsConfig &config, 
			uint32_t level);

	virtual Eigen::Vector3d GetVelocityFromPose(Eigen::Vector3d pose) override;

	void AdaptTrajectoryParameters(Eigen::Vector3d pose) override;

	void checkActiveNode(const std_msgs::Int32::ConstPtr& msg);




};


#endif // __ATTRACTOR_DS_H__