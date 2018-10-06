#include "tologin.h"
#include <QMessageBox>
#include <QErrorMessage>
#include <QSqlQuery>

toLogin::toLogin(QWidget *parent)
	: QWidget(parent)
{
	if (!QSqlDatabase::database("USERDATA_DB").isValid())
	{
		this->userDB = QSqlDatabase::addDatabase("QSQLITE", "USERDATA_DB");
	}
	else
	{
		this->userDB = QSqlDatabase::database("USERDATA_DB");
	}

	this->userDB.setDatabaseName("userdata.db");
	if (!this->userDB.open())
	{
		QMessageBox::warning(this, "Link Failed", "Please choose a SQLite3 database", QMessageBox::Abort);
		return;
	}

	ui.setupUi(this);
	ui.userNmae->setFocus();

	connect(ui.password, SIGNAL(returnPressed()), this, SLOT(checkAuthority()));
	connect(ui.loginButton, SIGNAL(clicked()), this, SLOT(checkAuthority()));
	connect(ui.cancelButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui.changeButton, SIGNAL(clicked()), this, SLOT(showChangeDlg()));

}

toLogin::~toLogin()
{
	this->userDB.close();
	QString name;
	{
		name = QSqlDatabase::database().connectionName();
	}
	QSqlDatabase::removeDatabase(name);
}

void toLogin::winClose()
{
	userDB.close();
	QString name;
	{
		name = QSqlDatabase::database().connectionName();
	}
	QSqlDatabase::removeDatabase(name);

	if (changeDlg != Q_NULLPTR)
	{
		changeDlg->winClsoe();
		delete changeDlg;
		changeDlg = Q_NULLPTR;
	}
}

void toLogin::checkAuthority()
{
	QString userName = ui.userNmae->text();
	QString password = ui.password->text();

	QSqlQuery query(this->userDB);
	query.exec("create table userData (UserName varchar(30) primary key, Password varchar(30))");
	query.exec("insert into userData values('supcon', '123456789')");

	query.exec("select * from userData where UserName = '" + userName + "' and Password = '" + password + "'");

	if (query.next())
	{
		emit okToLogin();
		close();
	}
	else
	{
		QErrorMessage * errorDlg = new QErrorMessage(this);
		errorDlg->setWindowTitle("Error");
		if (userName == "")
		{
			errorDlg->showMessage(QString::fromLocal8Bit("用户名不能为空"));
		}
		else if (password == "")
		{
			errorDlg->showMessage(QString::fromLocal8Bit("密码不能为空。"));
		}
		else
		{
			errorDlg->showMessage(QString::fromLocal8Bit("用户名或密码错误，请重新输入。"));
		}
		ui.userNmae->clear();
		ui.password->clear();
		ui.userNmae->setFocus();
	}
}

void toLogin::showChangeDlg()
{
	changeDlg = new toChangePassword;
	//connect(changeDlg, SIGNAL(userDataChanged(QString, QString)), this, SLOT(toChangePassword(QString, QString)));
	changeDlg->show();
}


