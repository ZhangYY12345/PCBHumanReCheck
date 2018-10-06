#pragma once

#include <QWidget>
#include "ui_mysettingwindow.h"

class mySettingWindow : public QWidget
{
	Q_OBJECT

public:
	mySettingWindow(QWidget *parent = Q_NULLPTR);
	mySettingWindow(QString databaseName, QString resFilePath, bool okModel, QWidget *parent = Q_NULLPTR);
	~mySettingWindow();

	void updateDatabaseFile(QString);
	void updateResFilePath(QString);
	void updateOKModel(bool);

	signals:
	void newDatabaseName(QString);
	void newResFilePath(QString);
	void newOKModel(bool);

	private slots:
	void setDatabaseFile();
	void setResFilePath();
	void setTransferModel();

private:
	Ui::mySettingWindow ui;
	QString databaseName;
	QString resFilePath;
	bool isTransferOK;
};
