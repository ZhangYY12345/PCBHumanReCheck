/********************************************************************************
** Form generated from reading UI file 'tologin.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOLOGIN_H
#define UI_TOLOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_toLogin
{
public:
    QGroupBox *groupBox;
    QLabel *label_2;
    QLineEdit *password;
    QLineEdit *userNmae;
    QLabel *label;
    QPushButton *loginButton;
    QPushButton *changeButton;
    QPushButton *cancelButton;

    void setupUi(QWidget *toLogin)
    {
        if (toLogin->objectName().isEmpty())
            toLogin->setObjectName(QStringLiteral("toLogin"));
        toLogin->resize(400, 245);
        groupBox = new QGroupBox(toLogin);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(50, 30, 301, 101));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 60, 54, 21));
        password = new QLineEdit(groupBox);
        password->setObjectName(QStringLiteral("password"));
        password->setGeometry(QRect(80, 60, 191, 20));
        password->setInputMask(QStringLiteral(""));
        password->setText(QStringLiteral(""));
        password->setFrame(true);
        password->setEchoMode(QLineEdit::Password);
        password->setCursorPosition(0);
        userNmae = new QLineEdit(groupBox);
        userNmae->setObjectName(QStringLiteral("userNmae"));
        userNmae->setGeometry(QRect(80, 20, 191, 21));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 22, 54, 20));
        loginButton = new QPushButton(toLogin);
        loginButton->setObjectName(QStringLiteral("loginButton"));
        loginButton->setGeometry(QRect(110, 160, 75, 23));
        changeButton = new QPushButton(toLogin);
        changeButton->setObjectName(QStringLiteral("changeButton"));
        changeButton->setGeometry(QRect(110, 190, 71, 21));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(9);
        font.setItalic(true);
        font.setUnderline(true);
        changeButton->setFont(font);
        changeButton->setFocusPolicy(Qt::StrongFocus);
        changeButton->setContextMenuPolicy(Qt::NoContextMenu);
        changeButton->setIconSize(QSize(16, 16));
#ifndef QT_NO_SHORTCUT
        changeButton->setShortcut(QStringLiteral(""));
#endif // QT_NO_SHORTCUT
        changeButton->setCheckable(false);
        changeButton->setAutoRepeat(false);
        changeButton->setAutoDefault(false);
        changeButton->setFlat(true);
        cancelButton = new QPushButton(toLogin);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setGeometry(QRect(240, 160, 75, 23));

        retranslateUi(toLogin);

        changeButton->setDefault(false);


        QMetaObject::connectSlotsByName(toLogin);
    } // setupUi

    void retranslateUi(QWidget *toLogin)
    {
        toLogin->setWindowTitle(QApplication::translate("toLogin", "toLogin", Q_NULLPTR));
        groupBox->setTitle(QString());
        label_2->setText(QApplication::translate("toLogin", " \345\257\206\347\240\201\357\274\232", Q_NULLPTR));
        label->setText(QApplication::translate("toLogin", "\347\224\250\346\210\267\345\220\215\357\274\232", Q_NULLPTR));
        loginButton->setText(QApplication::translate("toLogin", "\347\231\273\345\275\225", Q_NULLPTR));
        changeButton->setText(QApplication::translate("toLogin", "\344\277\256\346\224\271\345\257\206\347\240\201", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("toLogin", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class toLogin: public Ui_toLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOLOGIN_H
