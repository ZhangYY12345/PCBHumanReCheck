#pragma once

#include <QWidget>
#include "ui_tologin.h"
#include "tochangepassword.h"
#include <QSqlDatabase>

class toLogin : public QWidget
{
	Q_OBJECT

public:
	toLogin(QWidget *parent = Q_NULLPTR);
	~toLogin();

	void winClose();

	signals:
	void okToLogin(QString);

	public slots:
	void checkAuthority();
	void showChangeDlg();
	
private:
	Ui::toLogin ui;
	toChangePassword* changeDlg = Q_NULLPTR;
	QSqlDatabase userDB;
};
