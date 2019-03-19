/********************************************************************************
** Form generated from reading UI file 'mystatisticpic.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYSTATISTICPIC_H
#define UI_MYSTATISTICPIC_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qchartview.h>

QT_BEGIN_NAMESPACE

class Ui_myStatisticPic
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QChartView *pieToday;
    QChartView *pieWhole;
    QChartView *lineChart;

    void setupUi(QWidget *myStatisticPic)
    {
        if (myStatisticPic->objectName().isEmpty())
            myStatisticPic->setObjectName(QStringLiteral("myStatisticPic"));
        myStatisticPic->resize(400, 300);
        verticalLayout_2 = new QVBoxLayout(myStatisticPic);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pieToday = new QChartView(myStatisticPic);
        pieToday->setObjectName(QStringLiteral("pieToday"));

        horizontalLayout->addWidget(pieToday);

        pieWhole = new QChartView(myStatisticPic);
        pieWhole->setObjectName(QStringLiteral("pieWhole"));

        horizontalLayout->addWidget(pieWhole);


        verticalLayout_2->addLayout(horizontalLayout);

        lineChart = new QChartView(myStatisticPic);
        lineChart->setObjectName(QStringLiteral("lineChart"));

        verticalLayout_2->addWidget(lineChart);


        retranslateUi(myStatisticPic);

        QMetaObject::connectSlotsByName(myStatisticPic);
    } // setupUi

    void retranslateUi(QWidget *myStatisticPic)
    {
        myStatisticPic->setWindowTitle(QApplication::translate("myStatisticPic", "myStatisticPic", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class myStatisticPic: public Ui_myStatisticPic {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYSTATISTICPIC_H
