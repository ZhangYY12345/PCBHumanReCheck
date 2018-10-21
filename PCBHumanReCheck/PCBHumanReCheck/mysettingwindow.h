#pragma once

#include <QWidget>
#include "ui_mysettingwindow.h"

class mySettingWindow : public QWidget
{
	Q_OBJECT

public:
	mySettingWindow(QWidget *parent = Q_NULLPTR);
	mySettingWindow(QString databaseName, QString databaseManuName, QString resFileToGetPath, QString resFileToMESPath, bool okModel, QWidget *parent = Q_NULLPTR);
	~mySettingWindow();

	void updateDatabaseAutoFile(QString);
	void updateDatabaseManuFile(QString);
	void updateResFileToGetPath(QString);
	void updateResFileToMESPath(QString);
	void updateOKModel(bool);

	signals:
	void newDatabaseAutoName(QString);
	void newDatabaseManuName(QString);
	void newResFileToGetPath(QString);
	void newResFileToMESPath(QString);
	void newOKModel(bool);

	private slots:
	void setDatabaseAutoFile();
	void setDatabaseManuFile();
	void setResFileToGetPath();
	void setResFileToMESPath();
	void setTransferModel();

private:
	Ui::mySettingWindow ui;
	QString databaseAutoName;
	QString databaseManuName;
	QString resFileToGetPath;
	QString resFileToMESPath;
	bool isTransferOK;
};
