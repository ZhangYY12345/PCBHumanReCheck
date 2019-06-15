#include "mymainwindow.h"
#include "parameters.h"
#include "methods.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QFileDialog>
#include <QNetworkInterface>
#include <qobjectdefs.h>
#include <qcompilerdetection.h>
#include <direct.h>
#include <experimental/filesystem>

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
	connectComIP = "";

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

	connect(ui.viewIDComBox, SIGNAL(currentIndexChanged(int)), this, SLOT(resViewUpdate(int)));

	connect(ui.carrierAutoResTableView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(updateView_db_auto(const QModelIndex&)));
	connect(ui.carrierManuResTableView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(updateView_db_manu(const QModelIndex&)));

	connect(ui.imgShowWin, SIGNAL(reschanged()), this, SLOT(onePCBUpdate()));

	connect(ui.revokeBt, SIGNAL(clicked()), this, SLOT(revokeAllChanges()));
	connect(ui.saveBt, SIGNAL(clicked()), this, SLOT(saveAllChanges()));

	connect(ui.toConnectIP, SIGNAL(editingFinished()), this, SLOT(getToConnectIP()));

	connect(this, SIGNAL(readyCheck()), this, SLOT(showReadyMessage()));

	ui.onePCBID->setEnabled(false);

	ipAddress = getHostIPAddress();
}

myMainWindow::~myMainWindow()
{
}

void myMainWindow::toLog()
{
	if(isLogin)
	{
		int r = QMessageBox::question(this, QString::fromLocal8Bit("退出登录"), 
			QString::fromLocal8Bit("您将退出当前登录，是否确认退出登录？"), 
			QMessageBox::Yes, QMessageBox::No);
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
	checkDataDBManu();

	QSqlQuery query(dbOfManuRes);
	query.exec("create table reCheckRes (PCBID varchar(30) primary key, "
		"CarrierID varchar(30), REGIONID varchar(10), Date varchar(20), Time varchar(20), "
		"Result varchar(30), ExtraErrorNumF varchar(10), MissErrorNumF varchar(10), "
		"ExtraErrorNumB varchar(10), MissErrorNumB varchar(10), resImgPath varchar(100))");

	if (databaseView != Q_NULLPTR)
	{
		databaseView->closeDatabaseTable();
		delete databaseView;
		databaseView = Q_NULLPTR;
	}

	databaseView = new myDatabaseTable(dbOfManuRes);
	databaseView->show();

	return 0;
}

void myMainWindow::showSettingWin()
{
	settingWindow = new mySettingWindow(connectComIP, databaseAutoName, databaseManuName, resFileToGetPath, resFileToMESPath, OKModel);
	connect(settingWindow, SIGNAL(newComIP(QString)), this, SLOT(updateComIP(QString)));
	connect(settingWindow, SIGNAL(newDatabaseAutoName(QString)), this, SLOT(updateDatabaseAutoFile(QString)));
	connect(settingWindow, SIGNAL(newDatabaseManuName(QString)), this, SLOT(updateDatabaseManuFile(QString)));
	connect(settingWindow, SIGNAL(newResFileToGetPath(QString)), this, SLOT(updateResFileToGetPath(QString)));
	connect(settingWindow, SIGNAL(newResFileToMESPath(QString)), this, SLOT(updateResFileToMESPath(QString)));
	connect(settingWindow, SIGNAL(newOKModel(bool)), this, SLOT(updateOKModel(bool)));
	settingWindow->show();
}

void myMainWindow::newDatabase()
{
	QString fileName = QFileDialog::getSaveFileName(this, 
		QString::fromLocal8Bit("创建新的人工复检数据库"), ".", 
		QString::fromLocal8Bit("数据库") + tr(" (*.db)"));

	if (fileName.isEmpty())
	{
		return;
	}
	if (fileName.indexOf("userdata.db") != -1)
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("文件打开失败"), 
			QString::fromLocal8Bit("您没有打开所选文件的权限，请重新选择数据库文件。"), 
			QMessageBox::Abort);
		return;
	}

	if (!dbOfManuRes.isValid())
	{
		dbOfManuRes = QSqlDatabase::addDatabase("QSQLITE", "MANU_RESULT_DB");
	}

	dbOfManuRes.setDatabaseName(fileName);

	if (!dbOfManuRes.open())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("文件打开失败"), 
			QString::fromLocal8Bit("请重新选择数据库文件。"), QMessageBox::Abort);
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
	QString fileName = QFileDialog::getOpenFileName(this, 
		QString::fromLocal8Bit("加载自动检测结果数据库"), ".", 
		QString::fromLocal8Bit("数据库") + tr(" (*.db)"));
	if (fileName.isEmpty())
	{
		return;
	}
	if (fileName.indexOf("userdata.db") != -1)
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("文件打开失败"), 
			QString::fromLocal8Bit("您没有打开所选文件的权限，请重新选择数据库文件。"), 
			QMessageBox::Abort);
		return;
	}

	if (!dbOfAutoRes.isValid())
	{
		dbOfAutoRes = QSqlDatabase::addDatabase("QSQLITE", "AUTO_RESULT_DB");
	}

	dbOfAutoRes.setDatabaseName(fileName);

	if (!dbOfAutoRes.open())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("文件打开失败"),
			QString::fromLocal8Bit("请重新选择数据库文件。"), QMessageBox::Abort);
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
	QString fileName = QFileDialog::getOpenFileName(this, 
		QString::fromLocal8Bit("加载人工复检数据库"), ".", 
		QString::fromLocal8Bit("数据库") + tr(" (*.db)"));
	if (fileName.isEmpty())
	{
		return;
	}
	if (fileName.indexOf("userdata.db") != -1)
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("文件打开失败"), 
			QString::fromLocal8Bit("您没有打开所选文件的权限，请重新选择数据库文件。"), QMessageBox::Abort);
		return;
	}

	if (!dbOfManuRes.isValid())
	{
		dbOfManuRes = QSqlDatabase::addDatabase("QSQLITE", "MANU_RESULT_DB");
	}

	dbOfManuRes.setDatabaseName(fileName);

	if (!dbOfManuRes.open())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("文件打开失败"), 
			QString::fromLocal8Bit("请重新选择数据库文件。"), QMessageBox::Abort);
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
	resFileToGetPath = changePathDirt(resFileToGetPath);
	if (settingWindow != Q_NULLPTR)
	{
		settingWindow->updateResFileToGetPath(resFileToGetPath);
	}
	emit readyCheck();
}

void myMainWindow::setResFileToMESPath()
{
	resFileToMESPath = QFileDialog::getExistingDirectory(this);
	resFileToMESPath = changePathDirt(resFileToMESPath);

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

void myMainWindow::updateComIP(QString comIP)
{
	if(ipCheck(comIP))
	{
		connectComIP = comIP;
		ui.toConnectIP->setText(connectComIP);
		int a = ui.toConnectIP->cursorMoveStyle();
		ui.toConnectIP->setCursorMoveStyle(Qt::VisualMoveStyle);
		emit readyCheck();
	}
}

void myMainWindow::updateDatabaseAutoFile(QString fileName)
{
	if (fileName.isEmpty())
	{
		return;
	}
	if (fileName.indexOf("userdata.db") != -1)
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("文件打开失败"), 
			QString::fromLocal8Bit("您没有打开所选文件的权限，请重新选择数据库文件。"), QMessageBox::Abort);
		return;
	}

	if (!dbOfAutoRes.isValid())
	{
		dbOfAutoRes = QSqlDatabase::addDatabase("QSQLITE", "AUTO_RESULT_DB");
	}

	dbOfAutoRes.setDatabaseName(fileName);

	if (!dbOfAutoRes.open())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("文件打开失败"), 
			QString::fromLocal8Bit("请重新选择数据库文件。"), QMessageBox::Abort);
		return;
	}

	databaseAutoName = fileName;

	if (modelAutoResQuery != Q_NULLPTR)
	{
		delete modelAutoResQuery;
		modelAutoResQuery = Q_NULLPTR;
	}

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
		QMessageBox::warning(this, QString::fromLocal8Bit("文件打开失败"), 
			QString::fromLocal8Bit("您没有打开所选文件的权限，请重新选择数据库文件。"), QMessageBox::Abort);
		return;
	}

	if (!dbOfManuRes.isValid())
	{
		dbOfManuRes = QSqlDatabase::addDatabase("QSQLITE", "MANU_RESULT_DB");
	}

	dbOfManuRes.setDatabaseName(fileName);

	if (!dbOfManuRes.open())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("文件打开失败"), 
			QString::fromLocal8Bit("请重新选择数据库文件。"), QMessageBox::Abort);
		return;
	}
	databaseManuName = fileName;

	if (modelManuResQuery != Q_NULLPTR)
	{
		delete modelManuResQuery;
		modelManuResQuery = Q_NULLPTR;
	}

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
	ui.onePCBID->clear();
	showAutoCarrierInfo(onePCBId);
}

void myMainWindow::showAutoCarrierInfo(QString onePCBId)
{
	QString carrierID;
	QString carrierCheckDate;

	bool isInManu;
	getCarrierID_Date(onePCBId, carrierID, carrierCheckDate);
	getCarrierResInfo(carrierID, carrierCheckDate);

	this->carrierID = carrierID;

	checkDataDBAuto();
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

		ui.carrierAutoResTableView->setModel(modelAutoResQuery);
	}

	//
	std::vector<REGION_IN_CARRIER> recheckedViewID;
	std::string resImgPathBSide;
	onePCBResInfo curOnePCBRes;
	QString recheckDate;

	checkDataDBManu();
	QSqlQuery query_(dbOfManuRes);
	query_.exec("create table reCheckRes (PCBID varchar(30) primary key, "
		"CarrierID varchar(30), REGIONID varchar(10), Date varchar(20), Time varchar(20), "
		"Result varchar(30), ExtraErrorNumF varchar(10), MissErrorNumF varchar(10), "
		"ExtraErrorNumB varchar(10), MissErrorNumB varchar(10), resImgPath varchar(100))");
	query_.exec("select * from reCheckRes where CarrierID = '" + carrierID + "'");

	while (query_.next())
	{
		QString viewId = query_.value(2).toString();
		recheckDate = query_.value(3).toString();

		curOnePCBRes.pcbID = query_.value(0).toString().toStdString();
		std::string resImgPath = query_.value(10).toString().toStdString();
		std::string resImgPathFSide = resImgPath.substr(0, resImgPath.find_first_of(';'));
		resImgPathBSide = resImgPath.substr(resImgPath.find_first_of(';') + 1);
		QString viewID_F = viewId.mid(viewId.indexOf("VIEW"), 7);
		REGION_IN_CARRIER viewID__ = g_viewName_Reverse[viewID_F.toStdString()];

		std::string recheckXMLPath = resImgPathBSide.substr(0, resImgPathBSide.find_last_of('\\') + 1) 
		+ query_.value(1).toString().toStdString() + "_" + recheckDate.toStdString() + "_recheck.xml";
		if (std::experimental::filesystem::exists(recheckXMLPath))
		{
			if (!setOnePCBErrCtrs(viewID__, curOnePCBRes, recheckXMLPath))
			{
				break;
			}
		}

		curOnePCBRes.imgResFSide = cv::imread(transDBPath(resImgPathFSide));
		curOnePCBRes.imgResBSide = cv::imread(transDBPath(resImgPathBSide));
		if(curOnePCBRes.imgResFSide.empty() || curOnePCBRes.imgResBSide.empty())
		{
			continue;
		}

		if (curOnePCBRes == curCarrierRes.getOnePCBResManu(viewID__))
		{
			curOnePCBRes.clearInfo();
			continue;
		}

		curOnePCBRes.isModified = true;
		curCarrierRes.setOnePCBResManu(viewID__, curOnePCBRes);
		recheckedViewID.push_back(viewID__);
		curOnePCBRes.clearInfo();
	}

	if (!recheckedViewID.empty())
	{
		QString xmlFilePath = resFileToGetPath
			+ "\\" + recheckDate
			+ "\\" + carrierID.mid(0, 9)
			+ "\\" + carrierID + "-" + recheckDate
			+ "_recheck.xml";
		curCarrierRes.setErrContoursManu(recheckedViewID, xmlFilePath.toStdString());
	}

	setComBox();

}

void myMainWindow::showManuCarrierInfo()
{
	checkDataDBManu();
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
		//modelManuResQuery->setHeaderData(0, Qt::Horizontal, tr("PCBID"));
		//modelManuResQuery->setHeaderData(1, Qt::Horizontal, tr("RegionID"));
		//modelManuResQuery->setHeaderData(2, Qt::Horizontal, tr("Result"));
		//modelManuResQuery->setHeaderData(3, Qt::Horizontal, tr("ExtraErrorNumF"));
		//modelManuResQuery->setHeaderData(4, Qt::Horizontal, tr("MissErrorNumF"));
		//modelManuResQuery->setHeaderData(5, Qt::Horizontal, tr("ExtraErrorNumB"));
		//modelManuResQuery->setHeaderData(6, Qt::Horizontal, tr("MissErrorNumB"));

		//ui.carrierManuResTableView->setModel(modelManuResQuery);
	}
}

void myMainWindow::resViewUpdate(int)
{
	if (!curOnePCBResManu.empty())
	{
		ui.imgShowWin->getReCheckRes(curOnePCBResManu);
		curCarrierRes.setOnePCBResManu(curViewID, curOnePCBResManu);
		writeDatabaseTable_TXTFile(curOnePCBResManu);
	}

	curViewID = g_viewName_Reverse[ui.viewIDComBox->currentText().toStdString()];
	if (curCarrierRes.isRechecked(curViewID))
	{
		curCarrierRes.getOnePCBResManu(curViewID, curOnePCBResManu);
		ui.imgShowWin->loadOnePCBResInfo(curOnePCBResManu, ui.widthErrCon->currentText().toInt());
	}
	else
	{
		curCarrierRes.getOnePCBResAuto(curViewID, curOnePCBResManu);
		ui.imgShowWin->loadOnePCBResInfo(curOnePCBResManu, ui.widthErrCon->currentText().toInt());
	}
}

void myMainWindow::updateView_db_auto(const QModelIndex& index)
{
	int curCol = index.column();
	QVariant data_ = modelAutoResQuery->data(index);
	if (curCol == 0)
	{
		checkDataDBAuto();

		QSqlQuery query(dbOfAutoRes);
		query.exec("create table checkRes (PCBID varchar(30) primary key, "
			"CarrierID varchar(30), REGIONID varchar(10), Date varchar(20), Time varchar(20), "
			"Result varchar(30), ExtraErrorNumF varchar(10), MissErrorNumF varchar(10), "
			"ExtraErrorNumB varchar(10), MissErrorNumB varchar(10), resImgPath varchar(100))");
		query.exec("select * from checkRes where PCBID = '" + data_.toString() + "'");

		while (query.next())
		{
			QString viewId = query.value(2).toString();
			QString viewID_F = viewId.mid(viewId.indexOf("VIEW"), 7);
			ui.viewIDComBox->setCurrentText(viewID_F);
		}
	}
}

void myMainWindow::updateView_db_manu(const QModelIndex& index)
{
	int curCol = index.column();
	QVariant data_ = modelManuResQuery->data(index);
	if (curCol == 0)
	{
		checkDataDBManu();

		QSqlQuery query(dbOfManuRes);
		query.exec("create table reCheckRes (PCBID varchar(30) primary key, "
			"CarrierID varchar(30), REGIONID varchar(10), Date varchar(20), Time varchar(20), "
			"Result varchar(30), ExtraErrorNumF varchar(10), MissErrorNumF varchar(10), "
			"ExtraErrorNumB varchar(10), MissErrorNumB varchar(10), resImgPath varchar(100))");
		query.exec("select * from reCheckRes where PCBID = '" + data_.toString() + "'");

		while (query.next())
		{
			QString viewId = query.value(2).toString();
			QString viewID_F = viewId.mid(viewId.indexOf("VIEW"), 7);
			ui.viewIDComBox->setCurrentText(viewID_F);
		}
	}
}

void myMainWindow::onePCBUpdate()
{
	if (!curOnePCBResManu.empty())
	{
		ui.imgShowWin->getReCheckRes(curOnePCBResManu);
	}
}

void myMainWindow::revokeAllChanges()
{
	if (!curOnePCBResManu.empty())
	{
		curOnePCBResManu.clearInfo();
		curCarrierRes.getOnePCBResAuto(curViewID, curOnePCBResManu);
		curCarrierRes.revokeManuChanged(curViewID);
		ui.imgShowWin->loadOnePCBResInfo(curOnePCBResManu, ui.widthErrCon->currentText().toInt());
	}
}

void myMainWindow::saveAllChanges()
{
	if (!curOnePCBResManu.empty())
	{
		ui.imgShowWin->getReCheckRes(curOnePCBResManu);
		curCarrierRes.setOnePCBResManu(curViewID, curOnePCBResManu);
		writeDatabaseTable_TXTFile(curOnePCBResManu);
	}
}

void myMainWindow::refreshErrConWidth(QString indexCurText)
{
	int width = indexCurText.toInt();
	ui.imgShowWin->refreshPolyItemsDrawWidth(width);
}

void myMainWindow::getToConnectIP()
{
	QString comIP = ui.toConnectIP->text();
	if (ipCheck(comIP))
	{
		connectComIP = comIP;
		if (settingWindow != Q_NULLPTR)
		{
			settingWindow->updateComIP(connectComIP);
		}

		emit readyCheck();
	}
}

/**
 * \brief to show if all the setting is done and the software is ready to accept the QRCode information
 */
void myMainWindow::showReadyMessage()
{
	if(isLogin && !resFileToMESPath.isEmpty() && !databaseManuName.isEmpty() 
		&& !databaseAutoName.isEmpty() && !connectComIP.isEmpty())
	{
		ui.onePCBID->setEnabled(true);
		ui.onePCBID->clear();
		if(OKModel)
		{
			ui.statusBar->showMessage(QString::fromLocal8Bit("准备好进行人工复检。自动检测为合格的产品不进行复检。请把鼠标光标放在onePCBID栏，扫描输入PCB二维码ID。"));
		}
		else
		{
			ui.statusBar->showMessage(QString::fromLocal8Bit("准备好进行人工复检。自动检测为合格的产品也进行复检。请把鼠标光标放在onePCBID栏，扫描输入PCB二维码ID。"));
		}
	}
	else
	{
		ui.onePCBID->clear();
		ui.onePCBID->setEnabled(false);
		ui.statusBar->showMessage(QString::fromLocal8Bit("未准备好进行人工复检，请检查登录状态，设置与MES的通信路径，通信计算机IP，并设置存储和读取数据库文件。"));
	}
}

/**
 * \brief 获取第一个本主机的IPv4地址
 * \return 
 */
QString myMainWindow::getHostIPAddress()
{
	QString strIPAddress;
	QList<QHostAddress> ipAddressList = QNetworkInterface::allAddresses();
	int nListSize = ipAddressList.size();

	for (int i = 0; i < nListSize; i++)
	{
		if (ipAddressList.at(i) != QHostAddress::LocalHost 
			&& ipAddressList.at(i).toIPv4Address())
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

/**
 * \brief 获取本主机的所有IPv4地址
 * \return 
 */
std::vector<QString> myMainWindow::getHostIPAddresses()
{
	std::vector<QString> strIPAddress;
	QList<QHostAddress> ipAddressList = QNetworkInterface::allAddresses();
	int nListSize = ipAddressList.size();

	for (int i = 0; i < nListSize; i++)
	{
		if (ipAddressList.at(i) != QHostAddress::LocalHost
			&& ipAddressList.at(i).toIPv4Address())
		{
			strIPAddress.push_back(ipAddressList.at(i).toString());
		}
	}

	return strIPAddress;
}

bool myMainWindow::ipCheck(QString comIP)
{
	QStringList comIP_split;
	comIP_split = comIP.split('.');
	if (comIP_split.size() == 4)
	{
		for (int i = 0; i < 4; i++)
		{
			int num = comIP_split[i].toInt();
			if (num < 0 || num > 255)
				return false;
		}
	}
	else
	{
		return false;
	}
	return true;
}

bool myMainWindow::isIPInner(QString comIP)
{
	std::vector<QString> ipList;
	ipList = getHostIPAddresses();
	for(int i = 0; i < ipList.size(); i++)
	{
		if (comIP.remove(QRegExp("\\s")) == ipList[i].remove(QRegExp("\\s")))
			return true;
	}
	return false;
}

QString myMainWindow::transDBPath(QString imgPath)
{
	QString transedPath = "";
	if(!connectComIP.isEmpty())
	{
		QStringList comPan_;
		comPan_ = imgPath.split(':');

		transedPath = "\\" + connectComIP + '\\' + comPan_[0].toLower() + comPan_[1];
	}
	return transedPath;
}

std::string myMainWindow::transDBPath(std::string imgPath)
{
	std::string transedPath = "";
	if (!connectComIP.isEmpty() && !isIPInner(connectComIP))
	{
		std::vector<std::string> comPan_;
		comPan_ = split(imgPath, ':');

		//char lowerPanName = std::tolower(comPan_[0].at(0));

		transedPath = "\\\\" + connectComIP.toStdString() + '\\' + comPan_[0] + comPan_[1];
	}
	else if(isIPInner(connectComIP))
	{
		transedPath = imgPath;
	}

	if(transedPath.empty())
	{
		transedPath = imgPath;
	}

	return transedPath;
}

void myMainWindow::checkDataDBAuto()
{
	if (!dbOfAutoRes.isValid())
	{
		QString fileName = QFileDialog::getOpenFileName(this,
			QString::fromLocal8Bit("加载自动检测结果数据库"), ".",
			QString::fromLocal8Bit("数据库") + tr(" (*.db)"));
		if (fileName.isEmpty())
		{
			return;
		}
		if (fileName.indexOf("userdata.db") != -1)
		{
			QMessageBox::warning(this, QString::fromLocal8Bit("文件打开失败"),
				QString::fromLocal8Bit("您没有打开所选文件的权限，请重新选择数据库文件。"),
				QMessageBox::Abort);
			return;
		}

		dbOfAutoRes = QSqlDatabase::addDatabase("QSQLITE", "AUTO_RESULT_DB");
		dbOfAutoRes.setDatabaseName(fileName);

		if (!dbOfAutoRes.open())
		{
			QMessageBox::warning(this, QString::fromLocal8Bit("文件打开失败"),
				QString::fromLocal8Bit("请重新选择数据库文件。"), QMessageBox::Abort);
			return;
		}

		databaseAutoName = fileName;
		if (settingWindow != Q_NULLPTR)
		{
			settingWindow->updateDatabaseAutoFile(fileName);
		}
		emit readyCheck();
	}
}

void myMainWindow::checkDataDBManu()
{
	if (!dbOfManuRes.isValid())
	{
		QString fileName = QFileDialog::getOpenFileName(this,
			QString::fromLocal8Bit("加载人工复检数据库"), ".",
			QString::fromLocal8Bit("数据库") + tr(" (*.db)"));
		if (fileName.isEmpty())
		{
			return;
		}
		if (fileName.indexOf("userdata.db") != -1)
		{
			QMessageBox::warning(this, QString::fromLocal8Bit("文件打开失败"),
				QString::fromLocal8Bit("您没有打开所选文件的权限，请重新选择数据库文件。"),
				QMessageBox::Abort);
			return;
		}

		dbOfManuRes = QSqlDatabase::addDatabase("QSQLITE", "MANU_RESULT_DB");
		dbOfManuRes.setDatabaseName(fileName);

		if (!dbOfManuRes.open())
		{
			QMessageBox::warning(this, QString::fromLocal8Bit("文件打开失败"),
				QString::fromLocal8Bit("请重新选择数据库文件。"), QMessageBox::Abort);
			return;
		}
		databaseManuName = fileName;
		if (settingWindow != Q_NULLPTR)
		{
			settingWindow->updateDatabaseManuFile(fileName);
		}
		emit readyCheck();
	}
}

bool myMainWindow::setOnePCBErrCtrs(REGION_IN_CARRIER viewId, onePCBResInfo& onePCB, std::string filePathXML)
{
	std::string labels[4] = { "ExtraContours_FrontSide", "MissContours_FrontSide", "ExtraContours_BackSide", "MissContours_BackSide" };

	if (!isXmlEmpty(filePathXML))
	{
		cv::FileStorage fs(filePathXML, cv::FileStorage::READ);
		if (fs.isOpened())
		{
			std::string upperLabel = g_viewName[viewId];
			cv::FileNode fn = fs[upperLabel];

			if (fn.isNone())
				return false;

			fn[labels[0]] >> onePCB.contourExtraF;
			fn[labels[1]] >> onePCB.contourMissF;
			fn[labels[2]] >> onePCB.contourExtraB;
			fn[labels[3]] >> onePCB.contourMissB;

			onePCB.extraErrorNum = onePCB.contourExtraF.size()
				+ onePCB.contourExtraB.size();
			onePCB.missErrorNum = onePCB.contourMissF.size()
				+ onePCB.contourMissB.size();
		}
		else
		{
			return false;
		}
		fs.release();
		return true;
	}
	return false;
}

bool myMainWindow::isXmlEmpty(std::string filePathXML)
{
	QFile file_(QString::fromStdString(filePathXML));
	if(file_.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QXmlStreamReader xmlReader(&file_);
		xmlReader.readNext();
		if (xmlReader.atEnd())
		{
			file_.close();
			return true;
		}
		return false;
	}
	return false;
}

void myMainWindow::setComBox()
{
	if (curCarrierRes.getCarrierResAuto().size() == 1 ||
		curCarrierRes.getCarrierResAuto().size() == 4 ||
		curCarrierRes.getCarrierResAuto().size() == 6 ||
		curCarrierRes.getCarrierResAuto().size() == 8)
	{
		disconnect(ui.viewIDComBox, SIGNAL(currentIndexChanged(int)), this, SLOT(resViewUpdate(int)));

		ui.viewIDComBox->clear();
		for (int i = 0; i < curCarrierRes.getCarrierResAuto().size(); i++)
		{
			ui.viewIDComBox->addItem(QString::fromStdString(g_viewName[g_Views[i]]));
		}

		ui.viewIDComBox->setCurrentIndex(0);
		curViewID = VIEW_11;
		curCarrierRes.getOnePCBResAuto(VIEW_11, curOnePCBResManu);
		ui.imgShowWin->loadOnePCBResInfo(curOnePCBResManu, ui.widthErrCon->currentText().toInt());

		connect(ui.viewIDComBox, SIGNAL(currentIndexChanged(int)), this, SLOT(resViewUpdate(int)));
	}
	else
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("失败"),
			QString::fromLocal8Bit("当前PCB所在载具检测结果不完整，请重新检测"),
			QMessageBox::Abort);
	}
}

/**
 * \brief	get information from \auto result database with the \carrierID
 *			store the information of each PCB in the carrier to the \curCarrierRes
 *			load the xml file and store the auto found error contours to each PCB
 *				store the		\PCBID, 
 *								\imgResFSide, 
 *								\imgResBSide, 
 *								\contourExtraF, 
 *								\contourMissF, 
 *								\contourExtraB, 
 *								\contourMissB,
 *								\extraErrorNum,
 *								\missErrorNum		of each PCB in the carrier
 * \param carrierId :the known carrier id
 * \param checkDate :the known carrier check date
 */
void myMainWindow::getCarrierResInfo(QString carrierId, QString checkDate)
{
	checkDataDBAuto();
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
		std::string resImgPathFSide = resImgPath.substr(0, resImgPath.find_first_of(';'));
		resImgPathBSide = resImgPath.substr(resImgPath.find_first_of(';') + 1);
		curOnePCBRes.imgResFSide = cv::imread(transDBPath(resImgPathFSide));
		curOnePCBRes.imgResBSide = cv::imread(transDBPath(resImgPathBSide));

		QString viewID_F = viewId.mid(viewId.indexOf("VIEW"), 7);
		curCarrierRes.setOnePCBResAuto(g_viewName_Reverse[viewID_F.toStdString()], curOnePCBRes);

		curOnePCBRes.clearInfo();
	}

	std::string errContourFilePath_auto = resImgPathBSide.substr(0, resImgPathBSide.find_last_of('\\') + 1)
			+ carrierId.toStdString() + "-" + checkDate.toStdString() + ".xml";
	curCarrierRes.setErrContoursAuto(transDBPath(errContourFilePath_auto));
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
	checkDataDBAuto();

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
	checkDataDBManu();

	QSqlQuery query(dbOfManuRes);
	query.exec("create table reCheckRes (PCBID varchar(30) primary key, "
		"CarrierID varchar(30), REGIONID varchar(10), Date varchar(20), Time varchar(20), "
		"Result varchar(30), ExtraErrorNumF varchar(10), MissErrorNumF varchar(10), "
		"ExtraErrorNumB varchar(10), MissErrorNumB varchar(10), resImgPath varchar(100))");
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
	QString txtFilePathtoMES = resFileToMESPath + "/" + QString::fromStdString(pcbID) + "-" + curDate.toString("yyyyMMdd") + "-" + curTime.toString("hhmmss") + "-" + res + ".txt";

	QFile txtFile(txtFilePathtoMES);
	if (txtFile.open(QFile::WriteOnly | QIODevice::Truncate))
	{
		QTextStream out(&txtFile);
		out << QString::fromStdString(pcbID) << endl;
		out << carrierID.mid(0, 9) << endl;
		out << curDate.toString("yyyyMMdd") << endl;
		out << curTime.toString("hhmmss") << endl;
		out << userName << endl;
		out << ipAddress << endl;
		out << res << endl;
	}

	//save the recheck result images and related .xml file to the same file path of the auto check result files

	system(("md " + std::string(resFileToGetPath.toLocal8Bit())
		+ "\\" + curDate.toString("yyyyMMdd").toStdString()
		+ "\\" + carrierID.mid(0, 9).toStdString()).c_str());

	QString fileUpdate_OriginPath = resFileToGetPath 
		+ "\\" + curDate.toString("yyyyMMdd")
		+ "\\" + carrierID.mid(0, 9)
		+ "\\" + QString::fromStdString(pcbID) + "-" + curDate.toString("yyyyMMdd")
		+ "-" + curTime.toString("hhmmss") + "-" + res;

	//write information to recheck database
	QString str = "'" + QString::fromStdString(pcbID)
		+ "', '" + carrierID + "', '" + QString::fromStdString(g_viewName[curViewID])
		+ "', '" + curDate.toString("yyyyMMdd")
		+ "', '" + curTime.toString("hhmmss")
		+ "', '" + res
		+ "', '" + QString::number(onePCBResManu.contourExtraF.size(), 10)
		+ "', '" + QString::number(onePCBResManu.contourMissF.size(), 10)
		+ "', '" + QString::number(onePCBResManu.contourExtraB.size(), 10)
		+ "', '" + QString::number(onePCBResManu.contourMissB.size(), 10)
		+ "', '" + fileUpdate_OriginPath + "_A_recheck.jpg;"
				+ fileUpdate_OriginPath + "_B_recheck.jpg'";

	checkDataDBManu();
	QSqlQuery query(dbOfManuRes);
	query.exec("create table reCheckRes (PCBID varchar(30) primary key, "
		"CarrierID varchar(30), REGIONID varchar(10), Date varchar(20), Time varchar(20), "
		"Result varchar(30), ExtraErrorNumF varchar(10), MissErrorNumF varchar(10), "
		"ExtraErrorNumB varchar(10), MissErrorNumB varchar(10), resImgPath varchar(100))");
	query.exec("delete from reCheckRes where PCBID = '" + QString::fromStdString(pcbID) + "'");
	query.exec(tr("insert into reCheckRes values(%1)").arg(str));
	showManuCarrierInfo();

	//save result images(.jpg) and contours information(.xml)
	cv::imwrite(std::string(fileUpdate_OriginPath.toLocal8Bit()) + "_A_recheck.jpg", onePCBResManu.imgResFSide);
	cv::imwrite(std::string(fileUpdate_OriginPath.toLocal8Bit()) + "_B_recheck.jpg", onePCBResManu.imgResBSide);

	QString xmlFilePath = resFileToGetPath 
	    + "\\" + curDate.toString("yyyyMMdd")
		+ "\\" + carrierID.mid(0, 9) 
		+ "\\" + carrierID + "_" + curDate.toString("yyyyMMdd") + "_recheck.xml";
	curCarrierRes.saveManuErrContr(std::string(xmlFilePath.toLocal8Bit()));
}

void myMainWindow::closeEvent(QCloseEvent* event)
{
	if(loginWin != Q_NULLPTR)
	{
		loginWin->winClose();
		delete loginWin;
		loginWin = Q_NULLPTR;
	}

	if (databaseView != Q_NULLPTR)
	{
		databaseView->closeDatabaseTable();
		delete databaseView;
		databaseView = Q_NULLPTR;
	}

	if(modelAutoResQuery != Q_NULLPTR)
	{
		delete modelAutoResQuery;
		modelAutoResQuery = Q_NULLPTR;
	}

	if (modelManuResQuery != Q_NULLPTR)
	{
		delete modelManuResQuery;
		modelManuResQuery = Q_NULLPTR;
	}
}

