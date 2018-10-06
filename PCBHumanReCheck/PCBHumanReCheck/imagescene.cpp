#include "imagescene.h"
#include <QGraphicsView>

ImageScene::ImageScene(QObject* parent)
: QGraphicsScene(parent)
{
}

ImageScene::~ImageScene()
{
}

void ImageScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsScene::mousePressEvent(event);
}

void ImageScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsScene::mouseDoubleClickEvent(event);
}
