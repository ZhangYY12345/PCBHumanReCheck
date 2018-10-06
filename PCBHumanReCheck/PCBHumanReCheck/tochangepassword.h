#pragma once

#include <QWidget>
#include <QSqlDatabase>
#include "ui_tochangepassword.h"

class toChangePassword : public QWidget
{
	Q_OBJECT

public:
	toChangePassword(QWidget *parent = Q_NULLPTR);
	~toChangePassword();

	void winClsoe();

	public slots :
	void changePassword();

private:
	Ui::toChangePassword ui;
	QSqlDatabase userDB;
};
