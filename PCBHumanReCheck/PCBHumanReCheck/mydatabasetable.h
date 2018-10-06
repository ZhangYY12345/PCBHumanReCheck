#pragma once

#include <QWidget>
#include "ui_mydatabasetable.h"
#include "mystatisticpic.h"
#include <QSqlTableModel>

class myDatabaseTable : public QWidget
{
	Q_OBJECT

public:
	myDatabaseTable(QWidget *parent = Q_NULLPTR);
	myDatabaseTable(QSqlDatabase& db, QWidget *parent = Q_NULLPTR);
	~myDatabaseTable();

	void closeDatabaseTable();

	private slots:
	void toQuery();
	void toShowAll();
	void toShowStatistic();

	void toSubmit();
	void toRecall();
	void toAdd();
	void toDelete();
	void descendOrder();
	void acsendOrder();

private:
	Ui::myDatabaseTable ui;
	QSqlTableModel* model = Q_NULLPTR;
	myStatisticPic* statisticWin = Q_NULLPTR;

	int extraCoatingOnlyNum;
	int missCoatingOnlyNum;
	int bothErrorNum;
	int qualifiedNum;

};
