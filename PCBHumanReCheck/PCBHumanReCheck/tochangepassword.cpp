#include "tochangepassword.h"
#include <QMessageBox>
#include <QErrorMessage>
#include <QSqlQuery>

toChangePassword::toChangePassword(QWidget *parent)
	: QWidget(parent)
{
	this->userDB = QSqlDatabase::database("USERDATA_DB");
	this->userDB.setDatabaseName("userdata.db");
	if (!this->userDB.open())
	{
		QMessageBox::warning(this, "Link Failed", "Please choose a SQLite3 database", QMessageBox::Abort);
		return;
	}

	ui.setupUi(this);

	connect(ui.changeButton, SIGNAL(clicked()), this, SLOT(changePassword()));
	connect(ui.cancelButton, SIGNAL(clicked()), this, SLOT(close()));

}

toChangePassword::~toChangePassword()
{
	this->userDB.close();
	QString name;
	{
		name = QSqlDatabase::database().connectionName();
	}
	QSqlDatabase::removeDatabase(name);

}

void toChangePassword::winClsoe()
{
	this->userDB.close();
	QString name;
	{
		name = QSqlDatabase::database().connectionName();
	}
	QSqlDatabase::removeDatabase(name);
}

void toChangePassword::changePassword()
{
	QErrorMessage * errorDlg;

	QSqlQuery query(this->userDB);
	query.exec("create table userData (UserName varchar(30) primary key, Password varchar(30))");
	query.exec("insert into userData values('supcon', '123456789')");

	query.exec("select * from userData where UserName = '" + ui.userNmae->text() + "' and Password = '" + ui.oldPassword->text() + "'");

	if (query.next())
	{
		if (ui.newPassword->text() == ui.sureNewPassword->text())
		{
			query.exec("update userData set Password = '" + ui.newPassword->text() + "' where UserName = '" + ui.userNmae->text() + "'");
			close();
		}
		else
		{
			errorDlg = new QErrorMessage(this);
			errorDlg->setWindowTitle("Error");
			errorDlg->showMessage(QString::fromLocal8Bit("两次输入的密码不一样"));
			ui.newPassword->clear();
			ui.sureNewPassword->clear();
			ui.newPassword->setFocus();
		}
	}
	else
	{
		errorDlg = new QErrorMessage(this);
		errorDlg->setWindowTitle("Error");
		if (ui.userNmae->text() == "")
		{
			errorDlg->showMessage(QString::fromLocal8Bit("用户名不能为空"));
		}
		else if (ui.oldPassword->text() == "")
		{
			errorDlg->showMessage(QString::fromLocal8Bit("原密码不能为空。"));
		}
		else
		{
			errorDlg->showMessage(QString::fromLocal8Bit("用户名或密码错误，请重新输入。"));
		}
		ui.userNmae->clear();
		ui.oldPassword->clear();
		ui.newPassword->clear();
		ui.sureNewPassword->clear();
		ui.userNmae->setFocus();
	}
}
