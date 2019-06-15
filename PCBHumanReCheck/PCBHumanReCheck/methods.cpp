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

bool isSameDVecPt(std::vector<std::vector<cv::Point>> Pts1, std::vector<std::vector<cv::Point>> Pts2)
{
	if(Pts1.size() == Pts2.size())
	{
		for(int i = 0 ; i < Pts1.size(); i++)
		{
			if(Pts1[i].size() == Pts2[i].size())
			{
				for(int j = 0; j < Pts1[i].size(); j++)
				{
					if (Pts1[i][j].x != Pts2[i][j].x || Pts1[i][j].y != Pts2[i][j].y)
						return false;
				}
			}
			else
			{
				return false;
			}
		}
	}
	else
	{
		return false;
	}
	return true;
}

void _split(const std::string& s, char delim, std::vector<std::string>& elems)
{
	std::stringstream ss(s);
	std::string item;

	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
}

std::vector<std::string> split(const std::string& s, char delim)
{
	std::vector<std::string> elems;
	_split(s, delim, elems);
	return elems;
}

std::string changePathDirt(std::string folderPath)
{
	std::vector<std::string> names = split(folderPath, '/');
	if(names.empty())
	{
		return folderPath;
	}
	std::string chanedPath = names[0];
	for(std::vector<std::string>::iterator itor = names.begin() + 1; itor != names.end(); itor++)
	{
		chanedPath += '\\' + *itor;
	}
	return chanedPath;
}

QString changePathDirt(QString folderPath)
{
	QStringList list_ = folderPath.split('/');
	QString changedPath;
	for(int i = 0; i < list_.size(); i++)
	{
		if(i == 0)
		{
			changedPath = list_.at(0);
		}
		else
		{
			changedPath += '\\' + list_.at(i);
		}
	}
	return changedPath;
}

void eraseOneContour(std::vector<std::vector<cv::Point> >& allContours, std::vector<cv::Point> oneContour)
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

