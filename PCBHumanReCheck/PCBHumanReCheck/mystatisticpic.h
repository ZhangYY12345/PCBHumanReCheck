#pragma once

#include<QtCharts>
QT_CHARTS_USE_NAMESPACE

#include <QWidget>
#include "ui_mystatisticpic.h"
#include <QSqlDatabase>

class myStatisticPic : public QWidget
{
	Q_OBJECT

public:
	myStatisticPic(QSqlDatabase& db, QWidget *parent = Q_NULLPTR);
	~myStatisticPic();

	void drawPieToday();
	void drawPieWhole();
	void drawLineChart();

	void winClose();

private:
	Ui::myStatisticPic ui;
	QSqlDatabase dbToStatistic;

	void getAllDateDB(QStringList& dates);

	int getDayOnlyExErrNum(QString date);
	int getDayOnlyMiErNum(QString date);
	int getDayBothErrNum(QString date);
	int getDayQualityNum(QString date);

	int getWholeOnlyExErrNum();
	int getWholeOnlyMiErNum();
	int getWholeBothErrNum();
	int getWholeQualityNum();

};
