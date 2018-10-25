#pragma once

#include <QWidget>
#include "ui_picviewwindow.h"
#include <opencv2/opencv.hpp>
#include "mainwingraphview.h"

class PicViewWindow : public QWidget
{
	Q_OBJECT

public:
	PicViewWindow(QWidget *parent = Q_NULLPTR);
	~PicViewWindow();


	void loadOnePCBResInfo(onePCBResInfo& onePCBInfo, int lineWidth, int sideInfo);
	void refreshOnePCBResInfo(onePCBResInfo& onePCBInfoManu);

	bool isResModified();
	onePCBResInfo getReCheckRes();
	void getReCheckRes(onePCBResInfo& dstOnePCBResInfoManu);

	void refreshPolyItemsDrawWidth(int widthErr);

	void setErrConLineWidth(int widthErr);

	private slots:
	void deletePolyItem(QPointF);

	void setZoomLevel(int value);
	void zoomView(int value);

private:
	Ui::PicViewWindow ui;
	QGraphicsScene *graphicsScene = Q_NULLPTR;
	QGraphicsPixmapItem *pixmapItem = Q_NULLPTR;

	int sideIndi;								//0:front side	1:back side

	int lineWidth;

	onePCBResInfo curOnePCBResManu;

	qreal ZoomScale = 1.0;
	int zoomLevel;
	QMatrix matrix;


	void setImgInform(QString imgInfo, cv::Mat img);
	void loadPolygonItem(onePCBResInfo& onePCBInfo);

	void recheckResImg();
};
