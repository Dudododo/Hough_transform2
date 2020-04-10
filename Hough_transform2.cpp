#include <iostream>
#include <opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	cv::Mat srcMat = imread("metal-part-distorted-03.png", 1);
	cv::Mat dstMat;
	cv::Mat dx, dy;

	//边缘提取
	cv::Sobel(srcMat, dx, CV_16SC1, 1, 0, 3, 1, 0, BORDER_DEFAULT);
	cv::Sobel(srcMat, dy, CV_16SC1, 0, 1, 3, 1, 0, BORDER_DEFAULT);
	cv::Canny(dx, dy, dstMat, 150, 200);

	std::vector<cv::Vec4i> lines;
	HoughLinesP(dstMat, lines, 1, CV_PI / 180, 50, 0, 20);

	for (int i = 0; i < lines.size(); i++)
	{
		line(srcMat, Point(lines[i][0], lines[i][1]), Point(lines[i][2], lines[i][3]), Scalar(0, 0, 255), 1, LINE_AA);
	}

	cv::imshow("srcMat", srcMat);
	cv::imshow("dstMat", dstMat);
	waitKey(0);
}
