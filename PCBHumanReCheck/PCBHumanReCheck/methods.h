#pragma once
#include <opencv2/opencv.hpp>
#include <QImage>

QImage cvMat2QImage(const cv::Mat inMat);

QPointF cvPoint2QPointF(cv::Point point);
QVector<QPointF> StdVectorcvPoint2QVectorQPointF(std::vector<cv::Point>);
cv::Point QPointF2cvPoint(QPointF point);
std::vector<cv::Point> QVectorQPointF2StdVectorcvPoint(QVector<QPointF> qPoints);

bool isSameDVecPt(std::vector<std::vector<cv::Point> > Pts1, std::vector<std::vector<cv::Point> > Pts2);

static void _split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);
std::string changePathDirt(std::string folderPath);
QString changePathDirt(QString folderPath);

void eraseOneContour(std::vector<std::vector<cv::Point> >& allContours, std::vector<cv::Point> oneContour);

void getErrorContoursFromImg(const cv::Mat autoResImg, std::vector<std::vector<cv::Point> >& contoursExtra, std::vector<std::vector<cv::Point> >& contoursMiss);

std::vector<std::vector<cv::Point> > getIMG(std::vector<std::vector<cv::Point> >& img);