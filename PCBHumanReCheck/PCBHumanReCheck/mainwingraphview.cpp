#include "mainwingraphview.h"
#include <QWheelEvent>
#include <QMouseEvent>


MainWinGraphView::MainWinGraphView(QWidget *parent)
	: QGraphicsView(parent)
{
	this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	this->setResizeAnchor(QGraphicsView::AnchorUnderMouse);
}

MainWinGraphView::~MainWinGraphView()
{
}

void MainWinGraphView::zoom(int value)
{
	zoomLevel = value;

	ZoomScale = pow(qreal(2), qreal(value - 600) / 200.0);

	matrix.reset();
	matrix.scale(ZoomScale, ZoomScale);
	this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	this->setResizeAnchor(QGraphicsView::AnchorUnderMouse);
	this->setMatrix(matrix);
}

void MainWinGraphView::zoom(int value, QPointF pos)
{
	zoomLevel = value;

	ZoomScale = pow(qreal(2), qreal(value - 600) / 200.0);

	matrix.reset();
	matrix.scale(ZoomScale, ZoomScale);
	this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	this->setResizeAnchor(QGraphicsView::AnchorUnderMouse);
	this->setMatrix(matrix);
}

void MainWinGraphView::setZoomLevel(int value)
{
	zoomLevel = value;
}

void MainWinGraphView::wheelEvent(QWheelEvent* event)
{
	int x = event->x();
	int y = event->y();
	QPointF pos = this->mapToScene(x, y);
	if (event->delta() > 0)
	{
		if (zoomLevel < 800)
		{
			zoomLevel += 2;
			zoom(zoomLevel, pos);
		}
	}
	else
	{
		if (zoomLevel > 2)
		{
			zoomLevel -= 2;
			zoom(zoomLevel, pos);
		}
	}
	emit newZoomValue(zoomLevel);
}

void MainWinGraphView::mousePressEvent(QMouseEvent* event)
{
	originX = event->x();
	originY = event->y();
	QGraphicsView::mousePressEvent(event);
}

void MainWinGraphView::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::LeftButton) {
		int x = event->x();
		int y = event->y();
		int dx = originX - x;
		int dy = originY - y;
		matrix.translate(dx, dy);
		this->setMatrix(matrix);
	}
	QGraphicsView::mouseMoveEvent(event);
}

void MainWinGraphView::mouseDoubleClickEvent(QMouseEvent* event)
{
	zoomLevel = std::min(800, zoomLevel + 10);

	QPointF pos = event->pos();
	zoom(zoomLevel, pos);
	emit newZoomValue(zoomLevel);
}

