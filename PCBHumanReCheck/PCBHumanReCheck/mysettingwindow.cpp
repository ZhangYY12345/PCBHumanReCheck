#include "mysettingwindow.h"
#include <QFiledialog>
#include <QSqlDatabase>
#include <QMessageBox>

mySettingWindow::mySettingWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.setDatabaseAutoBt, SIGNAL(clicked()), this, SLOT(setDatabaseAutoFile()));
	connect(ui.setDatabaseManuBt, SIGNAL(clicked()), this, SLOT(setDatabaseManuFile()));
	connect(ui.setResToGetPathBt, SIGNAL(clicked()), this, SLOT(setResFileToGetPath()));
	connect(ui.setResToMESPathBt, SIGNAL(clicked()), this, SLOT(setResFileToMESPath()));
	connect(ui.setModelBt, SIGNAL(clicked()), this, SLOT(setTransferModel()));
}

mySettingWindow::mySettingWindow(QString databaseName, QString databaseManuName, QString resFileToGetPath, QString resFileToMESPath, bool okModel, QWidget* parent)
{
	ui.setupUi(this);

	ui.setDatabaseAuto->setText(databaseName);
	ui.setDatabaseManu->setText(databaseManuName);
	ui.setResToGetPath->setText(resFileToGetPath);
	ui.setResToMESPath->setText(resFileToMESPath);
	ui.setModelBt->setChecked(okModel);

	connect(ui.setDatabaseAutoBt, SIGNAL(clicked()), this, SLOT(setDatabaseAutoFile()));
	connect(ui.setDatabaseManuBt, SIGNAL(clicked()), this, SLOT(setDatabaseManuFile()));
	connect(ui.setResToGetPathBt, SIGNAL(clicked()), this, SLOT(setResFileToGetPath()));
	connect(ui.setResToMESPathBt, SIGNAL(clicked()), this, SLOT(setResFileToMESPath()));
	connect(ui.setModelBt, SIGNAL(clicked()), this, SLOT(setTransferModel()));
}

mySettingWindow::~mySettingWindow()
{
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

void mySettingWindow::setDatabaseAutoFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("数据库加载"), ".", QString::fromLocal8Bit("数据库") + tr(" (*.db)"));
	if (fileName.isEmpty())
	{
		return;
	}

	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "RESULT_DB");
	db.setDatabaseName(fileName);

	if (!db.open())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("文件打开失败"), QString::fromLocal8Bit("请重新选择数据库文件。"), QMessageBox::Abort);
		return;
	}
	db.close();
	QSqlDatabase::removeDatabase("RESULT_DB");

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

	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "RESULT_DB");
	db.setDatabaseName(fileName);

	if (!db.open())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("文件打开失败"), QString::fromLocal8Bit("请重新选择数据库文件。"), QMessageBox::Abort);
		return;
	}
	db.close();
	QSqlDatabase::removeDatabase("RESULT_DB");

	databaseManuName = fileName;
	ui.setDatabaseManu->setText(databaseManuName);
	emit newDatabaseManuName(databaseManuName);

}

void mySettingWindow::setResFileToGetPath()
{
	resFileToGetPath = QFileDialog::getExistingDirectory(this);
	ui.setResToGetPath->setText(resFileToGetPath);
	emit newResFileToGetPath(resFileToGetPath);
}

void mySettingWindow::setResFileToMESPath()
{
	resFileToMESPath = QFileDialog::getExistingDirectory(this);
	ui.setResToMESPath->setText(resFileToMESPath);
	emit newResFileToMESPath(resFileToMESPath);
}

void mySettingWindow::setTransferModel()
{
	isTransferOK = ui.setModelBt->isChecked();
	emit newOKModel(isTransferOK);
}
