#include "mymainwindow.h"
#include <opencv2/opencv.hpp>
#include "methods.h"
//int main(int argc, char *argv[])
//{
//	QApplication a(argc, argv);
//
//	myMainWindow mainWin;
//	mainWin.show();
//
//	return a.exec();
//}

using namespace cv;

int main(int argc, char *argv[])
{
	Mat img = imread("D:/14-00-10_WHOLEVIEW.jpg");

	std::vector<std::vector<cv::Point>> dots;
	std::vector<cv::Point> subDots;

	subDots.push_back(Point(1, 2));
	subDots.push_back(Point(2, 3));
	dots.push_back(subDots);
	dots.push_back(subDots);

	std::vector<std::vector<cv::Point>> img4 = getIMG(dots);
	img4.clear();
	subDots.clear();
	subDots.push_back(Point(12, 34));
	img4.push_back(subDots);

	std::vector<std::vector<cv::Point>> img5;
	img5 = img4;

	std::cout << dots.size() << endl;
	std::cout << img4.size() << endl;

	std::vector<std::vector<cv::Point>> contours;
	std::vector<std::vector<cv::Point>> contoursMiss;

	getErrorContoursFromImg(img, contours, contoursMiss);
}