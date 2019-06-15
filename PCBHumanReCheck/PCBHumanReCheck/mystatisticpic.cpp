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
	QString currentDate = qDate.toString("yyyyMMdd");

	QPieSeries *seriesError = new QPieSeries();
	seriesError->setName(QString::fromLocal8Bit("瑕疵PCB缺陷类型"));
	seriesError->append(QString::fromLocal8Bit("少涂缺陷"), getDayOnlyMiErNum(currentDate));
	seriesError->append(QString::fromLocal8Bit("多涂缺陷"), getDayOnlyExErrNum(currentDate));
	seriesError->append(QString::fromLocal8Bit("少涂和多涂缺陷"), getDayBothErrNum(currentDate));

	QPieSeries *seriesQualify = new QPieSeries();
	seriesQualify->setName(QString::fromLocal8Bit("合格PCB"));
	seriesQualify->append(QString::fromLocal8Bit("合格"), getDayQualityNum(currentDate));

	DonutBreakdownChart *donutBreakdown = new DonutBreakdownChart();
	donutBreakdown->setAnimationOptions(QChart::AllAnimations);
	donutBreakdown->setTitle(tr("%1.%2.%3").arg(qDate.year()).arg(qDate.month()).arg(qDate.day()) + QString::fromLocal8Bit("  PCB涂覆质量检测结果"));
	donutBreakdown->legend()->setAlignment(Qt::AlignRight);
	donutBreakdown->addBreakdownSeries(seriesError, Qt::red);
	donutBreakdown->addBreakdownSeries(seriesQualify, Qt::darkGreen);

	ui.pieToday->setChart(donutBreakdown);
	ui.pieToday->setRenderHint(QPainter::Antialiasing);
}

void myStatisticPic::drawPieWhole()
{
	QPieSeries *seriesError = new QPieSeries();
	seriesError->setName(QString::fromLocal8Bit("瑕疵PCB缺陷类型"));
	seriesError->append(QString::fromLocal8Bit("少涂缺陷"), getWholeOnlyMiErNum());
	seriesError->append(QString::fromLocal8Bit("多涂缺陷"), getWholeOnlyExErrNum());
	seriesError->append(QString::fromLocal8Bit("少涂和多涂缺陷"), getWholeBothErrNum());

	QPieSeries *seriesQualify = new QPieSeries();
	seriesQualify->setName(QString::fromLocal8Bit("合格PCB"));
	seriesQualify->append(QString::fromLocal8Bit("合格"), getWholeQualityNum());

	DonutBreakdownChart *donutBreakdown = new DonutBreakdownChart();
	donutBreakdown->setAnimationOptions(QChart::AllAnimations);
	donutBreakdown->setTitle(QString::fromLocal8Bit("PCB涂覆质量"));
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
	chart->setTitle(QString::fromLocal8Bit("PCB涂覆质量变化趋势图"));

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
	query.exec("create table reCheckRes (PCBID varchar(30) primary key, "
		"CarrierID varchar(30), REGIONID varchar(10), Date varchar(20), Time varchar(20), "
		"Result varchar(30), ExtraErrorNumF varchar(10), MissErrorNumF varchar(10), "
		"ExtraErrorNumB varchar(10), MissErrorNumB varchar(10), resImgPath varchar(100))");

	query.exec("select distinct Date from reCheckRes order by Date");
	while (query.next())
	{
		dates.push_back(query.value(QString("Date")).toString());
	}
}

int myStatisticPic::getDayOnlyExErrNum(QString date)
{
	QSqlQuery query(dbToStatistic);
	query.exec("create table reCheckRes (PCBID varchar(30) primary key, "
		"CarrierID varchar(30), REGIONID varchar(10), Date varchar(20), Time varchar(20), "
		"Result varchar(30), ExtraErrorNumF varchar(10), MissErrorNumF varchar(10), "
		"ExtraErrorNumB varchar(10), MissErrorNumB varchar(10), resImgPath varchar(100))");

	query.exec(tr("select * from reCheckRes where Date = '%1' and Result = 'Extra Coating Error'").arg(date));
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
	query.exec("create table reCheckRes (PCBID varchar(30) primary key, "
		"CarrierID varchar(30), REGIONID varchar(10), Date varchar(20), Time varchar(20), "
		"Result varchar(30), ExtraErrorNumF varchar(10), MissErrorNumF varchar(10), "
		"ExtraErrorNumB varchar(10), MissErrorNumB varchar(10), resImgPath varchar(100))");

	query.exec(tr("select * from reCheckRes where Date = '%1' and Result = 'Missing Coating Error'").arg(date));
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
	//QString tableName = dbToStatistic.tables()[0];
	query.exec(tr("select * from reCheckRes where Date = '%1' and Result = 'Both Extra and Missing Coating Error'").arg(date));
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
	//QString tableName = dbToStatistic.tables()[0];
	query.exec(tr("select * from reCheckRes where Date = '%1' and Result = 'No Error'").arg(date));
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
	//QString tableName = dbToStatistic.tables()[0];
	query.exec(tr("select * from reCheckRes where Result = 'Extra Coating Error'"));
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
	//QString tableName = dbToStatistic.tables()[0];
	query.exec(tr("select * from reCheckRes where Result = 'Missing Coating Error'"));
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
	//QString tableName = dbToStatistic.tables()[0];
	query.exec(tr("select * from reCheckRes where Result = 'Both Extra and Missing Coating Error'"));
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
	//QString tableName = dbToStatistic.tables()[0];
	query.exec(tr("select * from reCheckRes where Result = 'No Error'"));
	int b = 0;
	while (query.next())
	{
		b++;
	}
	return b;
}
