#include <iostream>
#include <opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	cv::Mat srcMat = imread("metal-part-distorted-03.png", 0);
	cv::Mat binMat, dstMat;
	cv::Mat dx, dy;

	//二值化
	threshold(srcMat, binMat, 100, 255, THRESH_BINARY);

	//边缘提取
	cv::Sobel(srcMat, dx, CV_16SC1, 1, 0, 3, 1, 0, BORDER_DEFAULT);
	cv::Sobel(srcMat, dy, CV_16SC1, 0, 1, 3, 1, 0, BORDER_DEFAULT);
	cv::Canny(dx, dy, dstMat, 150, 200);

	//霍夫变换
	std::vector<cv::Vec4i> lines;
	cv::HoughLines(dstMat, lines, 1, CV_PI / 180, 100);

	//绘制直线
	std::vector<cv::Vec4i>::iterator it = lines.begin();
	for (; it != lines.end(); ++it)
	{
		float rho = (*it)[0], theta = (*it)[1];
		cv:Point pt1, pt2;
		double a = cos(theta);
		double b = sin(theta);
		double x0 = a * rho;
		double y0 = b * rho;
		pt1.x = cv::saturate_cast<int>(x0 + 1000 * (-b));
		pt1.y = cv::saturate_cast<int>(y0 + 1000 * (a));
		pt2.x = cv::saturate_cast<int>(x0 - 1000 * (-b));
		pt2.y = cv::saturate_cast<int>(y0 - 1000 * (a));
		cv::line(srcMat, pt1, pt2, cv::Scalar(0, 0, 255), 1, LINE_AA);
	}

	imshow("srcMat", srcMat);
	imshow("binMat", binMat);
	imshow("dstMat", dstMat);
	waitKey(0);
}

