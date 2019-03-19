/********************************************************************************
** Form generated from reading UI file 'tochangepassword.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOCHANGEPASSWORD_H
#define UI_TOCHANGEPASSWORD_H

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

class Ui_toChangePassword
{
public:
    QGroupBox *groupBox;
    QLabel *label_2;
    QLineEdit *oldPassword;
    QLineEdit *userNmae;
    QLabel *label;
    QLabel *label_3;
    QLineEdit *newPassword;
    QLabel *label_4;
    QLineEdit *sureNewPassword;
    QPushButton *changeButton;
    QPushButton *cancelButton;

    void setupUi(QWidget *toChangePassword)
    {
        if (toChangePassword->objectName().isEmpty())
            toChangePassword->setObjectName(QStringLiteral("toChangePassword"));
        toChangePassword->resize(382, 300);
        groupBox = new QGroupBox(toChangePassword);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(40, 20, 301, 191));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 60, 54, 21));
        oldPassword = new QLineEdit(groupBox);
        oldPassword->setObjectName(QStringLiteral("oldPassword"));
        oldPassword->setGeometry(QRect(90, 60, 181, 21));
        oldPassword->setInputMask(QStringLiteral(""));
        oldPassword->setText(QStringLiteral(""));
        oldPassword->setFrame(true);
        oldPassword->setEchoMode(QLineEdit::Password);
        oldPassword->setCursorPosition(0);
        userNmae = new QLineEdit(groupBox);
        userNmae->setObjectName(QStringLiteral("userNmae"));
        userNmae->setGeometry(QRect(90, 20, 181, 21));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 22, 54, 20));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(40, 100, 54, 21));
        newPassword = new QLineEdit(groupBox);
        newPassword->setObjectName(QStringLiteral("newPassword"));
        newPassword->setGeometry(QRect(90, 100, 181, 21));
        newPassword->setInputMask(QStringLiteral(""));
        newPassword->setText(QStringLiteral(""));
        newPassword->setFrame(true);
        newPassword->setEchoMode(QLineEdit::Password);
        newPassword->setCursorPosition(0);
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 140, 71, 21));
        sureNewPassword = new QLineEdit(groupBox);
        sureNewPassword->setObjectName(QStringLiteral("sureNewPassword"));
        sureNewPassword->setGeometry(QRect(90, 140, 181, 21));
        sureNewPassword->setInputMask(QStringLiteral(""));
        sureNewPassword->setText(QStringLiteral(""));
        sureNewPassword->setFrame(true);
        sureNewPassword->setEchoMode(QLineEdit::Password);
        sureNewPassword->setCursorPosition(0);
        changeButton = new QPushButton(toChangePassword);
        changeButton->setObjectName(QStringLiteral("changeButton"));
        changeButton->setGeometry(QRect(90, 240, 75, 23));
        cancelButton = new QPushButton(toChangePassword);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setGeometry(QRect(220, 240, 75, 23));

        retranslateUi(toChangePassword);

        QMetaObject::connectSlotsByName(toChangePassword);
    } // setupUi

    void retranslateUi(QWidget *toChangePassword)
    {
        toChangePassword->setWindowTitle(QApplication::translate("toChangePassword", "toChangePassword", Q_NULLPTR));
        groupBox->setTitle(QString());
        label_2->setText(QApplication::translate("toChangePassword", "\345\216\237\345\257\206\347\240\201\357\274\232", Q_NULLPTR));
        label->setText(QApplication::translate("toChangePassword", "\347\224\250\346\210\267\345\220\215\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("toChangePassword", "\346\226\260\345\257\206\347\240\201\357\274\232", Q_NULLPTR));
        label_4->setText(QApplication::translate("toChangePassword", " \346\226\260\345\257\206\347\240\201\347\241\256\350\256\244\357\274\232", Q_NULLPTR));
        changeButton->setText(QApplication::translate("toChangePassword", "\347\241\256\350\256\244\344\277\256\346\224\271", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("toChangePassword", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class toChangePassword: public Ui_toChangePassword {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOCHANGEPASSWORD_H
