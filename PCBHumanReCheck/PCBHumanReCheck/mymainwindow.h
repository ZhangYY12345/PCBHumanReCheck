#pragma once

#include <QMainWindow>
#include "ui_mymainwindow.h"
#include <QSerialPort>

class myMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	myMainWindow(QWidget *parent = Q_NULLPTR);
	~myMainWindow();

private:
	Ui::myMainWindow ui;
};
