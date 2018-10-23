#include "mymainwindow.h"
#include "parameters.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QFileDialog>


myMainWindow::myMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	databaseAutoName = "";
	databaseManuName = "";
	resFileToMESPath = "";
	resFileToGetPath = "";
	OKModel = false;
	isLogin = false;

	ui.setupUi(this);

	isLogin = false;
	ui.actionOKNotAuto->setChecked(true);

	connect(ui.actLogin, SIGNAL(triggered()), this, SLOT(toLog()));
	connect(ui.actViewDatabase, SIGNAL(triggered()), this, SLOT(showDatabaseTable()));
	connect(ui.actSettings, SIGNAL(triggered()), this, SLOT(showSettingWin()));

	connect(ui.actionNewDB, SIGNAL(triggered()), this, SLOT(newDatabase()));
	connect(ui.actionSetARdb, SIGNAL(triggered()), this, SLOT(setDatabaseAuto()));
	connect(ui.actionOpenMRdb, SIGNAL(triggered()), this, SLOT(setDatabaseManu()));
	connect(ui.actionSetPathToMES, SIGNAL(triggered()), this, SLOT(setResFileToMESPath()));
	connect(ui.actionSetResFilePath, SIGNAL(triggered()), this, SLOT(setResFileToGetPath()));
	connect(ui.actionOKAuto, SIGNAL(triggered()), this, SLOT(setTransferModelAuto()));
	connect(ui.actionOKNotAuto, SIGNAL(triggered()), this, SLOT(setTransferModelNotAuto()));

	connect(ui.onePCBID, SIGNAL(returnPressed()), this, SLOT(showAutoCarrierInfo()));
	connect(ui.setResPathToMESBt, SIGNAL(clicked()), this, SLOT(setResFileToMESPath()));

	connect(this, SIGNAL(readyCheck()), this, SLOT(showReadyMessage()));
}

myMainWindow::~myMainWindow()
{
}

void myMainWindow::toLog()
{
	if(isLogin)
	{
		int r = QMessageBox::question(this, tr("Logout"), tr("You has logged in.\nDo you want to logout now?"), QMessageBox::Yes, QMessageBox::No);
		if (r == QMessageBox::Yes)
		{
			isLogin = false;
			ui.actLogin->setChecked(false);

			if (loginWin != Q_NULLPTR)
			{
				loginWin->winClose();
			}

			emit readyCheck();
		}
		else if(r == QMessageBox::No)
		{
			ui.actLogin->setChecked(true);

			if (loginWin != Q_NULLPTR)
			{
				loginWin->winClose();
			}
		}
	}
	else
	{
		loginWin = new toLogin;
		connect(loginWin, SIGNAL(okToLogin()), this, SLOT(beLogged()));
		loginWin->show();
	}
}

void myMainWindow::beLogged()
{
	isLogin = true;
	ui.actLogin->setChecked(true);

	if(loginWin != Q_NULLPTR)
	{
		loginWin->winClose();
	}
	emit readyCheck();
}

int myMainWindow::showDatabaseTable()
{
	if (!dbOfManuRes.isValid())
	{
		QString fileName = QFileDialog::getOpenFileName(this, tr("Load Manual ReCheckRes Database"), ".", tr("Settings (*.db)"));
		if (fileName.isEmpty())
		{
			return -1;
		}

		dbOfManuRes = QSqlDatabase::addDatabase("QSQLITE", "RESULT_DB");
		dbOfManuRes.setDatabaseName(fileName);

		if (!dbOfManuRes.open())
		{
			QMessageBox::warning(this, "Link Failed", "Please choose a SQLite3 database", QMessageBox::Abort);
			return -1;
		}
		databaseManuName = fileName;
		if (settingWindow != Q_NULLPTR)
		{
			settingWindow->updateDatabaseManuFile(fileName);
		}
		emit readyCheck();
	}

	QSqlQuery query(dbOfManuRes);
	query.exec("create table reCheckRes (PCBID varchar(30) primary key, "
		"CarrierID varchar(30), Date varchar(20), Time varchar(20), Checker varchar(10), Device varchar(10), Result varchar(30))");

	databaseView = new myDatabaseTable(dbOfManuRes);
	databaseView->show();
	return 0;
}

void myMainWindow::showSettingWin()
{
	settingWindow = new mySettingWindow(databaseAutoName, databaseManuName, resFileToGetPath, resFileToMESPath, OKModel);
	connect(settingWindow, SIGNAL(newDatabaseAutoName(QString)), this, SLOT(updateDatabaseAutoFile(QString)));
	connect(settingWindow, SIGNAL(newDatabaseManuName(QString)), this, SLOT(updateDatabaseManuFile(QString)));
	connect(settingWindow, SIGNAL(newResFileToGetPath(QString)), this, SLOT(updateResFileToGetPath(QString)));
	connect(settingWindow, SIGNAL(newResFileToMESPath(QString)), this, SLOT(updateResFileToMESPath(QString)));
	connect(settingWindow, SIGNAL(newOKModel(bool)), this, SLOT(updateOKModel(bool)));
	settingWindow->show();
}

void myMainWindow::newDatabase()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Create new Manual ReCheckRes Database"), ".", tr("Settings (*.db);"));
	if (fileName.isEmpty())
	{
		return;
	}

	if (!dbOfManuRes.isValid())
	{
		dbOfManuRes = QSqlDatabase::addDatabase("QSQLITE", "AUTO_RESULT_DB");
	}

	dbOfManuRes.setDatabaseName(fileName);

	if (!dbOfManuRes.open())
	{
		QMessageBox::warning(this, "Link Failed", "Please choose a SQLite3 database", QMessageBox::Abort);
		return;
	}

	databaseManuName = fileName;
	if (settingWindow != Q_NULLPTR)
	{
		settingWindow->updateDatabaseAutoFile(fileName);
	}
	emit readyCheck();
}

void myMainWindow::setDatabaseAuto()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Load AutoCheck Result Database"), ".", tr("Settings (*.db)"));
	if (fileName.isEmpty())
	{
		return;
	}

	if (!dbOfAutoRes.isValid())
	{
		dbOfAutoRes = QSqlDatabase::addDatabase("QSQLITE", "AUTO_RESULT_DB");
	}

	dbOfAutoRes.setDatabaseName(fileName);

	if (!dbOfAutoRes.open())
	{
		QMessageBox::warning(this, "Link Failed", "Please choose a SQLite3 database", QMessageBox::Abort);
		return;
	}

	databaseAutoName = fileName;
	if(settingWindow != Q_NULLPTR)
	{
		settingWindow->updateDatabaseAutoFile(fileName);
	}
	emit readyCheck();
}

void myMainWindow::setDatabaseManu()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Load Manual ReCheckRes Database"), ".", tr("Settings (*.db)"));
	if (fileName.isEmpty())
	{
		return;
	}

	if (!dbOfManuRes.isValid())
	{
		dbOfManuRes = QSqlDatabase::addDatabase("QSQLITE", "MANU_RESULT_DB");
	}

	dbOfManuRes.setDatabaseName(fileName);

	if (!dbOfManuRes.open())
	{
		QMessageBox::warning(this, "Link Failed", "Please choose a SQLite3 database", QMessageBox::Abort);
		return;
	}

	databaseManuName = fileName;
	if (settingWindow != Q_NULLPTR)
	{
		settingWindow->updateDatabaseManuFile(fileName);
	}
	emit readyCheck();
}

void myMainWindow::setResFileToGetPath()
{
	resFileToGetPath = QFileDialog::getExistingDirectory(this);
	if (settingWindow != Q_NULLPTR)
	{
		settingWindow->updateResFileToGetPath(resFileToGetPath);
	}
	emit readyCheck();
}

void myMainWindow::setResFileToMESPath()
{
	resFileToMESPath = QFileDialog::getExistingDirectory(this);

	ui.resultToMESPathLab->setText(resFileToMESPath);
	if (settingWindow != Q_NULLPTR)
	{
		settingWindow->updateResFileToMESPath(resFileToMESPath);
	}
	emit readyCheck();
}

void myMainWindow::setTransferModelAuto()
{
	if(ui.actionOKAuto->isChecked())
	{
		OKModel = true;
		disconnect(ui.actionOKNotAuto, SIGNAL(triggered()), this, SLOT(setTransferModelNotAuto()));
		ui.actionOKNotAuto->setChecked(false);
		connect(ui.actionOKNotAuto, SIGNAL(triggered()), this, SLOT(setTransferModelNotAuto()));
	}
	else
	{
		OKModel = false;
		disconnect(ui.actionOKNotAuto, SIGNAL(triggered()), this, SLOT(setTransferModelNotAuto()));
		ui.actionOKNotAuto->setChecked(true);
		connect(ui.actionOKNotAuto, SIGNAL(triggered()), this, SLOT(setTransferModelNotAuto()));
	}

	if (settingWindow != Q_NULLPTR)
	{
		settingWindow->updateOKModel(OKModel);
	}

	emit readyCheck();
}

void myMainWindow::setTransferModelNotAuto()
{
	if(ui.actionOKNotAuto->isChecked())
	{
		OKModel = false;
		disconnect(ui.actionOKAuto, SIGNAL(triggered()), this, SLOT(setTransferModelAuto()));
		ui.actionOKAuto->setChecked(false);
		connect(ui.actionOKAuto, SIGNAL(triggered()), this, SLOT(setTransferModelAuto()));
	}
	else
	{
		OKModel = true;
		disconnect(ui.actionOKAuto, SIGNAL(triggered()), this, SLOT(setTransferModelAuto()));
		ui.actionOKAuto->setChecked(true);
		connect(ui.actionOKAuto, SIGNAL(triggered()), this, SLOT(setTransferModelAuto()));
	}

	if (settingWindow != Q_NULLPTR)
	{
		settingWindow->updateOKModel(OKModel);
	}
	emit readyCheck();
}

void myMainWindow::updateDatabaseAutoFile(QString fileName)
{
	if (fileName.isEmpty())
	{
		return;
	}

	if (!dbOfAutoRes.isValid())
	{
		dbOfAutoRes = QSqlDatabase::addDatabase("QSQLITE", "AUTO_RESULT_DB");
	}

	dbOfAutoRes.setDatabaseName(fileName);

	if (!dbOfAutoRes.open())
	{
		QMessageBox::warning(this, "Link Failed", "Please choose a SQLite3 database", QMessageBox::Abort);
		return;
	}

	databaseAutoName = fileName;
	emit readyCheck();
}

void myMainWindow::updateDatabaseManuFile(QString fileName)
{
	if (fileName.isEmpty())
	{
		return;
	}

	if (!dbOfManuRes.isValid())
	{
		dbOfManuRes = QSqlDatabase::addDatabase("QSQLITE", "MANU_RESULT_DB");
	}

	dbOfManuRes.setDatabaseName(fileName);

	if (!dbOfManuRes.open())
	{
		QMessageBox::warning(this, "Link Failed", "Please choose a SQLite3 database", QMessageBox::Abort);
		return;
	}

	databaseManuName = fileName;
	emit readyCheck();
}

void myMainWindow::updateResFileToGetPath(QString filePath)
{
	resFileToGetPath = filePath;
	emit readyCheck();
}

void myMainWindow::updateResFileToMESPath(QString filePath)
{
	resFileToMESPath = filePath;
	ui.resultToMESPathLab->setText(resFileToMESPath);
	emit readyCheck();
}

void myMainWindow::updateOKModel(bool isOKTransfer)
{
	OKModel = isOKTransfer;

	disconnect(ui.actionOKAuto, SIGNAL(triggered()), this, SLOT(setTransferModelAuto()));
	ui.actionOKAuto->setChecked(OKModel);
	connect(ui.actionOKAuto, SIGNAL(triggered()), this, SLOT(setTransferModelAuto()));

	disconnect(ui.actionOKNotAuto, SIGNAL(triggered()), this, SLOT(setTransferModelNotAuto()));
	ui.actionOKNotAuto->setChecked(!OKModel);
	connect(ui.actionOKNotAuto, SIGNAL(triggered()), this, SLOT(setTransferModelNotAuto()));
	emit readyCheck();
}

void myMainWindow::showAutoCarrierInfo()
{
	QString onePCBId = ui.onePCBID->text();
	QString carrierID = getCarrierID(onePCBId);

	if (!dbOfAutoRes.isValid())
	{
		QString fileName = QFileDialog::getOpenFileName(this, tr("Load AutoCheck Result Database"), ".", tr("Settings (*.db)"));
		if (fileName.isEmpty())
		{
			return;
		}

		dbOfAutoRes = QSqlDatabase::addDatabase("QSQLITE", "AUTO_RESULT_DB");
		dbOfAutoRes.setDatabaseName(fileName);

		if (!dbOfAutoRes.open())
		{
			QMessageBox::warning(this, "Link Failed", "Please choose a SQLite3 database", QMessageBox::Abort);
		}
		databaseAutoName = fileName;
		if (settingWindow != Q_NULLPTR)
		{
			settingWindow->updateDatabaseAutoFile(fileName);
		}
	}

	if (modelAutoResQuery == Q_NULLPTR)
	{
		modelAutoResQuery = new QSqlQueryModel;
		modelAutoResQuery->setQuery("select PCBID,REGIONID,Result,ExtraErrorNumF,MissErrorNumF,ExtraErrorNumB,MissErrorNumB from checkRes where CarrierID = '" + carrierID + "'", dbOfAutoRes);
		modelAutoResQuery->setHeaderData(0, Qt::Horizontal, tr("PCBID"));
		modelAutoResQuery->setHeaderData(1, Qt::Horizontal, tr("RegionID"));
		modelAutoResQuery->setHeaderData(2, Qt::Horizontal, tr("Result"));
		modelAutoResQuery->setHeaderData(3, Qt::Horizontal, tr("ExtraErrorNumF"));
		modelAutoResQuery->setHeaderData(4, Qt::Horizontal, tr("MissErrorNumF"));
		modelAutoResQuery->setHeaderData(5, Qt::Horizontal, tr("ExtraErrorNumB"));
		modelAutoResQuery->setHeaderData(6, Qt::Horizontal, tr("MissErrorNumB"));

		ui.carrierAutoResTableView->setModel(modelAutoResQuery);
	}
	else
	{
		modelAutoResQuery->setQuery("select PCBID,REGIONID,Result,ExtraErrorNumF,MissErrorNumF,ExtraErrorNumB,MissErrorNumB from checkRes where CarrierID = '" + carrierID + "'", dbOfAutoRes);
		modelAutoResQuery->setHeaderData(0, Qt::Horizontal, tr("PCBID"));
		modelAutoResQuery->setHeaderData(1, Qt::Horizontal, tr("RegionID"));
		modelAutoResQuery->setHeaderData(2, Qt::Horizontal, tr("Result"));
		modelAutoResQuery->setHeaderData(3, Qt::Horizontal, tr("ExtraErrorNumF"));
		modelAutoResQuery->setHeaderData(4, Qt::Horizontal, tr("MissErrorNumF"));
		modelAutoResQuery->setHeaderData(5, Qt::Horizontal, tr("ExtraErrorNumB"));
		modelAutoResQuery->setHeaderData(6, Qt::Horizontal, tr("MissErrorNumB"));
	}
}

void myMainWindow::showReadyMessage()
{
	if(isLogin && !resFileToMESPath.isEmpty() && !databaseManuName.isEmpty() && !databaseAutoName.isEmpty() && ui.onePCBID->text().isEmpty())
	{
		if(OKModel)
		{
			ui.statusBar->showMessage("Ready for human rechecking.OK results are not rechecked.Please put the cursor in the onePCBID label for ID information.");
		}
		else
		{
			ui.statusBar->showMessage("Ready for human rechecking.OK results are also rechecked.Please put the cursor in the onePCBID label for ID information.");
		}
	}
	else
	{
		ui.statusBar->showMessage("Not ready for human rechecking.");
	}
}

QString myMainWindow::getCarrierID(QString onePCBID)
{
	QString carrierID = "";
	QString checkDate = "";
	QString checkTime = "";

	if (!dbOfAutoRes.isValid())
	{
		QString fileName = QFileDialog::getOpenFileName(this, tr("Load AutoCheck Result Database"), ".", tr("Settings (*.db)"));
		if (fileName.isEmpty())
		{
			return carrierID;
		}

		dbOfAutoRes = QSqlDatabase::addDatabase("QSQLITE", "AUTO_RESULT_DB");
		dbOfAutoRes.setDatabaseName(fileName);

		if (!dbOfAutoRes.open())
		{
			QMessageBox::warning(this, "Link Failed", "Please choose a SQLite3 database", QMessageBox::Abort);
		}

		databaseAutoName = fileName;
		if (settingWindow != Q_NULLPTR)
		{
			settingWindow->updateDatabaseAutoFile(fileName);
		}
	}

	QSqlQuery query(dbOfAutoRes);
	query.exec("create table checkRes (PCBID varchar(30) primary key, "
		"CarrierID varchar(30), REGIONID varchar(10), Date varchar(20), Time varchar(20), "
		"Result varchar(30), ExtraErrorNumF varchar(10), MissErrorNumF varchar(10), "
		"ExtraErrorNumB varchar(10), MissErrorNumB varchar(10), resImgPath varchar(100))");
	query.exec("select * from checkRes where PCBID = '" + onePCBID + "'");

	if(query.next())
	{
		carrierID = query.value(1).toString();
		checkDate = query.value(3).toString();
		checkTime = query.value(4).toString();
	}

	return carrierID;
}

void myMainWindow::closeEvent(QCloseEvent* event)
{
}

