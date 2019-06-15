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

	void picViewInit(onePCBResInfo curOnePCBRes, int width, int indicAB);
	void refreshPolyItemsDrawWidth(int widthErr);

	void setErrConLineWidth(int widthErr);

	void setImgInform();
	void setImgInform(QString imgInfo, cv::Mat img);
	void loadPolygonItem();
	void loadPolygonItem(onePCBResInfo& onePCBInfo);

	onePCBResInfo getReCheckRes();
	void getReCheckRes(onePCBResInfo& dstOnePCBResInfoManu);
	void recheckResImg();

	signals:
	void resChanged(int);

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


};
