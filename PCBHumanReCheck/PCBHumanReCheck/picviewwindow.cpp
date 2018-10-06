#include "picviewwindow.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include "methods.h"

PicViewWindow::PicViewWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	graphicsScene = new QGraphicsScene();
	pixmapItem = new QGraphicsPixmapItem();
	graphicsScene->addItem(pixmapItem);

	connect(ui.graphicsView, SIGNAL(newZoomValue(int)), this, SLOT(setZoomLevel(int)));
	connect(ui.zoomControl, SIGNAL(valueChanged(int)), this, SLOT(zoomView(int)));
}

PicViewWindow::~PicViewWindow()
{
}

void PicViewWindow::setImgInform(QString imgInfo, cv::Mat img)
{
	ui.imgInform->setText(imgInfo);

	if (img.empty()) {
		pixmapItem->setPixmap(QPixmap());
		return;
	}
	pixmapItem->setPixmap(QPixmap::fromImage(cvMat2QImage(img)));
	graphicsScene->setSceneRect(0, 0, img.cols, img.rows);
}

void PicViewWindow::setZoomLevel(int value)
{
	disconnect(ui.zoomControl, SIGNAL(valueChanged(int)), this, SLOT(zoomView(int)));
	ui.zoomControl->setValue(value);
	connect(ui.zoomControl, SIGNAL(valueChanged(int)), this, SLOT(zoomView(int)));
}

void PicViewWindow::zoomView(int value)
{
	zoomLevel = value;

	ZoomScale = pow(qreal(2), qreal(value - 600) / 200.0);
	matrix.reset();
	matrix.scale(ZoomScale, ZoomScale);
	ui.graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	ui.graphicsView->setResizeAnchor(QGraphicsView::AnchorUnderMouse);
	ui.graphicsView->setMatrix(matrix);

	ui.graphicsView->setZoomLevel(zoomLevel);
}
