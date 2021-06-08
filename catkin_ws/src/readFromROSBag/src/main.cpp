#include <ros/ros.h>

#include <sensor_msgs/LaserScan.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int count = 0;
std::ofstream outfile;

void laserCallback( const sensor_msgs::LaserScan::ConstPtr &scan )
{
	std::cout<<"laser call back ..."<<scan->ranges.size()<<std::endl;
	count ++;
	if( count == 1 ){
		outfile << "angle_min: "<<scan->angle_min<<std::endl;
		outfile <<"angle_max: "<<scan->angle_max<<std::endl;
		outfile <<"angle_increment: "<<std::ios::fixed<<std::setprecision(10)<<scan->angle_increment<<std::endl;
		outfile <<"time_increment: "<<std::ios::fixed<<std::setprecision(10)<<scan->time_increment<<std::endl;
		outfile <<"range_min: "<<std::ios::fixed<<std::setprecision(10)<<scan->range_min<<std::endl;
		outfile <<"range_max: "<<std::ios::fixed<<std::setprecision(10)<<scan->range_max<<std::endl;
		outfile <<"ranges_size: "<<scan->ranges.size()<<std::endl;
	}
	outfile<<"laser ";
	for( auto it : scan->ranges ){
	//	outfile << std::ios::fixed<<std::setprecision(10) << it << " ";
		outfile <<it<<" ";
	}
	outfile<<std::endl;
}

int main( int argc, char **argv )
{
	std::cout<<"Program Begins ..."<<std::endl;
	ros::init( argc, argv, "ReadData" );

	ros::NodeHandle n;

	ros::Subscriber lidar_sub = n.subscribe<sensor_msgs::LaserScan>("/laser_scan", 1, laserCallback);

	// ---------- open the file --------------//
	outfile.open( "./laser_data.txt", std::ios::app );
	if( !outfile.is_open() ){
		std::cerr<<"open file failed ..."<<std::endl;
		exit(-1);
	}

	ros::spin();

	outfile.close();
	return 0;
}
