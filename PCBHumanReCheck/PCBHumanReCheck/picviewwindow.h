#pragma once

#include <QWidget>
#include "ui_picviewwindow.h"
#include <opencv2/opencv.hpp>

class PicViewWindow : public QWidget
{
	Q_OBJECT

public:
	PicViewWindow(QWidget *parent = Q_NULLPTR);
	~PicViewWindow();

	void setImgInform(QString imgInfo, cv::Mat img);

	private slots:
	void setZoomLevel(int value);
	void zoomView(int value);

private:
	Ui::PicViewWindow ui;
	QGraphicsScene *graphicsScene = Q_NULLPTR;
	QGraphicsPixmapItem *pixmapItem = Q_NULLPTR;

	qreal ZoomScale = 1.0;
	int zoomLevel;
	QMatrix matrix;
};
