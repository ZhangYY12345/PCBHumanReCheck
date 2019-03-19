#include "methods.h"
#include "parameters.h"

QImage cvMat2QImage(const cv::Mat inMat)
{
	switch (inMat.type()) {
	case CV_8UC1: // 8-bit, 1 channel
	{
		static QVector<QRgb> sColorTable(256);
		for (int i = 0; i < 256; ++i) {
			sColorTable[i] = qRgb(i, i, i);
		}
		QImage image(inMat.data,
			inMat.cols, inMat.rows,
			static_cast<int>(inMat.step),
			QImage::Format_Indexed8);
		image.setColorTable(sColorTable);
		return image;
	}
	case CV_8UC3: // 8-bit, 3 channel
	{
		QImage image(inMat.data,
			inMat.cols, inMat.rows,
			static_cast<int>(inMat.step),
			QImage::Format_RGB888);
		//return image;
		return image.rgbSwapped();
	}
	case CV_8UC4: // 8-bit, 4 channel
	{
		QImage image(inMat.data,
			inMat.cols, inMat.rows,
			static_cast<int>(inMat.step),
			QImage::Format_ARGB32);
		return image;
	}
	default:
		break;
	}


	return QImage();
}

QPointF cvPoint2QPointF(cv::Point point)
{
	QPointF qPoint = QPointF(point.x, point.y);
	return qPoint;
}

QVector<QPointF> StdVectorcvPoint2QVectorQPointF(std::vector<cv::Point> stdVecPts)
{
	QVector<QPointF> QVecPts;
	for (std::vector<cv::Point>::iterator iter = stdVecPts.begin(); iter != stdVecPts.end(); ++iter) {
		QVecPts.push_back(cvPoint2QPointF(*iter));
	}
	return QVecPts;
}

cv::Point QPointF2cvPoint(QPointF point)
{
	cv::Point cvPoint = cv::Point(static_cast<int>(point.x()), static_cast<int>(point.y()));
	return cvPoint;
}

std::vector<cv::Point> QVectorQPointF2StdVectorcvPoint(QVector<QPointF> qPoints)
{
	std::vector<cv::Point> stdVecPoint;
	for (QVector<QPointF>::iterator iter = qPoints.begin(); iter != qPoints.end(); ++iter) {
		stdVecPoint.push_back(QPointF2cvPoint(*iter));
	}
	return stdVecPoint;
}

void eraseOneContour(std::vector<std::vector<cv::Point> > allContours, std::vector<cv::Point> oneContour)
{
	for(std::vector<std::vector<cv::Point> >::iterator itor = allContours.begin(); itor != allContours.end(); itor++)
	{
		if((*itor) == oneContour)
		{
			allContours.erase(itor);
			return;
		}
	}
}


/**
 * \brief	trying to use the color for drawing contours to recover the error areas from the result image,
 *			but this way is not work as the color is not excatly the value we used for drawing 
 *			and the number text in the image indicating areas will be confusing
 * \param autoResImg 
 * \param contoursExtra 
 * \param contoursMiss 
 */
void getErrorContoursFromImg(const cv::Mat autoResImg, std::vector<std::vector<cv::Point> >& contoursExtra, std::vector<std::vector<cv::Point> >& contoursMiss)
{
	cv::Mat extraContourMaskImg;
	cv::inRange(autoResImg, EXTRA_COATING_ERROR_COLOR, EXTRA_COATING_ERROR_COLOR, extraContourMaskImg);

	if(!contoursExtra.empty())
	{
		contoursExtra.clear();
	}
	std::vector<cv::Vec4i> hierarchyExtra;
	cv::findContours(extraContourMaskImg, contoursExtra, hierarchyExtra, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);


	cv::Mat missContourMaskImg;
	cv::inRange(autoResImg, MISS_COATING_ERROR_COLOR, MISS_COATING_ERROR_COLOR, missContourMaskImg);

	if (!contoursMiss.empty())
	{
		contoursMiss.clear();
	}
	std::vector<cv::Vec4i> hierarchyMiss;
	cv::findContours(extraContourMaskImg, contoursMiss, hierarchyMiss, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
}

std::vector<std::vector<cv::Point> > getIMG(std::vector<std::vector<cv::Point>>& img)
{
	return img;
}

