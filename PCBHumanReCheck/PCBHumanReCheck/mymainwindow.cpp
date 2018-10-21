#include "mymainwindow.h"
#include "parameters.h"
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QSqlQuery>
#include <QFileDialog>


myMainWindow::myMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	databaseAutoName = "";
	databaseManuName = "";
	resFileToMESPath = "";
	resFileToGetPath = "";
	OKModel = false;
	isLogin = false;

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

	if(infos.size() == 0)
	{
		ui.statusBar->showMessage("No serial port for communication.Not ready for human rechecking.");
	}

	ui.avalSerialPorts->setCurrentIndex(0);

	connect(ui.avalSerialPorts, SIGNAL(currentIndexChanged(int)), this, SLOT(serialPortChanged(int)));
	connect(ui.serialportButton, SIGNAL(clicked()), this, SLOT(openSerial()));

	isLogin = false;
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


	connect(ui.setResPathToMESBt, SIGNAL(clicked()), this, SLOT(setResFileToMESPath()));

	connect(this, SIGNAL(readyCheck()), this, SLOT(showReadyMessage()));
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

			connect(serial, &QSerialPort::readyRead, this, &myMainWindow::readData);

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

	emit readyCheck();

	return false;
}

bool myMainWindow::readData()
{
	bool isGetNewSignal = false;
	QByteArray buf = serial->readAll();

	if (signalCheck(buf))
	{
		if (buf == CARRIERID_TO_CHECK_SIGNAL) //若将二维码信息融入在信号中，则不需要这样的信号，而是直接从接受到的信号中分析该信号是否带有二维码信息
		{
		}
		else if (signalBefore == CARRIERID_TO_CHECK_SIGNAL)
		{
			getCarrierID(buf); //前提，setting文件是以PCB型号命名的.xml文件，此时得到的信号是PCB型号信息/////////////notice
		}
	}
	else
	{
		QByteArray requestData = PARDON_SIGNAL;
		qint64 isOK = serial->write(requestData);

		return isOK == signalNumByte;
	}

	signalBefore = buf;
	return isGetNewSignal;
}

bool myMainWindow::signalCheck(QByteArray buf)
{
	if (!buf.isEmpty())
	{
		char XORCheck = buf[0];
		for (int i = 1; i < buf.size() - 1; i++)
		{
			XORCheck = XORCheck ^ buf.at(i);
		}

		if (XORCheck == buf[buf.size() - 1])
		{
			return true;
		}
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
		connect(loginWin, SIGNAL(okToLogin()), this, SLOT(beLogged()));
		loginWin->show();
	}
}

void myMainWindow::beLogged()
{
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
	if (!dbOfManuRes.isValid())
	{
		QString fileName = QFileDialog::getOpenFileName(this, tr("Load Manual ReCheckRes Database"), ".", tr("Settings (*.db)"));
		if (fileName.isEmpty())
		{
			return -1;
		}

		dbOfManuRes = QSqlDatabase::addDatabase("QSQLITE", "RESULT_DB");
		dbOfManuRes.setDatabaseName(fileName);

		if (!dbOfManuRes.open())
		{
			QMessageBox::warning(this, "Link Failed", "Please choose a SQLite3 database", QMessageBox::Abort);
			return -1;
		}
		databaseManuName = fileName;
		if (settingWindow != Q_NULLPTR)
		{
			settingWindow->updateDatabaseManuFile(fileName);
		}
		emit readyCheck();
	}

	QSqlQuery query(dbOfManuRes);
	query.exec("create table checkRes (PCBID varchar(30) primary key, "
		"CarrierID varchar(30), Date varchar(20), Time varchar(20), Checker varchar(10), Device varchar(10), Result varchar(30))");

	databaseView = new myDatabaseTable(dbOfManuRes);
	databaseView->show();
	return 0;
}

void myMainWindow::showSettingWin()
{
	settingWindow = new mySettingWindow(databaseAutoName, databaseManuName, resFileToGetPath, resFileToMESPath, OKModel);
	connect(settingWindow, SIGNAL(newDatabaseAutoName(QString)), this, SLOT(updateDatabaseAutoFile(QString)));
	connect(settingWindow, SIGNAL(newDatabaseManuName(QString)), this, SLOT(updateDatabaseManuFile(QString)));
	connect(settingWindow, SIGNAL(newResFileToGetPath(QString)), this, SLOT(updateResFileToGetPath(QString)));
	connect(settingWindow, SIGNAL(newResFileToMESPath(QString)), this, SLOT(updateResFileToMESPath(QString)));
	connect(settingWindow, SIGNAL(newOKModel(bool)), this, SLOT(updateOKModel(bool)));
	settingWindow->show();
}

void myMainWindow::newDatabase()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Create new Manual ReCheckRes Database"), ".", tr("Settings (*.db);"));
	if (fileName.isEmpty())
	{
		return;
	}

	if (!dbOfManuRes.isValid())
	{
		dbOfManuRes = QSqlDatabase::addDatabase("QSQLITE", "RESULT_DB");
	}

	dbOfManuRes.setDatabaseName(fileName);

	if (!dbOfManuRes.open())
	{
		QMessageBox::warning(this, "Link Failed", "Please choose a SQLite3 database", QMessageBox::Abort);
		return;
	}

	databaseManuName = fileName;
	if (settingWindow != Q_NULLPTR)
	{
		settingWindow->updateDatabaseAutoFile(fileName);
	}
	emit readyCheck();
}

void myMainWindow::setDatabaseAuto()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Load AutoCheck Result Database"), ".", tr("Settings (*.db)"));
	if (fileName.isEmpty())
	{
		return;
	}

	if (!dbOfAutoRes.isValid())
	{
		dbOfAutoRes = QSqlDatabase::addDatabase("QSQLITE", "AUTO_RESULT_DB");
	}

	dbOfAutoRes.setDatabaseName(fileName);

	if (!dbOfAutoRes.open())
	{
		QMessageBox::warning(this, "Link Failed", "Please choose a SQLite3 database", QMessageBox::Abort);
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
	QString fileName = QFileDialog::getOpenFileName(this, tr("Load Manual ReCheckRes Database"), ".", tr("Settings (*.db)"));
	if (fileName.isEmpty())
	{
		return;
	}

	if (!dbOfManuRes.isValid())
	{
		dbOfManuRes = QSqlDatabase::addDatabase("QSQLITE", "MANU_RESULT_DB");
	}

	dbOfManuRes.setDatabaseName(fileName);

	if (!dbOfManuRes.open())
	{
		QMessageBox::warning(this, "Link Failed", "Please choose a SQLite3 database", QMessageBox::Abort);
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
	if (settingWindow != Q_NULLPTR)
	{
		settingWindow->updateResFileToGetPath(resFileToGetPath);
	}
	emit readyCheck();
}

void myMainWindow::setResFileToMESPath()
{
	resFileToMESPath = QFileDialog::getExistingDirectory(this);

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

void myMainWindow::updateDatabaseAutoFile(QString fileName)
{
	if (fileName.isEmpty())
	{
		return;
	}

	if (!dbOfAutoRes.isValid())
	{
		dbOfAutoRes = QSqlDatabase::addDatabase("QSQLITE", "AUTO_RESULT_DB");
	}

	dbOfAutoRes.setDatabaseName(fileName);

	if (!dbOfAutoRes.open())
	{
		QMessageBox::warning(this, "Link Failed", "Please choose a SQLite3 database", QMessageBox::Abort);
		return;
	}

	databaseAutoName = fileName;
	emit readyCheck();
}

void myMainWindow::updateDatabaseManuFile(QString fileName)
{
	if (fileName.isEmpty())
	{
		return;
	}

	if (!dbOfManuRes.isValid())
	{
		dbOfManuRes = QSqlDatabase::addDatabase("QSQLITE", "MANU_RESULT_DB");
	}

	dbOfManuRes.setDatabaseName(fileName);

	if (!dbOfManuRes.open())
	{
		QMessageBox::warning(this, "Link Failed", "Please choose a SQLite3 database", QMessageBox::Abort);
		return;
	}

	databaseManuName = fileName;
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

void myMainWindow::showReadyMessage()
{
	if(isLogin && !resFileToMESPath.isEmpty() && !databaseManuName.isEmpty() && !databaseAutoName.isEmpty() && ui.serialportButton->text() == tr("Close Serial Port"))
	{
		if(OKModel)
		{
			ui.statusBar->showMessage("Ready for human rechecking.OK results are not rechecked.");
		}
		else
		{
			ui.statusBar->showMessage("Ready for human rechecking.OK results are also rechecked.");
		}
		QByteArray requestData = ASK_FOR_NEW_CARRIERID_SIGNAL;
		qint64 isOK = serial->write(requestData);
	}
	else
	{
		ui.statusBar->showMessage("Not ready for human rechecking.");
	}
}

void myMainWindow::getCarrierID(QByteArray onePCBIDSignal)
{
	QString onePCBID = onePCBIDSignal;

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
