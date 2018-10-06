#include "mystatisticpic.h"
#include "donutbreakdownchart.h"
#include <QSqlQuery>
#include <QDateTime>
#include <QLineSeries>
#include <QBarCategoryAxis>
#include <QValueAxis>

QT_CHARTS_USE_NAMESPACE

myStatisticPic::myStatisticPic(QSqlDatabase& db, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->dbToStatistic = db;

	drawPieToday();
	drawPieWhole();
	drawLineChart();
}

myStatisticPic::~myStatisticPic()
{
}

void myStatisticPic::drawPieToday()
{
	QDate qDate = QDate::currentDate();
	QString currentDate = qDate.toString("yyyy-MM-dd");

	QPieSeries *seriesError = new QPieSeries();
	seriesError->setName("Coating Error PCBs");
	seriesError->append("MissCoating", getDayOnlyMiErNum(currentDate));
	seriesError->append("Extra Coating", getDayOnlyExErrNum(currentDate));
	seriesError->append("Both missing and extra Coating", getDayBothErrNum(currentDate));

	QPieSeries *seriesQualify = new QPieSeries();
	seriesQualify->setName("Qualified PCBs");
	seriesQualify->append("Qualified", getDayQualityNum(currentDate));

	DonutBreakdownChart *donutBreakdown = new DonutBreakdownChart();
	donutBreakdown->setAnimationOptions(QChart::AllAnimations);
	donutBreakdown->setTitle(tr("Quality of PCB coating on %1.%2.%3").arg(qDate.year()).arg(qDate.month()).arg(qDate.day()));
	donutBreakdown->legend()->setAlignment(Qt::AlignRight);
	donutBreakdown->addBreakdownSeries(seriesError, Qt::red);
	donutBreakdown->addBreakdownSeries(seriesQualify, Qt::darkGreen);

	ui.pieToday->setChart(donutBreakdown);
	ui.pieToday->setRenderHint(QPainter::Antialiasing);
}

void myStatisticPic::drawPieWhole()
{
	QPieSeries *seriesError = new QPieSeries();
	seriesError->setName("Coating Error PCBs");
	seriesError->append("MissCoating", getWholeOnlyMiErNum());
	seriesError->append("Extra Coating", getWholeOnlyExErrNum());
	seriesError->append("Both missing and extra Coating", getWholeBothErrNum());

	QPieSeries *seriesQualify = new QPieSeries();
	seriesQualify->setName("Qualified PCBs");
	seriesQualify->append("Qualified", getWholeQualityNum());

	DonutBreakdownChart *donutBreakdown = new DonutBreakdownChart();
	donutBreakdown->setAnimationOptions(QChart::AllAnimations);
	donutBreakdown->setTitle("Quality of PCB coating in the view of the whole");
	donutBreakdown->legend()->setAlignment(Qt::AlignRight);
	donutBreakdown->addBreakdownSeries(seriesError, Qt::red);
	donutBreakdown->addBreakdownSeries(seriesQualify, Qt::darkGreen);

	ui.pieWhole->setChart(donutBreakdown);
	ui.pieWhole->setRenderHint(QPainter::Antialiasing);

}

void myStatisticPic::drawLineChart()
{
	QLineSeries *series = new QLineSeries();

	QStringList dates;
	getAllDateDB(dates);

	for (int i = 0; i < dates.size(); i++)
	{
		series->append(i, getDayQualityNum(dates[i]));
	}

	QChart* chart = new QChart();
	chart->legend()->hide();

	chart->addSeries(series);
	//chart->createDefaultAxes();
	chart->setTitle("Trend of quality of PCB coating");

	QBarCategoryAxis *axisX = new QBarCategoryAxis();
	axisX->append(dates);
	chart->setAxisX(axisX, series);
	if (dates.size() <= 10)
	{
		axisX->setRange(*dates.begin(), *(dates.end() - 1));
	}
	else
	{
		axisX->setRange(*(dates.end() - 10), *(dates.end() - 1));
	}

	QValueAxis *axisY = new QValueAxis();
	chart->setAxisY(axisY, series);

	ui.lineChart->setChart(chart);
	ui.lineChart->setRenderHint(QPainter::Antialiasing);
}

void myStatisticPic::winClose()
{
	dbToStatistic.close();
	QString name;
	{
		name = QSqlDatabase::database().connectionName();
	}
	QSqlDatabase::removeDatabase(name);

}

void myStatisticPic::getAllDateDB(QStringList& dates)
{
	QSqlQuery query(dbToStatistic);
	query.exec("create table checkRes (PCBID varchar(30) primary key, "
		"CarrierID varchar(30), REGIONID varchar(10), Date varchar(20), Time varchar(20), Result varchar(30), resImgPath varchar(100))");

	query.exec("select distinct Date from checkRes order by Date");
	while (query.next())
	{
		dates.push_back(query.value(QString("Date")).toString());
	}
}

int myStatisticPic::getDayOnlyExErrNum(QString date)
{
	QSqlQuery query(dbToStatistic);
	query.exec("create table checkRes (PCBID varchar(30) primary key, "
		"CarrierID varchar(30), REGIONID varchar(10), Date varchar(20), Time varchar(20), Result varchar(30), resImgPath varchar(100))");

	query.exec(tr("select * from checkRes where Date = '%1' and Result = 'Extra Coating Error'").arg(date));
	int b = 0;
	while (query.next())
	{
		b++;
	}
	return b;
}

int myStatisticPic::getDayOnlyMiErNum(QString date)
{
	QSqlQuery query(dbToStatistic);
	query.exec("create table checkRes (PCBID varchar(30) primary key, "
		"CarrierID varchar(30), REGIONID varchar(10), Date varchar(20), Time varchar(20), Result varchar(30), resImgPath varchar(100))");

	query.exec(tr("select * from checkRes where Date = '%1' and Result = 'Missing Coating Error'").arg(date));
	int b = 0;
	while (query.next())
	{
		b++;
	}
	return b;
}

int myStatisticPic::getDayBothErrNum(QString date)
{
	QSqlQuery query(dbToStatistic);
	QString tableName = dbToStatistic.tables()[0];
	query.exec(tr("select * from %1 where Date = '%2' and Result = 'Both Extra and Missing Coating Error'").arg(tableName).arg(date));
	int b = 0;
	while (query.next())
	{
		b++;
	}
	return b;
}

int myStatisticPic::getDayQualityNum(QString date)
{
	QSqlQuery query(dbToStatistic);
	QString tableName = dbToStatistic.tables()[0];
	query.exec(tr("select * from %1 where Date = '%2' and Result = 'No Error'").arg(tableName).arg(date));
	int b = 0;
	while (query.next())
	{
		b++;
	}
	return b;
}

int myStatisticPic::getWholeOnlyExErrNum()
{
	QSqlQuery query(dbToStatistic);
	QString tableName = dbToStatistic.tables()[0];
	query.exec(tr("select * from %1 where Result = 'Extra Coating Error'").arg(tableName));
	int b = 0;
	while (query.next())
	{
		b++;
	}
	return b;
}

int myStatisticPic::getWholeOnlyMiErNum()
{
	QSqlQuery query(dbToStatistic);
	QString tableName = dbToStatistic.tables()[0];
	query.exec(tr("select * from %1 where Result = 'Missing Coating Error'").arg(tableName));
	int b = 0;
	while (query.next())
	{
		b++;
	}
	return b;
}

int myStatisticPic::getWholeBothErrNum()
{
	QSqlQuery query(dbToStatistic);
	QString tableName = dbToStatistic.tables()[0];
	query.exec(tr("select * from %1 where Result = 'Both Extra and Missing Coating Error'").arg(tableName));
	int b = 0;
	while (query.next())
	{
		b++;
	}
	return b;
}

int myStatisticPic::getWholeQualityNum()
{
	QSqlQuery query(dbToStatistic);
	QString tableName = dbToStatistic.tables()[0];
	query.exec(tr("select * from %1 where Result = 'No Error'").arg(tableName));
	int b = 0;
	while (query.next())
	{
		b++;
	}
	return b;
}
