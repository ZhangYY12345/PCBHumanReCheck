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

	private slots:
	void serialportChanged(int index);
	bool openSerial();

	void toLog();
	void beLogged();
	int showDatabaseTable();
	void showSettingWin();

	void newDatabase();
	void setDatabase();
	void setResFilePath();
	void setTransferModelAuto();
	void setTransferModelNotAuto();

	void updateDatabaseFile(QString);
	void updateResFilePath(QString);
	void updateOKModel(bool);

private:
	Ui::myMainWindow ui;

	QSerialPort* serial = Q_NULLPTR;
	toLogin* loginWin = Q_NULLPTR;

	myDatabaseTable* databaseView = Q_NULLPTR;
	QSqlDatabase db;

	mySettingWindow* settingWindow = Q_NULLPTR;

	QString databaseName;
	QString resFilePath;
	bool OKModel;

protected:
	void closeEvent(QCloseEvent* event) override;
};
