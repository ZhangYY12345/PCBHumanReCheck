#pragma once

#include <QWidget>
#include "ui_mysettingwindow.h"

class mySettingWindow : public QWidget
{
	Q_OBJECT

public:
	mySettingWindow(QWidget *parent = Q_NULLPTR);
	~mySettingWindow();

private:
	Ui::mySettingWindow ui;
};
