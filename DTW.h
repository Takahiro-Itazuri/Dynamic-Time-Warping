#ifndef _DTW_HPP_
#define _DTW_HPP_

#include<iostream>
#include<vector>

std::vector<std::vector<double>> calcDTW(const std::vector<double>& data1, const std::vector<double>& data2) {
	const int numData1 = data1.size();
	const int numData2 = data2.size();

	//　エラー処理
	if (numData1 == 0 || numData2 == 0) {
		std::cerr << "Invalid data: data length is 0." << std::endl;
		return std::vector<std::vector<double>>(0, std::vector<double>(0));
	}

	// 配列の初期化
	std::vector<std::vector<double>> DTWarray(numData1 + 1, std::vector<double>(numData2 + 1));

	DTWarray[0][0] = 0;
	for (int i = 1; i < numData1 + 1; ++i) {
		DTWarray[i][0] = INFINITY;
		DTWarray[0][i] = INFINITY;
	}

	// 計算
	for (int i = 0; i < numData1; ++i) {
		for (int j = 0; j < numData2; ++j) {
			double cost = sqrt(pow(data1[i] - data2[j], 2.0));

			double min = DTWarray[i][j];
			if (min > DTWarray[i][j + 1]) min = DTWarray[i][j + 1];
			if (min > DTWarray[i + 1][j]) min = DTWarray[i + 1][j];

			DTWarray[i + 1][j + 1] = cost + min;
		}
	}

	return DTWarray;
}

std::vector<std::vector<int>> getMinPath(const std::vector<std::vector<double>>& DTWarray) {
	std::vector<std::vector<int>> inverseMinPath;
	
	const int numData1 = DTWarray.size() - 1;
	const int numData2 = DTWarray[0].size() - 1;

	std::vector<int> buf(2);

	int posX = numData1;
	int posY = numData2;
	buf[0] = posX - 1;
	buf[1] = posY - 1;
	inverseMinPath.push_back(buf);
	
	while (!(posX == 1 && posY == 1)) {
		if (posX == 1) { posY--; }
		else if (posY == 1) { posX--; }
		else {
			double min = DTWarray[posX - 1][posY - 1];
			double minPosX = posX - 1;
			double minPosY = posY - 1;

			if (min >= DTWarray[posX - 1][posY]) {
				min = DTWarray[posX - 1][posY];
				minPosX = posX - 1;
				minPosY = posY;
			}

			if (min >= DTWarray[posX][posY - 1]) {
				min = DTWarray[posX][posY - 1];
				minPosX = posX;
				minPosY = posY - 1;
			}

			posX = minPosX;
			posY = minPosY;
			buf[0] = posX - 1;
			buf[1] = posY - 1;
			inverseMinPath.push_back(buf);
		}
	}

	std::vector<std::vector<int>> minPath;
	int numPath = inverseMinPath.size();
	for (int i = 0; i < numPath; ++i) {
		minPath.push_back(inverseMinPath[numPath - i - 1]);
	}
	
	return minPath;
}

#endif