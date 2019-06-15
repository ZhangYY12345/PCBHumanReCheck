/********************************************************************************
** Form generated from reading UI file 'mysettingwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYSETTINGWINDOW_H
#define UI_MYSETTINGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mySettingWindow
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_3;
    QLineEdit *toConnectIP;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_18;
    QLabel *setDatabaseAuto;
    QToolButton *setDatabaseAutoBt;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QLabel *setDatabaseManu;
    QToolButton *setDatabaseManuBt;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QLabel *setResToGetPath;
    QToolButton *setResToGetPathBt;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_19;
    QLabel *setResToMESPath;
    QToolButton *setResToMESPathBt;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_20;
    QSpacerItem *horizontalSpacer;
    QRadioButton *setModelBt;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *mySettingWindow)
    {
        if (mySettingWindow->objectName().isEmpty())
            mySettingWindow->setObjectName(QStringLiteral("mySettingWindow"));
        mySettingWindow->resize(1255, 503);
        verticalLayout_2 = new QVBoxLayout(mySettingWindow);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_3 = new QLabel(mySettingWindow);
        label_3->setObjectName(QStringLiteral("label_3"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        label_3->setFont(font);

        horizontalLayout_6->addWidget(label_3);

        toConnectIP = new QLineEdit(mySettingWindow);
        toConnectIP->setObjectName(QStringLiteral("toConnectIP"));
        toConnectIP->setFont(font);
        toConnectIP->setFrame(true);
        toConnectIP->setCursorMoveStyle(Qt::VisualMoveStyle);

        horizontalLayout_6->addWidget(toConnectIP);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_18 = new QLabel(mySettingWindow);
        label_18->setObjectName(QStringLiteral("label_18"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
        label_18->setSizePolicy(sizePolicy);
        label_18->setFont(font);

        horizontalLayout->addWidget(label_18);

        setDatabaseAuto = new QLabel(mySettingWindow);
        setDatabaseAuto->setObjectName(QStringLiteral("setDatabaseAuto"));
        setDatabaseAuto->setFont(font);
        setDatabaseAuto->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(setDatabaseAuto);

        setDatabaseAutoBt = new QToolButton(mySettingWindow);
        setDatabaseAutoBt->setObjectName(QStringLiteral("setDatabaseAutoBt"));

        horizontalLayout->addWidget(setDatabaseAutoBt);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_2 = new QLabel(mySettingWindow);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setFont(font);

        horizontalLayout_5->addWidget(label_2);

        setDatabaseManu = new QLabel(mySettingWindow);
        setDatabaseManu->setObjectName(QStringLiteral("setDatabaseManu"));
        setDatabaseManu->setFont(font);
        setDatabaseManu->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        horizontalLayout_5->addWidget(setDatabaseManu);

        setDatabaseManuBt = new QToolButton(mySettingWindow);
        setDatabaseManuBt->setObjectName(QStringLiteral("setDatabaseManuBt"));

        horizontalLayout_5->addWidget(setDatabaseManuBt);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label = new QLabel(mySettingWindow);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setFont(font);

        horizontalLayout_4->addWidget(label);

        setResToGetPath = new QLabel(mySettingWindow);
        setResToGetPath->setObjectName(QStringLiteral("setResToGetPath"));
        setResToGetPath->setFont(font);
        setResToGetPath->setAutoFillBackground(false);
        setResToGetPath->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        horizontalLayout_4->addWidget(setResToGetPath);

        setResToGetPathBt = new QToolButton(mySettingWindow);
        setResToGetPathBt->setObjectName(QStringLiteral("setResToGetPathBt"));

        horizontalLayout_4->addWidget(setResToGetPathBt);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_19 = new QLabel(mySettingWindow);
        label_19->setObjectName(QStringLiteral("label_19"));
        sizePolicy.setHeightForWidth(label_19->sizePolicy().hasHeightForWidth());
        label_19->setSizePolicy(sizePolicy);
        label_19->setFont(font);

        horizontalLayout_2->addWidget(label_19);

        setResToMESPath = new QLabel(mySettingWindow);
        setResToMESPath->setObjectName(QStringLiteral("setResToMESPath"));
        setResToMESPath->setFont(font);
        setResToMESPath->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        horizontalLayout_2->addWidget(setResToMESPath);

        setResToMESPathBt = new QToolButton(mySettingWindow);
        setResToMESPathBt->setObjectName(QStringLiteral("setResToMESPathBt"));

        horizontalLayout_2->addWidget(setResToMESPathBt);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_20 = new QLabel(mySettingWindow);
        label_20->setObjectName(QStringLiteral("label_20"));
        sizePolicy.setHeightForWidth(label_20->sizePolicy().hasHeightForWidth());
        label_20->setSizePolicy(sizePolicy);
        label_20->setFont(font);

        horizontalLayout_3->addWidget(label_20);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        setModelBt = new QRadioButton(mySettingWindow);
        setModelBt->setObjectName(QStringLiteral("setModelBt"));

        horizontalLayout_3->addWidget(setModelBt);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_3);


        retranslateUi(mySettingWindow);

        QMetaObject::connectSlotsByName(mySettingWindow);
    } // setupUi

    void retranslateUi(QWidget *mySettingWindow)
    {
        mySettingWindow->setWindowTitle(QApplication::translate("mySettingWindow", "mySettingWindow", Q_NULLPTR));
        label_3->setText(QApplication::translate("mySettingWindow", "\350\207\252\345\212\250\346\243\200\346\265\213\347\273\223\346\236\234\346\211\200\345\234\250\350\256\241\347\256\227\346\234\272IP:", Q_NULLPTR));
        toConnectIP->setInputMask(QApplication::translate("mySettingWindow", "000.000.000.000", Q_NULLPTR));
        label_18->setText(QApplication::translate("mySettingWindow", "\350\207\252\345\212\250\346\243\200\346\265\213\347\273\223\346\236\234\346\225\260\346\215\256\345\272\223\346\226\207\344\273\266\357\274\232", Q_NULLPTR));
        setDatabaseAuto->setText(QString());
        setDatabaseAutoBt->setText(QApplication::translate("mySettingWindow", "...", Q_NULLPTR));
        label_2->setText(QApplication::translate("mySettingWindow", "\344\272\272\345\267\245\345\244\215\346\243\200\346\243\200\346\265\213\346\225\260\346\215\256\345\272\223\346\226\207\344\273\266\357\274\232", Q_NULLPTR));
        setDatabaseManu->setText(QString());
        setDatabaseManuBt->setText(QApplication::translate("mySettingWindow", "...", Q_NULLPTR));
        label->setText(QApplication::translate("mySettingWindow", "\346\211\200\346\234\211TXT\345\255\230\345\202\250\346\226\207\344\273\266\345\244\271\350\267\257\345\276\204\357\274\232", Q_NULLPTR));
        setResToGetPath->setText(QString());
        setResToGetPathBt->setText(QApplication::translate("mySettingWindow", "...", Q_NULLPTR));
        label_19->setText(QApplication::translate("mySettingWindow", "MES\351\200\232\344\277\241TXT\346\226\207\344\273\266\345\255\230\345\202\250\350\267\257\345\276\204", Q_NULLPTR));
        setResToMESPath->setText(QString());
        setResToMESPathBt->setText(QApplication::translate("mySettingWindow", "...", Q_NULLPTR));
        label_20->setText(QApplication::translate("mySettingWindow", "\345\244\215\346\243\200\346\250\241\345\274\217\357\274\232", Q_NULLPTR));
        setModelBt->setText(QApplication::translate("mySettingWindow", "\345\244\215\346\243\200\350\207\252\345\212\250\346\243\200\346\265\213\344\270\272\345\220\210\346\240\274\347\232\204\344\272\247\345\223\201", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class mySettingWindow: public Ui_mySettingWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYSETTINGWINDOW_H
