#pragma once
#include <opencv2/opencv.hpp>
#include <QImage>

QImage cvMat2QImage(const cv::Mat inMat);

QPointF cvPoint2QPointF(cv::Point point);
QVector<QPointF> StdVectorcvPoint2QVectorQPointF(std::vector<cv::Point>);


void getErrorContoursFromImg(const cv::Mat autoResImg, std::vector<std::vector<cv::Point>>& contoursExtra, std::vector<std::vector<cv::Point>>& contoursMiss);

std::vector<std::vector<cv::Point>> getIMG(std::vector<std::vector<cv::Point>>& img);