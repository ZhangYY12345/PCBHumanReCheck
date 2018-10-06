#include "mysettingwindow.h"
#include <QFiledialog>

mySettingWindow::mySettingWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.setDatabaseBt, SIGNAL(clicked()), this, SLOT(setDatabaseFile()));
	connect(ui.setResPathBt, SIGNAL(clicked()), this, SLOT(setResFilePath()));
	connect(ui.setModelBt, SIGNAL(clicked()), this, SLOT(setTransferModel()));
}

mySettingWindow::mySettingWindow(QString databaseName, QString resFilePath, bool okModel, QWidget* parent)
{
	ui.setupUi(this);

	ui.setDatabase->setText(databaseName);
	ui.setResPath->setText(resFilePath);
	ui.setModelBt->setChecked(okModel);

	connect(ui.setDatabaseBt, SIGNAL(clicked()), this, SLOT(setDatabaseFile()));
	connect(ui.setResPathBt, SIGNAL(clicked()), this, SLOT(setResFilePath()));
	connect(ui.setModelBt, SIGNAL(clicked()), this, SLOT(setTransferModel()));
}

mySettingWindow::~mySettingWindow()
{
}

void mySettingWindow::updateDatabaseFile(QString newName)
{
	databaseName = newName;
	ui.setDatabase->setText(databaseName);
}

void mySettingWindow::updateResFilePath(QString newNames)
{
	resFilePath = newNames;
	ui.setResPath->setText(resFilePath);
}

void mySettingWindow::updateOKModel(bool okModel)
{
	disconnect(ui.setModelBt, SIGNAL(clicked()), this, SLOT(setTransferModel()));
	isTransferOK = okModel;
	ui.setModelBt->setChecked(isTransferOK);
	connect(ui.setModelBt, SIGNAL(clicked()), this, SLOT(setTransferModel()));
}

void mySettingWindow::setDatabaseFile()
{
	databaseName = QFileDialog::getExistingDirectory(this);
	ui.setDatabase->setText(databaseName);
	emit newDatabaseName(databaseName);
}

void mySettingWindow::setResFilePath()
{
	resFilePath = QFileDialog::getExistingDirectory(this);
	ui.setResPath->setText(resFilePath);
	emit newResFilePath(resFilePath);
}

void mySettingWindow::setTransferModel()
{
	isTransferOK = ui.setModelBt->isChecked();
	emit newOKModel(isTransferOK);
}
