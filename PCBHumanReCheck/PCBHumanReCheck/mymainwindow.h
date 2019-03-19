#pragma once

#include <QMainWindow>
#include "ui_mymainwindow.h"
#include "tologin.h"
#include "mysettingwindow.h"
#include "mydatabasetable.h"
#include "parameters.h"

class myMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	myMainWindow(QWidget *parent = Q_NULLPTR);
	~myMainWindow();


	signals:
	void readyCheck();

	private slots:
	void toLog();
	void beLogged(QString nameUser);
	int showDatabaseTable();	//only can show the database for human rechecking
	void showSettingWin();

	void newDatabase();		//only can create a new database for human rechecking
	void setDatabaseAuto();
	void setDatabaseManu();

	void setResFileToGetPath();
	void setResFileToMESPath();
	void setTransferModelAuto();
	void setTransferModelNotAuto();

	void updateDatabaseAutoFile(QString);
	void updateDatabaseManuFile(QString);

	void updateResFileToGetPath(QString);
	void updateResFileToMESPath(QString);
	void updateOKModel(bool);

	void showAutoCarrierInfo();
	void showManuCarrierInfo();

	void resViewUpdate(const QString& viewID);
	void resViewSideUpdate(int);

	void refreshErrConWidth(QString);

	void showReadyMessage();

private:
	Ui::myMainWindow ui;

	toLogin* loginWin = Q_NULLPTR;
	QString userName;

	myDatabaseTable* databaseView = Q_NULLPTR;
	QSqlDatabase dbOfManuRes;
	QSqlDatabase dbOfAutoRes;

	QSqlQueryModel* modelAutoResQuery = Q_NULLPTR;
	QSqlQueryModel* modelManuResQuery = Q_NULLPTR;

	mySettingWindow* settingWindow = Q_NULLPTR;

	QString databaseAutoName;
	QString databaseManuName;
	QString resFileToMESPath;
	QString resFileToGetPath;
	bool OKModel;
	bool isLogin;

	QString carrierID;
	REGION_IN_CARRIER curViewID;
	int viewSide;

	CarrierResInfo curCarrierRes;
	onePCBResInfo curOnePCBResManu;

	QString ipAddress;
	QString getHostIPAddress();

	void setComBox();

	void getCarrierResInfo(QString carrierId, QString checkDate);
	void getCarrierID_Date(QString onePCBID, QString& carrierId, QString& checkDate);

	void writeDatabaseTable(QString str);
	void saveErrContours(std::string filePath);
	void writeDatabaseTable_TXTFile(onePCBResInfo onePCBResManu);
protected:
	void closeEvent(QCloseEvent* event) override;
};
