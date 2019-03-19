/********************************************************************************
** Form generated from reading UI file 'picviewwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PICVIEWWINDOW_H
#define UI_PICVIEWWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "mainwingraphview.h"

QT_BEGIN_NAMESPACE

class Ui_PicViewWindow
{
public:
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QLabel *imgInform;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QLabel *labelZoomOut;
    QSlider *zoomControl;
    QLabel *labelZoomIn;
    MainWinGraphView *graphicsView;

    void setupUi(QWidget *PicViewWindow)
    {
        if (PicViewWindow->objectName().isEmpty())
            PicViewWindow->setObjectName(QStringLiteral("PicViewWindow"));
        PicViewWindow->resize(570, 414);
        verticalLayout_2 = new QVBoxLayout(PicViewWindow);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        imgInform = new QLabel(PicViewWindow);
        imgInform->setObjectName(QStringLiteral("imgInform"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        imgInform->setFont(font);
        imgInform->setStyleSheet(QStringLiteral("background-color: rgb(174, 174, 174);"));
        imgInform->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(imgInform, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        labelZoomOut = new QLabel(PicViewWindow);
        labelZoomOut->setObjectName(QStringLiteral("labelZoomOut"));
        labelZoomOut->setTextFormat(Qt::RichText);
        labelZoomOut->setPixmap(QPixmap(QString::fromUtf8(":/images/images/zoomout.png")));
        labelZoomOut->setScaledContents(true);
        labelZoomOut->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(labelZoomOut);

        zoomControl = new QSlider(PicViewWindow);
        zoomControl->setObjectName(QStringLiteral("zoomControl"));
        zoomControl->setMaximum(800);
        zoomControl->setPageStep(10);
        zoomControl->setValue(400);
        zoomControl->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(zoomControl);

        labelZoomIn = new QLabel(PicViewWindow);
        labelZoomIn->setObjectName(QStringLiteral("labelZoomIn"));
        labelZoomIn->setTextFormat(Qt::RichText);
        labelZoomIn->setPixmap(QPixmap(QString::fromUtf8(":/images/images/zoomin.png")));
        labelZoomIn->setScaledContents(true);
        labelZoomIn->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(labelZoomIn);


        gridLayout->addLayout(horizontalLayout, 2, 1, 1, 1);

        graphicsView = new MainWinGraphView(PicViewWindow);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        gridLayout->addWidget(graphicsView, 1, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout);


        retranslateUi(PicViewWindow);

        QMetaObject::connectSlotsByName(PicViewWindow);
    } // setupUi

    void retranslateUi(QWidget *PicViewWindow)
    {
        PicViewWindow->setWindowTitle(QApplication::translate("PicViewWindow", "PicViewWindow", Q_NULLPTR));
        imgInform->setText(QString());
        labelZoomOut->setText(QString());
        labelZoomIn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PicViewWindow: public Ui_PicViewWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PICVIEWWINDOW_H
