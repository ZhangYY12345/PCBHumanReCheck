/********************************************************************************
** Form generated from reading UI file 'mymainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYMAINWINDOW_H
#define UI_MYMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "abview.h"

QT_BEGIN_NAMESPACE

class Ui_myMainWindow
{
public:
    QAction *actLogin;
    QAction *actionSetPathToMES;
    QAction *actSettings;
    QAction *actViewDatabase;
    QAction *actionNewDB;
    QAction *actionOKAuto;
    QAction *actionOKNotAuto;
    QAction *actionSetResFilePath;
    QAction *actionSetARdb;
    QAction *actionOpenMRdb;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    abView *imgShowWin;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout;
    QLabel *label_18;
    QLabel *resultToMESPathLab;
    QToolButton *setResPathToMESBt;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QLineEdit *onePCBID;
    QLabel *label_3;
    QComboBox *viewIDComBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QComboBox *widthErrCon;
    QLabel *label_4;
    QLineEdit *toConnectIP;
    QSpacerItem *horizontalSpacer;
    QPushButton *revokeBt;
    QPushButton *saveBt;
    QVBoxLayout *verticalLayout;
    QTableView *carrierAutoResTableView;
    QTableView *carrierManuResTableView;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menuOpen_database;
    QMenu *menu_2;
    QMenu *menuSetModel;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *myMainWindow)
    {
        if (myMainWindow->objectName().isEmpty())
            myMainWindow->setObjectName(QStringLiteral("myMainWindow"));
        myMainWindow->resize(1064, 640);
        actLogin = new QAction(myMainWindow);
        actLogin->setObjectName(QStringLiteral("actLogin"));
        actLogin->setCheckable(true);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/images/login.png"), QSize(), QIcon::Normal, QIcon::Off);
        actLogin->setIcon(icon);
        actionSetPathToMES = new QAction(myMainWindow);
        actionSetPathToMES->setObjectName(QStringLiteral("actionSetPathToMES"));
        actSettings = new QAction(myMainWindow);
        actSettings->setObjectName(QStringLiteral("actSettings"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/images/setting.png"), QSize(), QIcon::Normal, QIcon::Off);
        actSettings->setIcon(icon1);
        actViewDatabase = new QAction(myMainWindow);
        actViewDatabase->setObjectName(QStringLiteral("actViewDatabase"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/images/view_database.png"), QSize(), QIcon::Normal, QIcon::Off);
        actViewDatabase->setIcon(icon2);
        actionNewDB = new QAction(myMainWindow);
        actionNewDB->setObjectName(QStringLiteral("actionNewDB"));
        actionOKAuto = new QAction(myMainWindow);
        actionOKAuto->setObjectName(QStringLiteral("actionOKAuto"));
        actionOKAuto->setCheckable(true);
        actionOKNotAuto = new QAction(myMainWindow);
        actionOKNotAuto->setObjectName(QStringLiteral("actionOKNotAuto"));
        actionOKNotAuto->setCheckable(true);
        actionSetResFilePath = new QAction(myMainWindow);
        actionSetResFilePath->setObjectName(QStringLiteral("actionSetResFilePath"));
        actionSetARdb = new QAction(myMainWindow);
        actionSetARdb->setObjectName(QStringLiteral("actionSetARdb"));
        actionOpenMRdb = new QAction(myMainWindow);
        actionOpenMRdb->setObjectName(QStringLiteral("actionOpenMRdb"));
        centralWidget = new QWidget(myMainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        imgShowWin = new abView(centralWidget);
        imgShowWin->setObjectName(QStringLiteral("imgShowWin"));

        gridLayout->addWidget(imgShowWin, 3, 1, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_4, 3, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_18 = new QLabel(centralWidget);
        label_18->setObjectName(QStringLiteral("label_18"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
        label_18->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        label_18->setFont(font);

        horizontalLayout->addWidget(label_18);

        resultToMESPathLab = new QLabel(centralWidget);
        resultToMESPathLab->setObjectName(QStringLiteral("resultToMESPathLab"));
        resultToMESPathLab->setFont(font);
        resultToMESPathLab->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(resultToMESPathLab);

        setResPathToMESBt = new QToolButton(centralWidget);
        setResPathToMESBt->setObjectName(QStringLiteral("setResPathToMESBt"));

        horizontalLayout->addWidget(setResPathToMESBt);


        gridLayout->addLayout(horizontalLayout, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 4, 1, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setFont(font);

        horizontalLayout_4->addWidget(label);

        onePCBID = new QLineEdit(centralWidget);
        onePCBID->setObjectName(QStringLiteral("onePCBID"));
        onePCBID->setFont(font);
        onePCBID->setAcceptDrops(true);
        onePCBID->setFrame(true);

        horizontalLayout_4->addWidget(onePCBID);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_4->addWidget(label_3);

        viewIDComBox = new QComboBox(centralWidget);
        viewIDComBox->setObjectName(QStringLiteral("viewIDComBox"));

        horizontalLayout_4->addWidget(viewIDComBox);


        gridLayout->addLayout(horizontalLayout_4, 0, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        horizontalLayout_3->addWidget(label_2);

        widthErrCon = new QComboBox(centralWidget);
        widthErrCon->setObjectName(QStringLiteral("widthErrCon"));
        widthErrCon->setFont(font);

        horizontalLayout_3->addWidget(widthErrCon);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);

        horizontalLayout_3->addWidget(label_4);

        toConnectIP = new QLineEdit(centralWidget);
        toConnectIP->setObjectName(QStringLiteral("toConnectIP"));
        toConnectIP->setFont(font);
        toConnectIP->setFrame(false);
        toConnectIP->setCursorPosition(0);
        toConnectIP->setCursorMoveStyle(Qt::VisualMoveStyle);

        horizontalLayout_3->addWidget(toConnectIP);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        revokeBt = new QPushButton(centralWidget);
        revokeBt->setObjectName(QStringLiteral("revokeBt"));

        horizontalLayout_3->addWidget(revokeBt);

        saveBt = new QPushButton(centralWidget);
        saveBt->setObjectName(QStringLiteral("saveBt"));

        horizontalLayout_3->addWidget(saveBt);


        gridLayout->addLayout(horizontalLayout_3, 2, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        carrierAutoResTableView = new QTableView(centralWidget);
        carrierAutoResTableView->setObjectName(QStringLiteral("carrierAutoResTableView"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(carrierAutoResTableView->sizePolicy().hasHeightForWidth());
        carrierAutoResTableView->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(carrierAutoResTableView);

        carrierManuResTableView = new QTableView(centralWidget);
        carrierManuResTableView->setObjectName(QStringLiteral("carrierManuResTableView"));
        sizePolicy1.setHeightForWidth(carrierManuResTableView->sizePolicy().hasHeightForWidth());
        carrierManuResTableView->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(carrierManuResTableView);


        horizontalLayout_2->addLayout(verticalLayout);

        myMainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(myMainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1064, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menuOpen_database = new QMenu(menu);
        menuOpen_database->setObjectName(QStringLiteral("menuOpen_database"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menuSetModel = new QMenu(menu_2);
        menuSetModel->setObjectName(QStringLiteral("menuSetModel"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        myMainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(myMainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        myMainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(myMainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        myMainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menu->addAction(actionNewDB);
        menu->addAction(menuOpen_database->menuAction());
        menuOpen_database->addAction(actionSetARdb);
        menuOpen_database->addAction(actionOpenMRdb);
        menu_2->addAction(actionSetPathToMES);
        menu_2->addAction(actionSetResFilePath);
        menu_2->addAction(menuSetModel->menuAction());
        menuSetModel->addAction(actionOKAuto);
        menuSetModel->addAction(actionOKNotAuto);
        mainToolBar->addAction(actLogin);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actSettings);
        mainToolBar->addAction(actViewDatabase);

        retranslateUi(myMainWindow);

        QMetaObject::connectSlotsByName(myMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *myMainWindow)
    {
        myMainWindow->setWindowTitle(QApplication::translate("myMainWindow", "myMainWindow", Q_NULLPTR));
        actLogin->setText(QApplication::translate("myMainWindow", "\347\231\273\345\275\225", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actLogin->setToolTip(QApplication::translate("myMainWindow", "Login/Logout", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionSetPathToMES->setText(QApplication::translate("myMainWindow", "\350\256\276\347\275\256MES\351\200\232\344\277\241\346\226\207\344\273\266\345\244\271\350\267\257\345\276\204", Q_NULLPTR));
        actSettings->setText(QApplication::translate("myMainWindow", "\350\256\276\347\275\256", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actSettings->setToolTip(QApplication::translate("myMainWindow", "Setting path and model", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actViewDatabase->setText(QApplication::translate("myMainWindow", "\346\225\260\346\215\256\345\272\223\350\247\206\345\233\276", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actViewDatabase->setToolTip(QApplication::translate("myMainWindow", "view database", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionNewDB->setText(QApplication::translate("myMainWindow", "\346\226\260\345\273\272\344\272\272\345\267\245\345\244\215\346\243\200\346\225\260\346\215\256\345\272\223", Q_NULLPTR));
        actionOKAuto->setText(QApplication::translate("myMainWindow", "\345\244\215\346\243\200\350\207\252\345\212\250\346\243\200\346\265\213\344\270\272\345\220\210\346\240\274\347\232\204\344\272\247\345\223\201", Q_NULLPTR));
        actionOKNotAuto->setText(QApplication::translate("myMainWindow", "\344\270\215\345\244\215\346\243\200\350\207\252\345\212\250\346\243\200\346\265\213\344\270\272\345\220\210\346\240\274\347\232\204\344\272\247\345\223\201", Q_NULLPTR));
        actionSetResFilePath->setText(QApplication::translate("myMainWindow", "\350\256\276\347\275\256TXT\346\226\207\344\273\266\345\255\230\345\202\250\350\267\257\345\276\204", Q_NULLPTR));
        actionSetARdb->setText(QApplication::translate("myMainWindow", "\350\256\276\347\275\256\350\207\252\345\212\250\346\243\200\346\265\213\346\225\260\346\215\256\345\272\223\346\226\207\344\273\266", Q_NULLPTR));
        actionOpenMRdb->setText(QApplication::translate("myMainWindow", "\346\211\223\345\274\200\344\272\272\345\267\245\351\231\204\344\273\266\347\273\223\346\236\234\346\225\260\346\215\256\345\272\223", Q_NULLPTR));
        label_18->setText(QApplication::translate("myMainWindow", "\344\270\216MES\351\200\232\344\277\241\346\226\207\344\273\266\345\244\271\350\267\257\345\276\204:", Q_NULLPTR));
        resultToMESPathLab->setText(QString());
        setResPathToMESBt->setText(QApplication::translate("myMainWindow", "...", Q_NULLPTR));
        label->setText(QApplication::translate("myMainWindow", "\345\215\225\344\270\252PCBID\357\274\232", Q_NULLPTR));
        onePCBID->setText(QString());
        label_3->setText(QApplication::translate("myMainWindow", "\345\214\272\345\237\237ID", Q_NULLPTR));
        label_2->setText(QApplication::translate("myMainWindow", "\346\212\245\350\255\246\345\214\272\345\237\237\350\275\256\345\273\223\346\230\276\347\244\272\347\272\277\345\256\275", Q_NULLPTR));
        widthErrCon->clear();
        widthErrCon->insertItems(0, QStringList()
         << QApplication::translate("myMainWindow", "1", Q_NULLPTR)
         << QApplication::translate("myMainWindow", "2", Q_NULLPTR)
         << QApplication::translate("myMainWindow", "3", Q_NULLPTR)
         << QApplication::translate("myMainWindow", "4", Q_NULLPTR)
         << QApplication::translate("myMainWindow", "5", Q_NULLPTR)
         << QApplication::translate("myMainWindow", "6", Q_NULLPTR)
         << QApplication::translate("myMainWindow", "7", Q_NULLPTR)
         << QApplication::translate("myMainWindow", "8", Q_NULLPTR)
        );
        widthErrCon->setCurrentText(QApplication::translate("myMainWindow", "1", Q_NULLPTR));
        label_4->setText(QApplication::translate("myMainWindow", "\351\200\232\344\277\241\350\256\241\347\256\227\346\234\272IP", Q_NULLPTR));
        toConnectIP->setInputMask(QApplication::translate("myMainWindow", "000.000.000.000", Q_NULLPTR));
        revokeBt->setText(QApplication::translate("myMainWindow", "\346\222\244\351\224\200\344\277\256\346\224\271", Q_NULLPTR));
        saveBt->setText(QApplication::translate("myMainWindow", "\344\277\235\345\255\230\344\277\256\346\224\271", Q_NULLPTR));
        menu->setTitle(QApplication::translate("myMainWindow", "\346\226\207\344\273\266", Q_NULLPTR));
        menuOpen_database->setTitle(QApplication::translate("myMainWindow", "\346\211\223\345\274\200\346\225\260\346\215\256\345\272\223", Q_NULLPTR));
        menu_2->setTitle(QApplication::translate("myMainWindow", "\350\256\276\347\275\256", Q_NULLPTR));
        menuSetModel->setTitle(QApplication::translate("myMainWindow", "\350\256\276\347\275\256\345\244\215\346\243\200\346\250\241\345\274\217", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("myMainWindow", "\345\270\256\345\212\251", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class myMainWindow: public Ui_myMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYMAINWINDOW_H
