#include "mainwingraphview.h"
#include <QMouseEvent>
#include <QMenu>
#include <QDebug>
#include <qgraphicssceneevent.h>
#include "methods.h"

//---------------------------------------------------
//------------------AreaPolygonItem------------------
//---------------------------------------------------

AreaPolygonItem::AreaPolygonItem(QGraphicsItem* parent)
{
	setFlag(QGraphicsPolygonItem::ItemIsSelectable);
	setSelected(false);

	setZValue(1);

	errName = NULL_ERR;
}

AreaPolygonItem::AreaPolygonItem(AreaPolygonItem& src)
{
	setFlags(src.flags());
	setSelected(src.isSelected());

	setZValue(1);

	setPolygon(src.polygon());
	setPen(src.pen());
	errName = src.errName;

	mouseEventScreenPt = src.mouseEventScreenPt;
	mouseEventScenePt = src.mouseEventScenePt;
}

AreaPolygonItem::AreaPolygonItem(const QPolygonF& polygonPts, QGraphicsItem* parent)
{
	setFlag(QGraphicsPolygonItem::ItemIsSelectable);
	setSelected(false);

	setZValue(1);

	setPolygon(polygonPts);
	errName = NULL_ERR;
}

AreaPolygonItem::AreaPolygonItem(const std::vector<cv::Point>& polygonPts, QGraphicsItem* parent)
{
	setFlag(QGraphicsPolygonItem::ItemIsSelectable);
	setSelected(false);

	setZValue(1);

	setPolygon(StdVectorcvPoint2QVectorQPointF(polygonPts));
	errName = NULL_ERR;
}

AreaPolygonItem::AreaPolygonItem(const QPolygonF& polygonPts, const ERR_CONTOUR_NAME typeName, int lineWidth,
	QGraphicsItem* parent)
{
	setFlag(QGraphicsPolygonItem::ItemIsSelectable);
	setSelected(false);

	setZValue(1);

	setPolygon(polygonPts);
	errName = typeName;
	setPolyPenStyle(lineWidth);
}

AreaPolygonItem::AreaPolygonItem(const std::vector<cv::Point>& polygonPts, const ERR_CONTOUR_NAME typeName,
	int lineWidth, QGraphicsItem* parent)
{
	setFlag(QGraphicsPolygonItem::ItemIsSelectable);
	setSelected(false);

	setZValue(1);

	setPolygon(StdVectorcvPoint2QVectorQPointF(polygonPts));
	errName = typeName;
	setPolyPenStyle(lineWidth);
}

AreaPolygonItem::~AreaPolygonItem()
{
	destroyed(this);
}

void AreaPolygonItem::reset()
{
	QPolygonF emptyPts;
	setPolygon(emptyPts);
	errName = NULL_ERR;

	mouseEventScreenPt = QPoint(0, 0);
	mouseEventScenePt = QPointF(0, 0);

}

void AreaPolygonItem::refresh(AreaPolygonItem& src)
{
	setPolygon(src.polygon());
	setPen(src.pen());
	errName = src.errName;
}

void AreaPolygonItem::setAreaName(ERR_CONTOUR_NAME name)
{
	errName = name;
}

ERR_CONTOUR_NAME AreaPolygonItem::getAreaName()
{
	return errName;
}

void AreaPolygonItem::setPolyPenStyle(int lineWidth)
{
	QPen pen;
	pen.setWidth(lineWidth);

	switch (errName)
	{
	case EXTRA_ERR:
		pen.setColor(EXTRA_COATING_ERROR_QCOLOR);
		break;
	case MISS_ERR:
		pen.setColor(MISS_COATING_ERROR_QCOLOR);
		break;
	}
	setPen(pen);
}

QPointF AreaPolygonItem::getMouseEventScenePt()
{
	return mouseEventScenePt;
}

QPoint AreaPolygonItem::getMouseEventScreenPt()
{
	return mouseEventScreenPt;
}

void AreaPolygonItem::rightMenu()
{
	QMenu menu;
	QAction *deleteAction = menu.addAction("Delete");
	QAction *selectedAction = menu.exec(mouseEventScreenPt);

	if (selectedAction == deleteAction)
	{
		emit deleteItem(mouseEventScenePt);
	}
	setSelected(false);
}

void AreaPolygonItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	qDebug() << isSelected() << endl;
	mouseEventScenePt = event->scenePos();
	mouseEventScreenPt = event->screenPos();

	if (event->button() == Qt::RightButton)
	{
		if (isSelected())
			rightMenu();
	}

}

void AreaPolygonItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
	qDebug() << "mouse double click event" << endl << endl;
	mouseEventScenePt = event->scenePos();
	mouseEventScreenPt = event->screenPos();

	setFlag(QGraphicsPolygonItem::ItemIsSelectable, true);
	if (event->button() == Qt::LeftButton)
	{
		setSelected(true);

		QPen newPen = pen();
		newPen.setStyle(Qt::DashDotDotLine);
		setPen(newPen);
	}
}

//---------------------------------------------------
//-----------------MainWinGraphView------------------
//---------------------------------------------------
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

void MainWinGraphView::addItem(AreaPolygonItem* item)
{
	this->scene()->addItem(item);
}

void MainWinGraphView::removeItem(AreaPolygonItem* item)
{
	this->scene()->removeItem(item);
}

void MainWinGraphView::clearAllPolyItems()
{
	QList<QGraphicsItem*> toDeletePolyItems = getAllPolyItems();
	for (QList<QGraphicsItem*>::iterator iter = toDeletePolyItems.begin(); iter != toDeletePolyItems.end(); iter++)
	{
		removeItem((AreaPolygonItem*)(*iter));
	}
}

void MainWinGraphView::clearAllItem()
{
	this->scene()->clear();
}

QList<QGraphicsItem*> MainWinGraphView::getAllPolyItems()
{
	QList<QGraphicsItem*> polyItemList = this->scene()->items();
	if (!polyItemList.isEmpty())
	{
		polyItemList.removeLast();
	}
	return polyItemList;
}

QList<QGraphicsItem*> MainWinGraphView::getOneErrTypePolyItems(ERR_CONTOUR_NAME errType)
{
	QList<QGraphicsItem*> areaNamePolyItems;
	QList<QGraphicsItem* > allPolyItems = getAllPolyItems();
	for (int i = 0; i < allPolyItems.size(); i++)
	{
		if (((AreaPolygonItem*)allPolyItems[i])->getAreaName() == errType)
			areaNamePolyItems.push_back(allPolyItems[i]);
	}
	return areaNamePolyItems;
}

QGraphicsItem* MainWinGraphView::getOneErrTypePolyItems(QPointF pt)
{
	QList<QGraphicsItem* > allItems = this->scene()->items(pt);
	if(allItems[0]->zValue() != 0)
	{
		return allItems[0];
	}

	return Q_NULLPTR;
}

QGraphicsItem* MainWinGraphView::getPolygonItemWithPts(QVector<QPointF> pts)
{
	QList<QGraphicsItem*> itemList = this->scene()->items(pts);
	if(itemList.size() != 0 && itemList[0]->zValue() == 1)
	{
		return itemList[0];
	}
	return Q_NULLPTR;
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

