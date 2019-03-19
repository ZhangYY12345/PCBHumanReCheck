#include "mydatabasetable.h"
#include <QtSql/QSqlError>
#include <QMessageBox>


myDatabaseTable::myDatabaseTable(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	model = new QSqlTableModel(this);
	model->setTable("checkRes");
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	model->select();

	ui.dbTableView->setModel(model);
	ui.dbTableView->setColumnWidth(0, 80);
	ui.dbTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	ui.dbTableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
	ui.dbTableView->resizeColumnsToContents();

	connect(ui.queryButton, SIGNAL(clicked()), this, SLOT(toQuery()));
	connect(ui.showAllButton, SIGNAL(clicked()), this, SLOT(toShowAll()));

	connect(ui.addButton, SIGNAL(clicked()), this, SLOT(toAdd()));
	connect(ui.deleteButton, SIGNAL(clicked()), this, SLOT(toDelete()));
	connect(ui.submitButton, SIGNAL(clicked()), this, SLOT(toSubmit()));
	connect(ui.recallButton, SIGNAL(clicked()), this, SLOT(toRecall()));

	connect(ui.statisticButton, SIGNAL(clicked()), this, SLOT(toShowStatistic()));
	connect(ui.descendButton, SIGNAL(clicked()), this, SLOT(descendOrder()));
	connect(ui.ascendButton, SIGNAL(clicked()), this, SLOT(acsendOrder()));

}

myDatabaseTable::myDatabaseTable(QSqlDatabase& db, QWidget* parent)
{
	ui.setupUi(this);
	model = new QSqlTableModel(this, db);
	QStringList tableList = db.tables();
	if (tableList.isEmpty())
	{
		model->setTable("checkRes");
	}
	else
	{
		model->setTable(tableList[0]);
	}

	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	model->select();

	ui.dbTableView->setModel(model);
	ui.dbTableView->setColumnWidth(0, 80);
	ui.dbTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	ui.dbTableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
	ui.dbTableView->resizeColumnsToContents();

	connect(ui.queryButton, SIGNAL(clicked()), this, SLOT(toQuery()));
	connect(ui.showAllButton, SIGNAL(clicked()), this, SLOT(toShowAll()));

	connect(ui.addButton, SIGNAL(clicked()), this, SLOT(toAdd()));
	connect(ui.deleteButton, SIGNAL(clicked()), this, SLOT(toDelete()));
	connect(ui.submitButton, SIGNAL(clicked()), this, SLOT(toSubmit()));
	connect(ui.recallButton, SIGNAL(clicked()), this, SLOT(toRecall()));

	connect(ui.statisticButton, SIGNAL(clicked()), this, SLOT(toShowStatistic()));
	connect(ui.descendButton, SIGNAL(clicked()), this, SLOT(descendOrder()));
	connect(ui.ascendButton, SIGNAL(clicked()), this, SLOT(acsendOrder()));
}

myDatabaseTable::~myDatabaseTable()
{
}

void myDatabaseTable::closeDatabaseTable()
{
	if (model != Q_NULLPTR)
	{
		model->clear();
		delete model;
	}

	if (statisticWin != Q_NULLPTR)
	{
		statisticWin->winClose();
		delete statisticWin;
	}
}

void myDatabaseTable::toQuery()
{
	QString queryoption;
	if (ui.idEdit->text() != "")
	{
		queryoption = "PCBID = '" + ui.idEdit->text();
	}

	if (ui.typeEdit->text() != "")
	{
		if (queryoption == "")
		{
			queryoption = "CarrierID = '" + ui.typeEdit->text();
		}
		else
		{
			queryoption += "' and CarrierID = '" + ui.typeEdit->text();
		}
	}

	if (ui.regionEdit->text() != "")
	{
		if (queryoption == "")
		{
			queryoption = "REGIONID = '" + ui.regionEdit->text();
		}
		else
		{
			queryoption += "' and REGIONID = '" + ui.regionEdit->text();
		}
	}

	if (ui.dateEdit->text() != "")
	{
		if (queryoption == "")
		{
			queryoption = "Date = '" + ui.dateEdit->text();
		}
		else
		{
			queryoption += "' and Date = '" + ui.dateEdit->text();
		}
	}

	if (ui.resEdit->text() != "")
	{
		if (queryoption == "")
		{
			queryoption = "Result = '" + ui.resEdit->text();
		}
		else
		{
			queryoption += "' and Result = '" + ui.resEdit->text();
		}
	}

	if (queryoption == "")
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("查询出错"), QString::fromLocal8Bit("查询项为空。"), QMessageBox::Abort);
		return;
	}
	else
	{
		queryoption += "'";
	}

	model->setFilter(queryoption);
	model->select();
	//qDebug() << model->rowCount() << endl;
}

void myDatabaseTable::toShowAll()
{
	model->setTable("checkRes");
	model->select();
}

void myDatabaseTable::toShowStatistic()
{
	//extraCoatingOnlyNum
	QSqlDatabase db = model->database();
	statisticWin = new myStatisticPic(db);
	statisticWin->show();
}

void myDatabaseTable::toSubmit()
{
	model->database().transaction();
	if (model->submitAll())
	{
		model->database().commit();
	}
	else
	{
		model->database().rollback();
		QMessageBox::warning(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("数据库操作错误：")+ tr("%1").arg(model->lastError().text()));
	}
}

void myDatabaseTable::toRecall()
{
	model->revertAll();
}

void myDatabaseTable::toAdd()
{
	int rowNum = model->rowCount();
	QString id = ui.toAddID->text();
	model->insertRow(rowNum);
	model->setData(model->index(rowNum, 0), ui.toAddID->text(), Qt::TextAlignmentRole);
	//model->data(model->index(rowNum, 0), Qt::TextAlignmentRole);
}

void myDatabaseTable::toDelete()
{
	int curRow = ui.dbTableView->currentIndex().row();

	model->removeRow(curRow);

	int ok = QMessageBox::warning(this, QString::fromLocal8Bit("删除当前行"),
		QString::fromLocal8Bit("是否确认删除当前行？"), QMessageBox::Yes, QMessageBox::No);
	if (ok == QMessageBox::No)
	{
		model->revertAll();
	}
	else
	{
		model->submitAll();
	}
}

void myDatabaseTable::descendOrder()
{
	model->setSort(0, Qt::DescendingOrder);
	model->select();
}

void myDatabaseTable::acsendOrder()
{
	model->setSort(0, Qt::AscendingOrder);
	model->select();
}
