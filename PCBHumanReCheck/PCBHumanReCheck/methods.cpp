#include "methods.h"

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
