#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <sstream>
#include <iomanip>

#include <stdlib.h>
#include <stdint.h>


typedef struct {
	uint32_t time_stamp;

	float range[360];
}Laser;

typedef struct {
	float x;
	float y;
	float theta;
}Position;

int readLaserTXT( Laser *scan )
{
	int count = 0;
	std::string input_file_name = "laser_log.txt";
	std::ifstream input_file(input_file_name.c_str(), std::ifstream::in);

	if (!input_file.is_open()) {
		std::cout << "Failed to open file ..." << std::endl;
		exit(-1);
	}
	std::cout << "open file ..." << std::endl;

	std::string line;
	while (getline(input_file, line)) {
		//std::cout << line << std::endl;

		std::istringstream iss(line);
		std::string tag;
		iss >> tag;
		if (tag.compare("laser") == 0) {
			count++;
			for (int i = 0; i < 1440; i++) {
				iss >> scan[count].range[i];
			}
		}
	}
	return count;
}

int readOdomTXT( Position *pose )
{
	std::string input_file_name = "odom_log.txt";
	std::ifstream input_file(input_file_name.c_str(), std::ifstream::in);

	if (!input_file.is_open()) {
		std::cout << "Failed to open file ..." << std::endl;
		exit(-1);
	}
	std::cout << "open file ..." << std::endl;

	int count = 0;
	std::string line;
	while (getline(input_file, line)) {
		//std::cout << line << std::endl;

		std::istringstream iss(line);
		std::string tag;
		iss >> tag;
		if (tag.compare("odom") == 0) {
			//std::cout << "in here ..." << std::endl;
			count++;
			iss >> pose[count].x;
			iss >> pose[count].y;
			iss >> pose[count].theta;
		}
	}

	for (int i = 0; i < count; i++) {
		std::cout << "pose.x = " << pose[i + 1].x << std::endl;
		std::cout << "pose.y = " << pose[i + 1].y << std::endl;
		std::cout << "pose.theta = " << pose[i + 1].theta << std::endl;
	}
	return count;
}

int main()
{
	
	return 0;
}
