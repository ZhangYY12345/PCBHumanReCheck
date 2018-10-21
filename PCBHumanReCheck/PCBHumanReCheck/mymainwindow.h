#pragma once

#include <QMainWindow>
#include "ui_mymainwindow.h"
#include <QSerialPort>
#include "tologin.h"
#include "mysettingwindow.h"
#include "mydatabasetable.h"

class myMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	myMainWindow(QWidget *parent = Q_NULLPTR);
	~myMainWindow();

	signals:
	void readyCheck();

	private slots:
	void serialportChanged(int index);
	bool openSerial();

	bool readData();
	bool signalCheck(QByteArray buf);

	void toLog();
	void beLogged();
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

	void showReadyMessage();

private:
	Ui::myMainWindow ui;

	QSerialPort* serial = Q_NULLPTR;
	QByteArray signalBefore;
	QByteArray onePCBIDSignal;

	toLogin* loginWin = Q_NULLPTR;

	myDatabaseTable* databaseView = Q_NULLPTR;
	QSqlDatabase dbOfManuRes;
	QSqlDatabase dbOfAutoRes;

	mySettingWindow* settingWindow = Q_NULLPTR;

	QString databaseAutoName;
	QString databaseManuName;
	QString resFileToMESPath;
	QString resFileToGetPath;
	bool OKModel;
	bool isLogin;

	void getCarrierID(QByteArray onePCBIDSignal);

protected:
	void closeEvent(QCloseEvent* event) override;
};
