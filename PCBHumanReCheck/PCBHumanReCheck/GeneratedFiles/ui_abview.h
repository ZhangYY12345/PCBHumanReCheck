/********************************************************************************
** Form generated from reading UI file 'abview.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABVIEW_H
#define UI_ABVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>
#include "picviewwindow.h"

QT_BEGIN_NAMESPACE

class Ui_abView
{
public:
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    PicViewWindow *picViewA;
    PicViewWindow *picViewB;

    void setupUi(QWidget *abView)
    {
        if (abView->objectName().isEmpty())
            abView->setObjectName(QStringLiteral("abView"));
        abView->resize(400, 300);
        horizontalLayout_2 = new QHBoxLayout(abView);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        picViewA = new PicViewWindow(abView);
        picViewA->setObjectName(QStringLiteral("picViewA"));

        horizontalLayout->addWidget(picViewA);

        picViewB = new PicViewWindow(abView);
        picViewB->setObjectName(QStringLiteral("picViewB"));

        horizontalLayout->addWidget(picViewB);


        horizontalLayout_2->addLayout(horizontalLayout);


        retranslateUi(abView);

        QMetaObject::connectSlotsByName(abView);
    } // setupUi

    void retranslateUi(QWidget *abView)
    {
        abView->setWindowTitle(QApplication::translate("abView", "abView", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class abView: public Ui_abView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABVIEW_H
