#pragma once

#include <QGraphicsView>

class MainWinGraphView : public QGraphicsView
{
	Q_OBJECT

public:
	MainWinGraphView(QWidget *parent = Q_NULLPTR);
	~MainWinGraphView();
	void zoom(int value);
	void zoom(int value, QPointF pos);
	void setZoomLevel(int value);

	signals:
	void newZoomValue(int zoomLevel);

protected:
	void wheelEvent(QWheelEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseDoubleClickEvent(QMouseEvent* event) override;

private:
	QMatrix matrix;
	int originX;
	int originY;
	int zoomLevel;
	qreal ZoomScale = 1.0;
};
