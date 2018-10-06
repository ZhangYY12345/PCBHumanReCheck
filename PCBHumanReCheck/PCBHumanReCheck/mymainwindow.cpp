#include "mymainwindow.h"
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QSqlQuery>
#include <QFileDialog>


bool isLogin = false;

myMainWindow::myMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	databaseName = "";
	resFilePath = "";
	OKModel = false;

	ui.setupUi(this);

	const auto infos = QSerialPortInfo::availablePorts();
	foreach(const QSerialPortInfo &info, infos)
	{
		QSerialPort serial;
		serial.setPort(info);
		if (serial.open(QIODevice::ReadWrite))
		{
			ui.avalSerialPorts->addItem(info.portName());
			serial.close();
		}
	}
	ui.avalSerialPorts->setCurrentIndex(0);

	connect(ui.avalSerialPorts, SIGNAL(currentIndexChanged(int)), this, SLOT(serialPortChanged(int)));
	connect(ui.serialportButton, SIGNAL(clicked()), this, SLOT(openSerial()));

	isLogin = false;

	connect(ui.actLogin, SIGNAL(triggered()), this, SLOT(toLog()));
	connect(ui.actViewDatabase, SIGNAL(triggered()), this, SLOT(showDatabaseTable()));
	connect(ui.actSettings, SIGNAL(triggered()), this, SLOT(showSettingWin()));


	connect(ui.actionNewDB, SIGNAL(triggered()), this, SLOT(newDatabase()));
	connect(ui.actionOpenDB, SIGNAL(triggered()), this, SLOT(setDatabase()));
	connect(ui.actionSetPath, SIGNAL(triggered()), this, SLOT(setResFilePath()));
	connect(ui.actionOKAuto, SIGNAL(triggered()), this, SLOT(setTransferModelAuto()));
	connect(ui.actionOKNotAuto, SIGNAL(triggered()), this, SLOT(setTransferModelNotAuto()));


	connect(ui.setResPathBt, SIGNAL(clicked()), this, SLOT(setResFilePath()));
}

myMainWindow::~myMainWindow()
{
}

void myMainWindow::serialportChanged(int index)
{
	ui.avalSerialPorts->setCurrentIndex(index);
}

bool myMainWindow::openSerial()
{
	QString portName = ui.avalSerialPorts->currentText();
	if (ui.serialportButton->text() == tr("Open Serial Port"))
	{
		serial = new QSerialPort();
		serial->setPortName(portName);
		if (serial->open(QIODevice::ReadWrite))
		{
			serial->setDataTerminalReady(true);
			serial->setBaudRate(QSerialPort::Baud115200); //setting baud rate
			serial->setDataBits(QSerialPort::Data8);

			ui.avalSerialPorts->setEnabled(false);
			ui.serialportButton->setText(tr("Close Serial Port"));

			return true;
		}
	}
	else
	{
		serial->clear();
		serial->close();
		serial->deleteLater();

		ui.avalSerialPorts->setEnabled(true);
		ui.serialportButton->setText(tr("Open Serial Port"));
		return false;
	}
	return false;
}

void myMainWindow::toLog()
{
	if(isLogin)
	{
		int r = QMessageBox::question(this, tr("Logout"), tr("You has logged in.\nDo you want to logout now?"), QMessageBox::Yes, QMessageBox::No);
		if (r == QMessageBox::Yes)
		{
			isLogin = false;
			loginWin->winClose();
		}
	}
	else
	{
		loginWin = new toLogin;
		connect(loginWin, SIGNAL(okToLogin()), this, SLOT(beLogged()));
		loginWin->show();
	}
}

void myMainWindow::beLogged()
{
	isLogin = true;
	if(loginWin != Q_NULLPTR)
	{
		loginWin->winClose();
	}
}

int myMainWindow::showDatabaseTable()
{
	if (!db.isValid())
	{
		db = QSqlDatabase::addDatabase("QSQLITE", "RESULT_DB");
		QString fileName = QFileDialog::getOpenFileName(this, tr("Load Database"), ".", tr("Settings (*.db)"));
		if (fileName.isEmpty())
		{
			return -1;
		}

		db.setDatabaseName(fileName);

		if (!db.open())
		{
			QMessageBox::warning(this, "Link Failed", "Please choose a SQLite3 database", QMessageBox::Abort);
			return -1;
		}
	}

	QSqlQuery query(db);
	query.exec("create table checkRes (PCBID varchar(30) primary key, "
		"CarrierID varchar(30), REGIONID varchar(10), Date varchar(20), Time varchar(20), Result varchar(30), resImgPath varchar(100))");

	databaseView = new myDatabaseTable(db);
	databaseView->show();
	return 0;
}

void myMainWindow::showSettingWin()
{
	settingWindow = new mySettingWindow(databaseName, resFilePath, OKModel);
	connect(settingWindow, SIGNAL(newDatabaseName(QString)), this, SLOT(updateDatabaseFile(QString)));
	connect(settingWindow, SIGNAL(newResFilePath(QString)), this, SLOT(updateResFilePath(QString)));
	connect(settingWindow, SIGNAL(newOKModel(bool)), this, SLOT(updateOKModel(bool)));
	settingWindow->show();
}

void myMainWindow::newDatabase()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save new Database"), ".", tr("Settings (*.db);"));
	if (fileName.isEmpty())
	{
		return;
	}

	if (!db.isValid())
	{
		db = QSqlDatabase::addDatabase("QSQLITE", "RESULT_DB");
	}

	db.setDatabaseName(fileName);

	if (!db.open())
	{
		QMessageBox::warning(this, "Link Failed", "Please choose a SQLite3 database", QMessageBox::Abort);
		return;
	}

	databaseName = fileName;
	if (settingWindow != Q_NULLPTR)
	{
		settingWindow->updateDatabaseFile(fileName);
	}
}

void myMainWindow::setDatabase()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Load Database"), ".", tr("Settings (*.db)"));
	if (fileName.isEmpty())
	{
		return;
	}

	if (!db.isValid())
	{
		db = QSqlDatabase::addDatabase("QSQLITE", "RESULT_DB");
	}

	db.setDatabaseName(fileName);

	if (!db.open())
	{
		QMessageBox::warning(this, "Link Failed", "Please choose a SQLite3 database", QMessageBox::Abort);
		return;
	}

	databaseName = fileName;
	if(settingWindow != Q_NULLPTR)
	{
		settingWindow->updateDatabaseFile(fileName);
	}
}

void myMainWindow::setResFilePath()
{
	resFilePath = QFileDialog::getExistingDirectory(this);

	ui.resultPathLab->setText(resFilePath);
	if (settingWindow != Q_NULLPTR)
	{
		settingWindow->updateResFilePath(resFilePath);
	}
}

void myMainWindow::setTransferModelAuto()
{
	OKModel = true;
	disconnect(ui.actionOKNotAuto, SIGNAL(triggered()), this, SLOT(setTransferModelNotAuto()));
	ui.actionOKNotAuto->setChecked(false);
	connect(ui.actionOKNotAuto, SIGNAL(triggered()), this, SLOT(setTransferModelNotAuto()));

	if (settingWindow != Q_NULLPTR)
	{
		settingWindow->updateOKModel(true);
	}
}

void myMainWindow::setTransferModelNotAuto()
{
	OKModel = false;
	disconnect(ui.actionOKAuto, SIGNAL(triggered()), this, SLOT(setTransferModelAuto()));
	ui.actionOKAuto->setChecked(false);
	connect(ui.actionOKAuto, SIGNAL(triggered()), this, SLOT(setTransferModelAuto()));

	if (settingWindow != Q_NULLPTR)
	{
		settingWindow->updateOKModel(false);
	}
}

void myMainWindow::updateDatabaseFile(QString fileName)
{
	if (fileName.isEmpty())
	{
		return;
	}

	if (!db.isValid())
	{
		db = QSqlDatabase::addDatabase("QSQLITE", "RESULT_DB");
	}

	db.setDatabaseName(fileName);

	if (!db.open())
	{
		QMessageBox::warning(this, "Link Failed", "Please choose a SQLite3 database", QMessageBox::Abort);
		return;
	}

	databaseName = fileName;
}

void myMainWindow::updateResFilePath(QString filePath)
{
	resFilePath = filePath;
	ui.resultPathLab->setText(resFilePath);
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
}

void myMainWindow::closeEvent(QCloseEvent* event)
{
	if (this->serial != Q_NULLPTR)
	{
		if (this->serial->isOpen())
		{
			serial->clear();
			serial->close();
		}
	}
}
