#include "mysettingwindow.h"
#include <QFiledialog>
#include <QSqlDatabase>
#include <QMessageBox>
#include "methods.h"

mySettingWindow::mySettingWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.toConnectIP, SIGNAL(editingFinished()), this, SLOT(setComIP()));
	connect(ui.setDatabaseAutoBt, SIGNAL(clicked()), this, SLOT(setDatabaseAutoFile()));
	connect(ui.setDatabaseManuBt, SIGNAL(clicked()), this, SLOT(setDatabaseManuFile()));
	connect(ui.setResToGetPathBt, SIGNAL(clicked()), this, SLOT(setResFileToGetPath()));
	connect(ui.setResToMESPathBt, SIGNAL(clicked()), this, SLOT(setResFileToMESPath()));
	connect(ui.setModelBt, SIGNAL(clicked()), this, SLOT(setTransferModel()));
}

mySettingWindow::mySettingWindow(QString comIP, QString databaseName, QString databaseManuName, QString resFileToGetPath, QString resFileToMESPath, bool okModel, QWidget* parent)
{
	ui.setupUi(this);

	ui.toConnectIP->setText(comIP);
	ui.toConnectIP->setCursorMoveStyle(Qt::VisualMoveStyle);

	ui.setDatabaseAuto->setText(databaseName);
	ui.setDatabaseManu->setText(databaseManuName);
	ui.setResToGetPath->setText(resFileToGetPath);
	ui.setResToMESPath->setText(resFileToMESPath);
	ui.setModelBt->setChecked(okModel);

	connect(ui.toConnectIP, SIGNAL(editingFinished()), this, SLOT(setComIP()));
	connect(ui.setDatabaseAutoBt, SIGNAL(clicked()), this, SLOT(setDatabaseAutoFile()));
	connect(ui.setDatabaseManuBt, SIGNAL(clicked()), this, SLOT(setDatabaseManuFile()));
	connect(ui.setResToGetPathBt, SIGNAL(clicked()), this, SLOT(setResFileToGetPath()));
	connect(ui.setResToMESPathBt, SIGNAL(clicked()), this, SLOT(setResFileToMESPath()));
	connect(ui.setModelBt, SIGNAL(clicked()), this, SLOT(setTransferModel()));
}

mySettingWindow::~mySettingWindow()
{
}

void mySettingWindow::updateComIP(QString comIP)
{
	if(ipCheck(comIP))
	{
		toConnectComIP = comIP;
		ui.toConnectIP->setText(toConnectComIP);
		ui.toConnectIP->setCursorMoveStyle(Qt::VisualMoveStyle);
	}
}

void mySettingWindow::updateDatabaseAutoFile(QString newName)
{
	databaseAutoName = newName;
	ui.setDatabaseAuto->setText(databaseAutoName);
}

void mySettingWindow::updateDatabaseManuFile(QString newName)
{
	databaseManuName = newName;
	ui.setDatabaseManu->setText(databaseManuName);
}

void mySettingWindow::updateResFileToGetPath(QString newName)
{
	resFileToGetPath = newName;
	ui.setResToGetPath->setText(resFileToGetPath);
}

void mySettingWindow::updateResFileToMESPath(QString newNames)
{
	resFileToMESPath = newNames;
	ui.setResToMESPath->setText(resFileToMESPath);
}

void mySettingWindow::updateOKModel(bool okModel)
{
	disconnect(ui.setModelBt, SIGNAL(clicked()), this, SLOT(setTransferModel()));
	isTransferOK = okModel;
	ui.setModelBt->setChecked(isTransferOK);
	connect(ui.setModelBt, SIGNAL(clicked()), this, SLOT(setTransferModel()));
}

void mySettingWindow::setComIP()
{
	QString comIP = ui.toConnectIP->text();
	if(ipCheck(comIP))
	{
		toConnectComIP = comIP;
		emit newComIP(toConnectComIP);
	}
}

void mySettingWindow::setDatabaseAutoFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("数据库加载"), ".", QString::fromLocal8Bit("数据库") + tr(" (*.db)"));
	if (fileName.isEmpty())
	{
		return;
	}

	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "AUTO_RESULT_DB");
	db.setDatabaseName(fileName);

	if (!db.open())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("文件打开失败"), QString::fromLocal8Bit("请重新选择数据库文件。"), QMessageBox::Abort);
		return;
	}
	db.close();
	QSqlDatabase::removeDatabase("AUTO_RESULT_DB");

	databaseAutoName = fileName;
	ui.setDatabaseAuto->setText(databaseAutoName);
	emit newDatabaseAutoName(databaseAutoName);
}

void mySettingWindow::setDatabaseManuFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("数据库加载"), ".", QString::fromLocal8Bit("数据库") + tr(" (*.db)"));
	if (fileName.isEmpty())
	{
		return;
	}

	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "MANU_RESULT_DB");
	db.setDatabaseName(fileName);

	if (!db.open())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("文件打开失败"), QString::fromLocal8Bit("请重新选择数据库文件。"), QMessageBox::Abort);
		return;
	}
	db.close();
	QSqlDatabase::removeDatabase("MANU_RESULT_DB");

	databaseManuName = fileName;
	ui.setDatabaseManu->setText(databaseManuName);
	emit newDatabaseManuName(databaseManuName);

}

void mySettingWindow::setResFileToGetPath()
{
	resFileToGetPath = QFileDialog::getExistingDirectory(this);
	resFileToGetPath = changePathDirt(resFileToGetPath);

	ui.setResToGetPath->setText(resFileToGetPath);
	emit newResFileToGetPath(resFileToGetPath);
}

void mySettingWindow::setResFileToMESPath()
{
	resFileToMESPath = QFileDialog::getExistingDirectory(this);
	resFileToMESPath = changePathDirt(resFileToMESPath);

	ui.setResToMESPath->setText(resFileToMESPath);
	emit newResFileToMESPath(resFileToMESPath);
}

void mySettingWindow::setTransferModel()
{
	isTransferOK = ui.setModelBt->isChecked();
	emit newOKModel(isTransferOK);
}

bool mySettingWindow::ipCheck(QString comIP)
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
