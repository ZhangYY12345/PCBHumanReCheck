#pragma once

#include <QWidget>
#include "ui_abview.h"

class abView : public QWidget
{
	Q_OBJECT

public:
	abView(QWidget *parent = Q_NULLPTR);
	~abView();

	void loadOnePCBResInfo(onePCBResInfo& onePCBInfo, int lineWidth);
	void refreshOnePCBResInfo(onePCBResInfo& onePCBInfoManu);

	bool isResModified();
	onePCBResInfo getReCheckRes();
	void getReCheckRes(onePCBResInfo& dstOnePCBResInfoManu);

	void refreshPolyItemsDrawWidth(int widthErr);

	void setErrConLineWidth(int widthErr);

	signals:
		void reschanged();

private slots:
	void updateOnePCBResH(int index);
private:
	Ui::abView ui;

	int lineWidth;
	onePCBResInfo curOnePCBResManu;

	void recheckResImg();
};
