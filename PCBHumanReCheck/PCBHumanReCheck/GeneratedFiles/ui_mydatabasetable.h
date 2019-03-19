/********************************************************************************
** Form generated from reading UI file 'mydatabasetable.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYDATABASETABLE_H
#define UI_MYDATABASETABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_myDatabaseTable
{
public:
    QGridLayout *gridLayout_2;
    QTableView *dbTableView;
    QGridLayout *gridLayout;
    QPushButton *ascendButton;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *idEdit;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QLineEdit *dateEdit;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QLineEdit *resEdit;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *recallButton;
    QPushButton *submitButton;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *queryButton;
    QPushButton *showAllButton;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QLineEdit *regionEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QLineEdit *typeEdit;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_3;
    QLineEdit *toAddID;
    QFrame *line;
    QFrame *line_3;
    QFrame *line_2;
    QPushButton *descendButton;
    QPushButton *statisticButton;
    QFrame *line_4;
    QFrame *line_5;
    QFrame *line_6;

    void setupUi(QWidget *myDatabaseTable)
    {
        if (myDatabaseTable->objectName().isEmpty())
            myDatabaseTable->setObjectName(QStringLiteral("myDatabaseTable"));
        myDatabaseTable->resize(567, 489);
        gridLayout_2 = new QGridLayout(myDatabaseTable);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        dbTableView = new QTableView(myDatabaseTable);
        dbTableView->setObjectName(QStringLiteral("dbTableView"));
        dbTableView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        dbTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

        gridLayout_2->addWidget(dbTableView, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        ascendButton = new QPushButton(myDatabaseTable);
        ascendButton->setObjectName(QStringLiteral("ascendButton"));

        gridLayout->addWidget(ascendButton, 5, 2, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(myDatabaseTable);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        idEdit = new QLineEdit(myDatabaseTable);
        idEdit->setObjectName(QStringLiteral("idEdit"));

        horizontalLayout_2->addWidget(idEdit);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        addButton = new QPushButton(myDatabaseTable);
        addButton->setObjectName(QStringLiteral("addButton"));

        horizontalLayout_9->addWidget(addButton);

        deleteButton = new QPushButton(myDatabaseTable);
        deleteButton->setObjectName(QStringLiteral("deleteButton"));

        horizontalLayout_9->addWidget(deleteButton);


        gridLayout->addLayout(horizontalLayout_9, 3, 1, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_2 = new QLabel(myDatabaseTable);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_5->addWidget(label_2);

        dateEdit = new QLineEdit(myDatabaseTable);
        dateEdit->setObjectName(QStringLiteral("dateEdit"));

        horizontalLayout_5->addWidget(dateEdit);


        gridLayout->addLayout(horizontalLayout_5, 1, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_6 = new QLabel(myDatabaseTable);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_6->addWidget(label_6);

        resEdit = new QLineEdit(myDatabaseTable);
        resEdit->setObjectName(QStringLiteral("resEdit"));

        horizontalLayout_6->addWidget(resEdit);


        gridLayout->addLayout(horizontalLayout_6, 1, 1, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        recallButton = new QPushButton(myDatabaseTable);
        recallButton->setObjectName(QStringLiteral("recallButton"));

        horizontalLayout_10->addWidget(recallButton);

        submitButton = new QPushButton(myDatabaseTable);
        submitButton->setObjectName(QStringLiteral("submitButton"));

        horizontalLayout_10->addWidget(submitButton);


        gridLayout->addLayout(horizontalLayout_10, 3, 2, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        queryButton = new QPushButton(myDatabaseTable);
        queryButton->setObjectName(QStringLiteral("queryButton"));

        horizontalLayout_8->addWidget(queryButton);

        showAllButton = new QPushButton(myDatabaseTable);
        showAllButton->setObjectName(QStringLiteral("showAllButton"));

        horizontalLayout_8->addWidget(showAllButton);


        gridLayout->addLayout(horizontalLayout_8, 1, 2, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_5 = new QLabel(myDatabaseTable);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_4->addWidget(label_5);

        regionEdit = new QLineEdit(myDatabaseTable);
        regionEdit->setObjectName(QStringLiteral("regionEdit"));

        horizontalLayout_4->addWidget(regionEdit);


        gridLayout->addLayout(horizontalLayout_4, 0, 2, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_4 = new QLabel(myDatabaseTable);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_3->addWidget(label_4);

        typeEdit = new QLineEdit(myDatabaseTable);
        typeEdit->setObjectName(QStringLiteral("typeEdit"));

        horizontalLayout_3->addWidget(typeEdit);


        gridLayout->addLayout(horizontalLayout_3, 0, 1, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_3 = new QLabel(myDatabaseTable);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_7->addWidget(label_3);

        toAddID = new QLineEdit(myDatabaseTable);
        toAddID->setObjectName(QStringLiteral("toAddID"));

        horizontalLayout_7->addWidget(toAddID);


        gridLayout->addLayout(horizontalLayout_7, 3, 0, 1, 1);

        line = new QFrame(myDatabaseTable);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 2, 0, 1, 1);

        line_3 = new QFrame(myDatabaseTable);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_3, 2, 2, 1, 1);

        line_2 = new QFrame(myDatabaseTable);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 2, 1, 1, 1);

        descendButton = new QPushButton(myDatabaseTable);
        descendButton->setObjectName(QStringLiteral("descendButton"));

        gridLayout->addWidget(descendButton, 5, 1, 1, 1);

        statisticButton = new QPushButton(myDatabaseTable);
        statisticButton->setObjectName(QStringLiteral("statisticButton"));

        gridLayout->addWidget(statisticButton, 5, 0, 1, 1);

        line_4 = new QFrame(myDatabaseTable);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_4, 4, 0, 1, 1);

        line_5 = new QFrame(myDatabaseTable);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_5, 4, 1, 1, 1);

        line_6 = new QFrame(myDatabaseTable);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_6, 4, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 1);


        retranslateUi(myDatabaseTable);

        QMetaObject::connectSlotsByName(myDatabaseTable);
    } // setupUi

    void retranslateUi(QWidget *myDatabaseTable)
    {
        myDatabaseTable->setWindowTitle(QApplication::translate("myDatabaseTable", "myDatabaseTable", Q_NULLPTR));
        ascendButton->setText(QApplication::translate("myDatabaseTable", "\345\215\207\345\272\217\346\216\222\345\210\227", Q_NULLPTR));
        label->setText(QApplication::translate("myDatabaseTable", " PCB ID ", Q_NULLPTR));
        addButton->setText(QApplication::translate("myDatabaseTable", "\346\267\273\345\212\240", Q_NULLPTR));
        deleteButton->setText(QApplication::translate("myDatabaseTable", "\345\210\240\351\231\244", Q_NULLPTR));
        label_2->setText(QApplication::translate("myDatabaseTable", "\346\243\200\346\265\213\346\227\245\346\234\237", Q_NULLPTR));
        label_6->setText(QApplication::translate("myDatabaseTable", "\346\243\200\346\265\213\347\273\223\346\236\234", Q_NULLPTR));
        recallButton->setText(QApplication::translate("myDatabaseTable", "\346\222\244\345\233\236", Q_NULLPTR));
        submitButton->setText(QApplication::translate("myDatabaseTable", "\346\217\220\344\272\244", Q_NULLPTR));
        queryButton->setText(QApplication::translate("myDatabaseTable", "\346\237\245\350\257\242", Q_NULLPTR));
        showAllButton->setText(QApplication::translate("myDatabaseTable", "\346\230\276\347\244\272\345\205\250\351\203\250", Q_NULLPTR));
        label_5->setText(QApplication::translate("myDatabaseTable", "\345\214\272\345\237\237ID", Q_NULLPTR));
        label_4->setText(QApplication::translate("myDatabaseTable", " \350\275\275\345\205\267ID ", Q_NULLPTR));
        label_3->setText(QApplication::translate("myDatabaseTable", " PCB ID ", Q_NULLPTR));
        descendButton->setText(QApplication::translate("myDatabaseTable", "\351\231\215\345\272\217\346\216\222\345\210\227", Q_NULLPTR));
        statisticButton->setText(QApplication::translate("myDatabaseTable", "\346\230\276\347\244\272\347\273\237\350\256\241\345\233\276", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class myDatabaseTable: public Ui_myDatabaseTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYDATABASETABLE_H
