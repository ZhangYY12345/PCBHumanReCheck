#pragma once
#include <QGraphicsScene>  

class ImageScene :
	public QGraphicsScene
{
public:
	ImageScene(QObject* parent = nullptr);
	~ImageScene();

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
};

