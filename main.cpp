#include<iostream>
#include"DTW.h"

#define M_PI 3.14159265358979323846


int main(int argc, char* argv[]) {

	std::vector<double> data1, data2;
	const int numData1 = 30;
	const int numData2 = 60;
	
	const double period1 = 10;
	const double period2 = 20;

	for (int i = 0; i < numData1; ++i) {
		data1.push_back(std::sin(2 * M_PI * i / period1));
	}

	for (int i = 0; i < numData2; ++i) {
		data2.push_back(std::sin(2 * M_PI * i / period2));
	}

	std::vector<std::vector<double>> DTWarray = calcDTW(data1, data2);
	std::vector<std::vector<int>> minPath = getMinPath(DTWarray);

	for (int i = 0; i < minPath.size(); ++i) {
		std::cout << minPath[i][0] << ", " << minPath[i][1] << std::endl;
	}

	system("pause");

	return 0;
}