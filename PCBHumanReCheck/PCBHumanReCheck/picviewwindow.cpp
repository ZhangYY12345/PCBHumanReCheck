#include "picviewwindow.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include "methods.h"

PicViewWindow::PicViewWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	pixmapItem = new QGraphicsPixmapItem(QPixmap(0, 0));
	graphicsScene = new QGraphicsScene();
	graphicsScene->addItem(pixmapItem);
	ui.graphicsView->setScene(graphicsScene);

	zoomLevel = ui.zoomControl->value();
	ui.graphicsView->setZoomLevel(zoomLevel);

	connect(ui.graphicsView, SIGNAL(newZoomValue(int)), this, SLOT(setZoomLevel(int)));
	connect(ui.zoomControl, SIGNAL(valueChanged(int)), this, SLOT(zoomView(int)));

	lineWidth = 5;
	sideIndi = 3;  //either the front side or the back side
}

PicViewWindow::~PicViewWindow()
{
}

void PicViewWindow::picViewInit(onePCBResInfo curOnePCBRes, int width, int indicAB)
{
	curOnePCBResManu = curOnePCBRes;
	lineWidth = width;
	sideIndi = indicAB;

	ui.graphicsView->clearAllPolyItems();
}

/**
 * \brief when the recheck of the current PCB is done, store all the 
 * \return 
 */
onePCBResInfo PicViewWindow::getReCheckRes()
{
	return curOnePCBResManu;
}

void PicViewWindow::getReCheckRes(onePCBResInfo& dstOnePCBResInfoManu)
{
	dstOnePCBResInfoManu = curOnePCBResManu;
}

void PicViewWindow::refreshPolyItemsDrawWidth(int widthErr)
{
	lineWidth = widthErr;
	QList<QGraphicsItem*> allContourItems = ui.graphicsView->getAllPolyItems();
	for(auto itor = allContourItems.begin(); itor != allContourItems.end(); itor++)
	{		
		QPen newPen = (*(AreaPolygonItem*)(*itor)).pen();
		newPen.setWidth(widthErr);
		(*(AreaPolygonItem*)(*itor)).setPen(newPen);
	}
}

void PicViewWindow::setErrConLineWidth(int widthErr)
{
	lineWidth = widthErr;
}

void PicViewWindow::setImgInform()
{
	if(sideIndi == 0)		//front side
	{
		ui.imgInform->setText("ImgRes FrontSide");

		if (curOnePCBResManu.imgResFSide.empty()) {
			pixmapItem->setPixmap(QPixmap());
			return;
		}

		QImage image(curOnePCBResManu.imgResFSide.data, 
			curOnePCBResManu.imgResFSide.cols, curOnePCBResManu.imgResFSide.rows, 
			curOnePCBResManu.imgResFSide.step, QImage::Format_RGB888);
		pixmapItem->setPixmap(QPixmap::fromImage(image.rgbSwapped()));
		graphicsScene->setSceneRect(0, 0, curOnePCBResManu.imgResFSide.cols, curOnePCBResManu.imgResFSide.rows);

	}
	else if(sideIndi == 1)	//back side
	{
		ui.imgInform->setText("ImgRes BackSide");

		if (curOnePCBResManu.imgResBSide.empty()) {
			pixmapItem->setPixmap(QPixmap());
			return;
		}

		QImage image(curOnePCBResManu.imgResBSide.data,
			curOnePCBResManu.imgResBSide.cols, curOnePCBResManu.imgResBSide.rows,
			curOnePCBResManu.imgResBSide.step, QImage::Format_RGB888);
		pixmapItem->setPixmap(QPixmap::fromImage(image.rgbSwapped()));
		graphicsScene->setSceneRect(0, 0, curOnePCBResManu.imgResBSide.cols, curOnePCBResManu.imgResBSide.rows);

	}
}

void PicViewWindow::setImgInform(QString imgInfo, cv::Mat img)
{
	ui.imgInform->setText(imgInfo);

	if (img.empty()) {
		pixmapItem->setPixmap(QPixmap());
		return;
	}
	QImage image(img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);

	pixmapItem->setPixmap(QPixmap::fromImage(image));
	graphicsScene->setSceneRect(0, 0, img.cols, img.rows);
}

void PicViewWindow::loadPolygonItem()
{
	loadPolygonItem(curOnePCBResManu);
}

void PicViewWindow::loadPolygonItem(onePCBResInfo& onePCBInfo)
{
	if (sideIndi == 0)
	{
		for (auto itor = onePCBInfo.contourExtraF.begin(); itor != onePCBInfo.contourExtraF.end(); itor++)
		{
			AreaPolygonItem* newErrContour = new AreaPolygonItem(*itor);
			newErrContour->setAreaName(EXTRA_ERR);
			newErrContour->setPolyPenStyle(lineWidth);

			ui.graphicsView->addItem(newErrContour);
			connect(newErrContour, SIGNAL(deleteItem(QPointF)), this, SLOT(deletePolyItem(QPointF)));
		}

		for (auto itor = onePCBInfo.contourMissF.begin(); itor != onePCBInfo.contourMissF.end(); itor++)
		{
			AreaPolygonItem* newErrContour = new AreaPolygonItem(*itor);
			newErrContour->setAreaName(MISS_ERR);
			newErrContour->setPolyPenStyle(lineWidth);

			ui.graphicsView->addItem(newErrContour);
			connect(newErrContour, SIGNAL(deleteItem(QPointF)), this, SLOT(deletePolyItem(QPointF)));
		}
	}
	else if (sideIndi == 1)
	{
		for (auto itor = onePCBInfo.contourExtraB.begin(); itor != onePCBInfo.contourExtraB.end(); itor++)
		{
			AreaPolygonItem* newErrContour = new AreaPolygonItem(*itor);
			newErrContour->setAreaName(EXTRA_ERR);
			newErrContour->setPolyPenStyle(lineWidth);

			ui.graphicsView->addItem(newErrContour);
			connect(newErrContour, SIGNAL(deleteItem(QPointF)), this, SLOT(deletePolyItem(QPointF)));
		}

		for (auto itor = onePCBInfo.contourMissB.begin(); itor != onePCBInfo.contourMissB.end(); itor++)
		{
			AreaPolygonItem* newErrContour = new AreaPolygonItem(*itor);
			newErrContour->setAreaName(MISS_ERR);
			newErrContour->setPolyPenStyle(lineWidth);

			ui.graphicsView->addItem(newErrContour);
			connect(newErrContour, SIGNAL(deleteItem(QPointF)), this, SLOT(deletePolyItem(QPointF)));
		}
	}
}

void PicViewWindow::deletePolyItem(QPointF pt)
{
	AreaPolygonItem * itemToRemove = (AreaPolygonItem*)(ui.graphicsView->getOneErrTypePolyItems(pt));

	if (itemToRemove != Q_NULLPTR)
	{
		QPolygonF polyPts = itemToRemove->polygon();
		std::vector<cv::Point> stdVecPoints = QVectorQPointF2StdVectorcvPoint(polyPts);
		curOnePCBResManu.erase(sideIndi, itemToRemove->getAreaName(), stdVecPoints);

		ui.graphicsView->removeItem(itemToRemove);

		emit resChanged(sideIndi);
	}
}

void PicViewWindow::setZoomLevel(int value)
{
	disconnect(ui.zoomControl, SIGNAL(valueChanged(int)), this, SLOT(zoomView(int)));
	ui.zoomControl->setValue(value);
	connect(ui.zoomControl, SIGNAL(valueChanged(int)), this, SLOT(zoomView(int)));
}

void PicViewWindow::zoomView(int value)
{
	if(value <= 0)
	{
		value = 1;
	}

	zoomLevel = value;

	ZoomScale = pow(qreal(2), qreal(value - 600) / 200.0);
	matrix.reset();
	matrix.scale(ZoomScale, ZoomScale);
	ui.graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	ui.graphicsView->setResizeAnchor(QGraphicsView::AnchorUnderMouse);
	ui.graphicsView->setMatrix(matrix);

	ui.graphicsView->setZoomLevel(zoomLevel);
}


void PicViewWindow::recheckResImg()
{
	if (sideIndi == 0)				//front side
	{
		cv::drawContours(curOnePCBResManu.imgResFSide, curOnePCBResManu.contourExtraF, -1, EXTRA_COATING_ERROR_COLOR, 1, cv::LINE_4);
		cv::drawContours(curOnePCBResManu.imgResFSide, curOnePCBResManu.contourMissF, -1, MISS_COATING_ERROR_COLOR, 1, cv::LINE_4);
	}
	else if (sideIndi == 1)			//back side
	{
		cv::drawContours(curOnePCBResManu.imgResBSide, curOnePCBResManu.contourExtraB, -1, EXTRA_COATING_ERROR_COLOR, 1, cv::LINE_4);
		cv::drawContours(curOnePCBResManu.imgResBSide, curOnePCBResManu.contourMissB, -1, MISS_COATING_ERROR_COLOR, 1, cv::LINE_4);
	}
}
