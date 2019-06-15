#include "abview.h"

abView::abView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	lineWidth = 5;

	connect(ui.picViewA, SIGNAL(resChanged(int)), this, SLOT(updateOnePCBResH(int)));
	connect(ui.picViewB, SIGNAL(resChanged(int)), this, SLOT(updateOnePCBResH(int)));
}

abView::~abView()
{
}

void abView::loadOnePCBResInfo(onePCBResInfo& onePCBInfo, int lineWidth)
{
	this->lineWidth = lineWidth;

	ui.picViewA->picViewInit(onePCBInfo, lineWidth, 0);
	ui.picViewA->setImgInform();
	ui.picViewA->loadPolygonItem();

	ui.picViewB->picViewInit(onePCBInfo, lineWidth, 1);
	ui.picViewB->setImgInform();
	ui.picViewB->loadPolygonItem();

	curOnePCBResManu.clearInfo();
	curOnePCBResManu = onePCBInfo;
}

void abView::refreshOnePCBResInfo(onePCBResInfo& onePCBInfoManu)
{
	loadOnePCBResInfo(onePCBInfoManu, lineWidth);
}

bool abView::isResModified()
{
	return curOnePCBResManu.isModified;
}

onePCBResInfo abView::getReCheckRes()
{
	return curOnePCBResManu;
}

void abView::getReCheckRes(onePCBResInfo& dstOnePCBResInfoManu)
{
	dstOnePCBResInfoManu = curOnePCBResManu;
}

void abView::refreshPolyItemsDrawWidth(int widthErr)
{
	lineWidth = widthErr;
	ui.picViewA->refreshPolyItemsDrawWidth(lineWidth);
	ui.picViewB->refreshPolyItemsDrawWidth(lineWidth);
}

void abView::setErrConLineWidth(int widthErr)
{
	lineWidth = widthErr;
}

void abView::updateOnePCBResH(int index)
{
	if(index == 0)
	{
		ui.picViewA->recheckResImg();
		curOnePCBResManu.resetOneSideRes(0, ui.picViewA->getReCheckRes());
	}
	else if(index == 1)
	{
		ui.picViewB->recheckResImg();
		curOnePCBResManu.resetOneSideRes(1, ui.picViewB->getReCheckRes());
	}
	curOnePCBResManu.isModified = true;
}

void abView::recheckResImg()
{
	ui.picViewA->recheckResImg();
	ui.picViewB->recheckResImg();
}




