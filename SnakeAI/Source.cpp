#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>

#include "SnakeBoard.h"

int main()
{
	try {
		cv::Mat img = cv::Mat::zeros(500, 500, CV_8UC3);
		
		SnakeBoard board(10, 10);
		board.print(img);
		
		cv::imshow("Snake AI", img);
		cv::waitKey(2000);
	}
	catch (std::exception & e) {
		cout << "Exception caught in " << __FUNCTION__ << ": "
			<< e.what() << '\n';
	}

	//cout << "Press any key to continue . . .";
	//cin.get();
	return 0;
}
