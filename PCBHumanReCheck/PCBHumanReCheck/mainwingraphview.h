#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QTimer>
#include "parameters.h"

class AreaPolygonItem : public QObject, public QGraphicsPolygonItem
{
	Q_OBJECT

public:
	explicit AreaPolygonItem(QGraphicsItem *parent = Q_NULLPTR);
	explicit AreaPolygonItem(AreaPolygonItem &src);
	explicit AreaPolygonItem(const QPolygonF &polygonPts, QGraphicsItem *parent = Q_NULLPTR);
	explicit AreaPolygonItem(const std::vector<cv::Point> &polygonPts, QGraphicsItem *parent = Q_NULLPTR);
	explicit AreaPolygonItem(const QPolygonF &polygonPts, const ERR_CONTOUR_NAME typeName, int lineWidth, QGraphicsItem *parent = Q_NULLPTR);
	explicit AreaPolygonItem(const std::vector<cv::Point> &polygonPts, const ERR_CONTOUR_NAME typeName, int lineWidth, QGraphicsItem *parent = Q_NULLPTR);
	~AreaPolygonItem();

	void reset();
	void refresh(AreaPolygonItem &src);

	void setAreaName(ERR_CONTOUR_NAME name);
	ERR_CONTOUR_NAME getAreaName();

	void setPolyPenStyle(int lineWidth);

	QPointF getMouseEventScenePt();
	QPoint getMouseEventScreenPt();

	void rightMenu();

signals:
	void deleteItem(QPointF);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

private:
	ERR_CONTOUR_NAME errName; // lable to indicate which set the item belong to;
	
	QPointF mouseEventScenePt;
	QPoint mouseEventScreenPt;
};


class MainWinGraphView : public QGraphicsView
{
	Q_OBJECT

public:
	MainWinGraphView(QWidget *parent = Q_NULLPTR);
	~MainWinGraphView();
	void zoom(int value);
	void zoom(int value, QPointF pos);
	void setZoomLevel(int value);

	void addItem(AreaPolygonItem* item);
	void removeItem(AreaPolygonItem* item);
	void clearAllPolyItems();
	void clearAllItem();

	QList<QGraphicsItem*> getAllPolyItems();
	QList<QGraphicsItem*> getOneErrTypePolyItems(ERR_CONTOUR_NAME errType);
	QGraphicsItem* getOneErrTypePolyItems(QPointF pt);
	QGraphicsItem* getPolygonItemWithPts(QVector<QPointF> pts);

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
