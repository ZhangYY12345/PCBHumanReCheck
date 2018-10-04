#include "mymainwindow.h"

myMainWindow::myMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
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

}

myMainWindow::~myMainWindow()
{
}
