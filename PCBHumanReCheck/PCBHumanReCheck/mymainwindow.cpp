#include "mymainwindow.h"
#include "parameters.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QFileDialog>
#include <QNetworkInterface>

extern REGION_IN_CARRIER g_Views[8];
extern std::map<REGION_IN_CARRIER, std::string> g_viewName;
extern std::map<std::string, REGION_IN_CARRIER> g_viewName_Reverse;

myMainWindow::myMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	databaseAutoName = "";
	databaseManuName = "";
	resFileToMESPath = "";
	resFileToGetPath = "";
	OKModel = false;
	isLogin = false;
	userName = "";


	ui.setupUi(this);

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
	connect(ui.widthErrCon, SIGNAL(currentIndexChanged(QString)), this, SLOT(refreshErrConWidth(QString)));

	connect(ui.viewIDComBox, SIGNAL(currentIndextChanged(QString)), this, SLOT(resViewUpdate(QString)));
	connect(ui.viewFBSide, SIGNAL(currentIndexChanged(int)), this, SLOT(resViewSideUpdate(int)));

	connect(this, SIGNAL(readyCheck()), this, SLOT(showReadyMessage()));

	ui.onePCBID->setEnabled(false);
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
		connect(loginWin, SIGNAL(okToLogin(QString)), this, SLOT(beLogged(QString)));
		loginWin->show();
	}
}

void myMainWindow::beLogged(QString nameUser)
{
	userName = nameUser;
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
		QString fileName = QFileDialog::getOpenFileName(this, tr("Load Manual ReCheckRes Database"), ".", tr("Databases (*.db)"));
		if (fileName.isEmpty())
		{
			return -1;
		}
		if(fileName.indexOf("userdata.db") != -1)
		{
			QMessageBox::warning(this, "Link Failed", "You have no access to this database.Please choose a SQLite3 database", QMessageBox::Abort);
			return -1;
		}

		dbOfManuRes = QSqlDatabase::addDatabase("QSQLITE", "MANU_RESULT_DB");
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
		"CarrierID varchar(30), REGIONID varchar(10), Date varchar(20), Time varchar(20), "
		"Result varchar(30), ExtraErrorNumF varchar(10), MissErrorNumF varchar(10), "
		"ExtraErrorNumB varchar(10), MissErrorNumB varchar(10), resImgPath varchar(100))");

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
	QString fileName = QFileDialog::getSaveFileName(this, tr("Create new Manual ReCheckRes Database"), ".", tr("Databases (*.db);"));
	if (fileName.isEmpty())
	{
		return;
	}
	if (fileName.indexOf("userdata.db") != -1)
	{
		QMessageBox::warning(this, "Link Failed", "You have no access to this database.Please choose a SQLite3 database", QMessageBox::Abort);
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

void myMainWindow::setDatabaseAuto()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Load AutoCheck Result Database"), ".", tr("Databases (*.db)"));
	if (fileName.isEmpty())
	{
		return;
	}
	if (fileName.indexOf("userdata.db") != -1)
	{
		QMessageBox::warning(this, "Link Failed", "You have no access to this database.Please choose a SQLite3 database", QMessageBox::Abort);
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
	QString fileName = QFileDialog::getOpenFileName(this, tr("Load Manual ReCheckRes Database"), ".", tr("Databases (*.db)"));
	if (fileName.isEmpty())
	{
		return;
	}
	if (fileName.indexOf("userdata.db") != -1)
	{
		QMessageBox::warning(this, "Link Failed", "You have no access to this database.Please choose a SQLite3 database", QMessageBox::Abort);
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
	if (fileName.indexOf("userdata.db") != -1)
	{
		QMessageBox::warning(this, "Link Failed", "You have no access to this database.Please choose a SQLite3 database", QMessageBox::Abort);
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
	if (fileName.indexOf("userdata.db") != -1)
	{
		QMessageBox::warning(this, "Link Failed", "You have no access to this database.Please choose a SQLite3 database", QMessageBox::Abort);
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
	QString carrierID;
	QString carrierCheckDate;

	getCarrierID_Date(onePCBId, carrierID, carrierCheckDate);
	getCarrierResInfo(carrierID, carrierCheckDate);

	this->carrierID = carrierID;

	if (!dbOfAutoRes.isValid())
	{
		QString fileName = QFileDialog::getOpenFileName(this, tr("Load AutoCheck Result Database"), ".", tr("Databases (*.db)"));
		if (fileName.isEmpty())
		{
			return;
		}
		if (fileName.indexOf("userdata.db") != -1)
		{
			QMessageBox::warning(this, "Link Failed", "You have no access to this database.Please choose a SQLite3 database", QMessageBox::Abort);
			return;
		}

		dbOfAutoRes = QSqlDatabase::addDatabase("QSQLITE", "AUTO_RESULT_DB");
		dbOfAutoRes.setDatabaseName(fileName);

		if (!dbOfAutoRes.open())
		{
			QMessageBox::warning(this, "Link Failed", "Please choose a SQLite3 database", QMessageBox::Abort);
			return;
		}
		databaseAutoName = fileName;
		if (settingWindow != Q_NULLPTR)
		{
			settingWindow->updateDatabaseAutoFile(fileName);
		}
	}

	if (modelAutoResQuery == Q_NULLPTR)
	{
		modelAutoResQuery = new QSqlQueryModel();
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

void myMainWindow::showManuCarrierInfo()
{
	if (!dbOfManuRes.isValid())
	{
		QString fileName = QFileDialog::getOpenFileName(this, tr("Load Manual ReCheckRes Database"), ".", tr("Databases (*.db)"));
		if (fileName.isEmpty())
		{
			return;
		}
		if (fileName.indexOf("userdata.db") != -1)
		{
			QMessageBox::warning(this, "Link Failed", "You have no access to this database.Please choose a SQLite3 database", QMessageBox::Abort);
			return;
		}

		dbOfManuRes = QSqlDatabase::addDatabase("QSQLITE", "MANU_RESULT_DB");
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
	}

	if (modelManuResQuery == Q_NULLPTR)
	{
		modelManuResQuery = new QSqlQueryModel();
		modelManuResQuery->setQuery("select PCBID,REGIONID,Result,ExtraErrorNumF,MissErrorNumF,ExtraErrorNumB,MissErrorNumB from reCheckRes where CarrierID = '" + carrierID + "'", dbOfManuRes);
		modelManuResQuery->setHeaderData(0, Qt::Horizontal, tr("PCBID"));
		modelManuResQuery->setHeaderData(1, Qt::Horizontal, tr("RegionID"));
		modelManuResQuery->setHeaderData(2, Qt::Horizontal, tr("Result"));
		modelManuResQuery->setHeaderData(3, Qt::Horizontal, tr("ExtraErrorNumF"));
		modelManuResQuery->setHeaderData(4, Qt::Horizontal, tr("MissErrorNumF"));
		modelManuResQuery->setHeaderData(5, Qt::Horizontal, tr("ExtraErrorNumB"));
		modelManuResQuery->setHeaderData(6, Qt::Horizontal, tr("MissErrorNumB"));

		ui.carrierManuResTableView->setModel(modelManuResQuery);
	}
	else
	{
		modelManuResQuery->setQuery("select PCBID,REGIONID,Result,ExtraErrorNumF,MissErrorNumF,ExtraErrorNumB,MissErrorNumB from reCheckRes where CarrierID = '" + carrierID + "'", dbOfManuRes);
		modelManuResQuery->setHeaderData(0, Qt::Horizontal, tr("PCBID"));
		modelManuResQuery->setHeaderData(1, Qt::Horizontal, tr("RegionID"));
		modelManuResQuery->setHeaderData(2, Qt::Horizontal, tr("Result"));
		modelManuResQuery->setHeaderData(3, Qt::Horizontal, tr("ExtraErrorNumF"));
		modelManuResQuery->setHeaderData(4, Qt::Horizontal, tr("MissErrorNumF"));
		modelManuResQuery->setHeaderData(5, Qt::Horizontal, tr("ExtraErrorNumB"));
		modelManuResQuery->setHeaderData(6, Qt::Horizontal, tr("MissErrorNumB"));
	}
}

void myMainWindow::resViewUpdate(QString viewID)
{
	curViewID = g_viewName_Reverse[viewID.toStdString()];
	if (!curOnePCBResManu.empty())
	{
		ui.imgShowWin->getReCheckRes(curOnePCBResManu);
		writeDatabaseTable_TXTFile(curOnePCBResManu);
		curCarrierRes.setOnePCBResManu(g_viewName_Reverse[viewID.toStdString()], curOnePCBResManu);

		curCarrierRes.getOnePCBResAuto(curViewID, curOnePCBResManu);
		ui.imgShowWin->loadOnePCBResInfo(curOnePCBResManu, ui.widthErrCon->currentText().toInt(), ui.viewFBSide->currentIndex());
	}
}

void myMainWindow::resViewSideUpdate(int viewSide)
{
	this->viewSide = viewSide;

	if (!curOnePCBResManu.empty())
	{
		ui.imgShowWin->loadOnePCBResInfo(curOnePCBResManu, ui.widthErrCon->currentText().toInt(), this->viewSide);
	}
}

void myMainWindow::refreshErrConWidth(QString indexCurText)
{
	int width = indexCurText.toInt();
	ui.imgShowWin->refreshPolyItemsDrawWidth(width);
}

/**
 * \brief to show if all the setting is done and the software is ready to accept the QRCode information
 */
void myMainWindow::showReadyMessage()
{
	if(isLogin && !resFileToMESPath.isEmpty() && !databaseManuName.isEmpty() && !databaseAutoName.isEmpty())
	{
		ui.onePCBID->setEnabled(true);
		ui.onePCBID->clear();
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
		ui.onePCBID->clear();
		ui.onePCBID->setEnabled(false);
		ui.statusBar->showMessage("Not ready for human rechecking.");
	}
}

QString myMainWindow::getHostIPAddress()
{
	QString strIPAddress;
	QList<QHostAddress> ipAddressList = QNetworkInterface::allAddresses();
	int nListSize = ipAddressList.size();

	for (int i = 0; i < nListSize; i++)
	{
		if (ipAddressList.at(i) != QHostAddress::LocalHost && ipAddressList.at(i).toIPv4Address())
		{
			strIPAddress = ipAddressList.at(i).toString();
			break;
		}
	}

	if (strIPAddress.isEmpty())
	{
		strIPAddress = QHostAddress(QHostAddress::LocalHost).toString();
	}

	return strIPAddress;

}

void myMainWindow::setComBox()
{
	disconnect(ui.viewIDComBox, SIGNAL(currentIndextChanged(QString)), this, SLOT(resViewUpdate(QString)));

	ui.viewIDComBox->clear();
	for(int i = 0; i < curCarrierRes.getCarrierResAuto().size(); i++)
	{
		ui.viewIDComBox->addItem(QString::fromStdString(g_viewName[g_Views[i]]));
	}

	ui.viewIDComBox->setCurrentIndex(0);
	curViewID = VIEW_11;
	curCarrierRes.getOnePCBResAuto(VIEW_11, curOnePCBResManu);
	ui.imgShowWin->loadOnePCBResInfo(curOnePCBResManu, ui.widthErrCon->currentText().toInt(), ui.viewFBSide->currentIndex());

	connect(ui.viewIDComBox, SIGNAL(currentIndextChanged(QString)), this, SLOT(resViewUpdate(QString)));
}

/**
 * \brief	get information from \auto result database with the \carrierID
 *			stroe the information of each PCB in the carrier to the curCarrierRes
 *			load the xml file and stroe the auto found error contours to each PCB
 *				stroe the		\PCBID, 
 *							\imgResFSide, 
 *							\imgResBSide, 
 *							\contourExtraF, 
 *							\contourMissF, 
 *							\contourExtraB, 
 *							\contourMissB,
 *							\extraErrorNum,
 *							\missErrorNum		of each PCB in the carrier
 * \param carrierId :the known carrier id
 * \param checkDate :the known carrier check date
 */
void myMainWindow::getCarrierResInfo(QString carrierId, QString checkDate)
{
	if (!dbOfAutoRes.isValid())
	{
		QString fileName = QFileDialog::getOpenFileName(this, tr("Load AutoCheck Result Database"), ".", tr("Databases (*.db)"));
		if (fileName.isEmpty())
		{
			return;
		}
		if (fileName.indexOf("userdata.db") != -1)
		{
			QMessageBox::warning(this, "Link Failed", "You have no access to this database.Please choose a SQLite3 database", QMessageBox::Abort);
			return;
		}

		dbOfAutoRes = QSqlDatabase::addDatabase("QSQLITE", "AUTO_RESULT_DB");
		dbOfAutoRes.setDatabaseName(fileName);

		if (!dbOfAutoRes.open())
		{
			QMessageBox::warning(this, "Link Failed", "Please choose a SQLite3 database", QMessageBox::Abort);
			return;
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
	query.exec("select * from checkRes where CarrierID = '" + carrierId + "'");

	std::string resImgPathBSide;

	onePCBResInfo curOnePCBRes;
	while (query.next())
	{
		QString viewId = query.value(2).toString();

		curOnePCBRes.pcbID = query.value(0).toString().toStdString();
		std::string resImgPath = query.value(10).toString().toStdString();
		std::string resImgPathFSide = resImgPath.substr(0, resImgPath.find_first_of('\n'));
		resImgPathBSide = resImgPath.substr(resImgPath.find_first_of('\n') + 1);
		curOnePCBRes.imgResFSide = cv::imread(resImgPathFSide);
		curOnePCBRes.imgResBSide = cv::imread(resImgPathBSide);

		curCarrierRes.setOnePCBResAuto(g_viewName_Reverse[viewId.toStdString()], curOnePCBRes);

		curOnePCBRes.clearInfo();
	}

	std::string errContourFilePath = resImgPathBSide.substr(0, resImgPathBSide.find_last_of('/') + 1) + "/" + carrierId.toStdString() + "_" + checkDate.toStdString() + ".xml";
	curCarrierRes.setErrContoursAuto(errContourFilePath);

	setComBox();
}

/**
 * \brief	get the \carrierID, \carrierCheckDate, \carrierCheckTime with the known one PCB id in the carrier from \auto results database
 * \param onePCBID :the known PCB id which is gotten from the QRCode scanner
 * \param carrierId :the to get \carrierID
 * \param checkDate :the to get \carrierDate
 * \param checkTime :the to get \carrierTime
 */
void myMainWindow::getCarrierID_Date(QString onePCBID, QString& carrierId, QString& checkDate)
{
	if (!dbOfAutoRes.isValid())
	{
		QString fileName = QFileDialog::getOpenFileName(this, tr("Load AutoCheck Result Database"), ".", tr("Databases (*.db)"));
		if (fileName.isEmpty())
		{
			return;
		}
		if (fileName.indexOf("userdata.db") != -1)
		{
			QMessageBox::warning(this, "Link Failed", "You have no access to this database.Please choose a SQLite3 database", QMessageBox::Abort);
			return;
		}

		dbOfAutoRes = QSqlDatabase::addDatabase("QSQLITE", "AUTO_RESULT_DB");
		dbOfAutoRes.setDatabaseName(fileName);

		if (!dbOfAutoRes.open())
		{
			QMessageBox::warning(this, "Link Failed", "Please choose a SQLite3 database", QMessageBox::Abort);
			return;
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
		carrierId = query.value(1).toString();
		checkDate = query.value(3).toString();
	}
}

void myMainWindow::writeDatabaseTable(QString str)
{
	if (!dbOfManuRes.isValid())
	{
		QString fileName = QFileDialog::getOpenFileName(this, tr("Load Manual ReCheckRes Database"), ".", tr("Databases (*.db)"));
		if (fileName.isEmpty())
		{
			return;
		}
		if (fileName.indexOf("userdata.db") != -1)
		{
			QMessageBox::warning(this, "Link Failed", "You have no access to this database.Please choose a SQLite3 database", QMessageBox::Abort);
			return;
		}

		dbOfManuRes = QSqlDatabase::addDatabase("QSQLITE", "RESULT_DB");
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
	}

	QSqlQuery query(dbOfManuRes);
	query.exec("create table reCheckRes (PCBID varchar(30) primary key, "
		"CarrierID varchar(30), REGIONID varchar(10), Date varchar(20), Time varchar(20), "
		"Result varchar(30), ExtraErrorNumF varchar(10), MissErrorNumF varchar(10), "
		"ExtraErrorNumB varchar(10), MissErrorNumB varchar(10), resImgPath varchar(100))");
	query.exec(tr("insert into reCheckRes values(%1)").arg(str));
}

void myMainWindow::saveErrContours(std::string filePath)
{
	std::string labels[4] = { "ExtraContours_FrontSide", "MissContours_FrontSide", "ExtraContours_BackSide", "MissContours_BackSide" };
	cv::FileStorage fs(filePath, cv::FileStorage::WRITE);

	fs << curOnePCBResManu.pcbID << "{";
	fs << labels[0] << curOnePCBResManu.contourExtraF;
	fs << labels[1] << curOnePCBResManu.contourMissF;
	fs << labels[2] << curOnePCBResManu.contourExtraB;
	fs << labels[3] << curOnePCBResManu.contourMissB;
	fs << "}";
}

void myMainWindow::writeDatabaseTable_TXTFile(onePCBResInfo onePCBResManu)
{
	std::string pcbID = onePCBResManu.pcbID;
	QDate curDate = QDate::currentDate();
	QTime curTime = QTime::currentTime();

	QString res;
	if(onePCBResManu.extraErrorNum == 0 && onePCBResManu.missErrorNum == 0)
	{
		if(onePCBResManu.isModified)
		{
			res = "PS";
		}
		else
		{
			res = "OK";
		}
	}
	else
	{
		res = "NG";
	}

	////create the txt file to MES
	QString txtFilePathtoMES = resFileToMESPath + "/" + QString::fromStdString(pcbID) + "_" + curDate.toString("yyyy-MM-dd") + "_" + curTime.toString("hh-mm-ss") + "_" + res + ".txt";

	QFile txtFile(txtFilePathtoMES);
	if (txtFile.open(QFile::WriteOnly | QIODevice::Truncate))
	{
		QTextStream out(&txtFile);
		out << QString::fromStdString(pcbID) << endl;
		out << carrierID.mid(0, 9) << endl;
		out << curDate.toString("yyyy-MM-dd") << endl;
		out << curTime.toString("hh-mm-ss") << endl;
		out << userName << endl;
		out << ipAddress << endl;
		out << res << endl;
	}

	//save the recheck result images and related .xml file to the same file path of the auto check result files
	QString fileUpdate_OriginPath = resFileToGetPath + "/" + carrierID.mid(0, 9)
		+ "/" + curDate.toString("yyyy-MM-dd")
		+ "/" + QString::fromStdString(pcbID) + "_" + curDate.toString("yyyy-MM-dd")
		+ "_" + curTime.toString("hh-mm-ss") + "_" + res;

	//write information to recheck database
	QString str = "'" + QString::fromStdString(pcbID)
		+ "', '" + carrierID + "', '" + QString::fromStdString(g_viewName[curViewID])
		+ "', '" + curDate.toString("yyyy-MM-dd")
		+ "', '" + curTime.toString("hh-mm-ss")
		+ "', '" + res
		+ "', '" + QString::number(onePCBResManu.contourExtraF.size(), 10)
		+ "', '" + QString::number(onePCBResManu.contourMissF.size(), 10)
		+ "', '" + QString::number(onePCBResManu.contourExtraB.size(), 10)
		+ "', '" + QString::number(onePCBResManu.contourMissB.size(), 10)
		+ "', '" + fileUpdate_OriginPath + "_fside_recheck.jpg\n"
				+ fileUpdate_OriginPath + "_bside_recheck.jpg'";

	writeDatabaseTable(str);

	//save result images(.jpg) and contours information(.xml)
	cv::imwrite(fileUpdate_OriginPath.toStdString() + "_fside_recheck.jpg", onePCBResManu.imgResFSide);
	cv::imwrite(fileUpdate_OriginPath.toStdString() + "_bside_recheck.jpg", onePCBResManu.imgResBSide);

	QString xmlFilePath = resFileToGetPath + "/" + carrierID.mid(0, 9) + "/" + curDate.toString("yyyy-MM-dd")
		+ "/" + carrierID + "_" + curDate.toString("yyyy-MM-dd") + "_recheck.xml";
	saveErrContours(xmlFilePath.toStdString());
}

void myMainWindow::closeEvent(QCloseEvent* event)
{
}

