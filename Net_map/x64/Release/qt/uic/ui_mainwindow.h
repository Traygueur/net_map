/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "customgraphicsview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNouvellePage;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QStackedWidget *stackedWidget;
    QWidget *page1;
    QVBoxLayout *verticalLayout_5;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_3;
    QVBoxLayout *verticalLayout_4;
    QWidget *widgetContainer;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QProgressBar *progressBar;
    QLabel *labelStep;
    QLineEdit *lineEdit;
    QPushButton *pushButtonImage;
    CustomGraphicsView *graphicsView;
    QWidget *page2;
    QVBoxLayout *verticalLayout_6;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_7;
    QWidget *widget;
    QVBoxLayout *verticalLayout_8;
    QTableWidget *tableWidget;
    QWidget *page3;
    QVBoxLayout *verticalLayout_9;
    QScrollArea *scrollArea_3;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_10;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_11;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBoxClosed;
    QCheckBox *checkBoxFiltered;
    QCheckBox *checkBoxOpen;
    QTableWidget *tableWidget_2;
    QMenuBar *menubar;
    QMenu *menuNetMap;
    QMenu *menuDevices;
    QMenu *menuSecurity;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(690, 600);
        actionNouvellePage = new QAction(MainWindow);
        actionNouvellePage->setObjectName("actionNouvellePage");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        page1 = new QWidget();
        page1->setObjectName("page1");
        verticalLayout_5 = new QVBoxLayout(page1);
        verticalLayout_5->setObjectName("verticalLayout_5");
        scrollArea = new QScrollArea(page1);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName("scrollAreaWidgetContents_3");
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 652, 519));
        verticalLayout_4 = new QVBoxLayout(scrollAreaWidgetContents_3);
        verticalLayout_4->setObjectName("verticalLayout_4");
        widgetContainer = new QWidget(scrollAreaWidgetContents_3);
        widgetContainer->setObjectName("widgetContainer");
        verticalLayout_2 = new QVBoxLayout(widgetContainer);
        verticalLayout_2->setObjectName("verticalLayout_2");
        frame = new QFrame(widgetContainer);
        frame->setObjectName("frame");
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName("verticalLayout");
        progressBar = new QProgressBar(frame);
        progressBar->setObjectName("progressBar");
        progressBar->setMinimumSize(QSize(500, 32));
        progressBar->setValue(26);

        verticalLayout->addWidget(progressBar);

        labelStep = new QLabel(frame);
        labelStep->setObjectName("labelStep");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelStep->sizePolicy().hasHeightForWidth());
        labelStep->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(labelStep);

        lineEdit = new QLineEdit(frame);
        lineEdit->setObjectName("lineEdit");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy2);
        lineEdit->setMinimumSize(QSize(0, 0));
        lineEdit->setMaximumSize(QSize(200, 16777215));

        verticalLayout->addWidget(lineEdit);

        pushButtonImage = new QPushButton(frame);
        pushButtonImage->setObjectName("pushButtonImage");
        sizePolicy1.setHeightForWidth(pushButtonImage->sizePolicy().hasHeightForWidth());
        pushButtonImage->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(pushButtonImage);


        verticalLayout_2->addWidget(frame);

        graphicsView = new CustomGraphicsView(widgetContainer);
        graphicsView->setObjectName("graphicsView");

        verticalLayout_2->addWidget(graphicsView);


        verticalLayout_4->addWidget(widgetContainer);

        scrollArea->setWidget(scrollAreaWidgetContents_3);

        verticalLayout_5->addWidget(scrollArea);

        stackedWidget->addWidget(page1);
        page2 = new QWidget();
        page2->setObjectName("page2");
        verticalLayout_6 = new QVBoxLayout(page2);
        verticalLayout_6->setObjectName("verticalLayout_6");
        scrollArea_2 = new QScrollArea(page2);
        scrollArea_2->setObjectName("scrollArea_2");
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 106, 106));
        sizePolicy.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy);
        verticalLayout_7 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_7->setObjectName("verticalLayout_7");
        widget = new QWidget(scrollAreaWidgetContents);
        widget->setObjectName("widget");
        verticalLayout_8 = new QVBoxLayout(widget);
        verticalLayout_8->setObjectName("verticalLayout_8");
        tableWidget = new QTableWidget(widget);
        tableWidget->setObjectName("tableWidget");

        verticalLayout_8->addWidget(tableWidget);


        verticalLayout_7->addWidget(widget);

        scrollArea_2->setWidget(scrollAreaWidgetContents);

        verticalLayout_6->addWidget(scrollArea_2);

        stackedWidget->addWidget(page2);
        page3 = new QWidget();
        page3->setObjectName("page3");
        verticalLayout_9 = new QVBoxLayout(page3);
        verticalLayout_9->setObjectName("verticalLayout_9");
        scrollArea_3 = new QScrollArea(page3);
        scrollArea_3->setObjectName("scrollArea_3");
        scrollArea_3->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName("scrollAreaWidgetContents_2");
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 652, 519));
        verticalLayout_10 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_10->setObjectName("verticalLayout_10");
        widget_2 = new QWidget(scrollAreaWidgetContents_2);
        widget_2->setObjectName("widget_2");
        verticalLayout_11 = new QVBoxLayout(widget_2);
        verticalLayout_11->setObjectName("verticalLayout_11");
        widget_3 = new QWidget(widget_2);
        widget_3->setObjectName("widget_3");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy3);
        horizontalLayout = new QHBoxLayout(widget_3);
        horizontalLayout->setObjectName("horizontalLayout");
        checkBoxClosed = new QCheckBox(widget_3);
        checkBoxClosed->setObjectName("checkBoxClosed");
        checkBoxClosed->setChecked(true);

        horizontalLayout->addWidget(checkBoxClosed);

        checkBoxFiltered = new QCheckBox(widget_3);
        checkBoxFiltered->setObjectName("checkBoxFiltered");
        checkBoxFiltered->setChecked(true);

        horizontalLayout->addWidget(checkBoxFiltered);

        checkBoxOpen = new QCheckBox(widget_3);
        checkBoxOpen->setObjectName("checkBoxOpen");
        checkBoxOpen->setChecked(true);

        horizontalLayout->addWidget(checkBoxOpen);


        verticalLayout_11->addWidget(widget_3);

        tableWidget_2 = new QTableWidget(widget_2);
        tableWidget_2->setObjectName("tableWidget_2");

        verticalLayout_11->addWidget(tableWidget_2);


        verticalLayout_10->addWidget(widget_2);

        scrollArea_3->setWidget(scrollAreaWidgetContents_2);

        verticalLayout_9->addWidget(scrollArea_3);

        stackedWidget->addWidget(page3);

        verticalLayout_3->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 690, 21));
        menuNetMap = new QMenu(menubar);
        menuNetMap->setObjectName("menuNetMap");
        menuDevices = new QMenu(menubar);
        menuDevices->setObjectName("menuDevices");
        menuSecurity = new QMenu(menubar);
        menuSecurity->setObjectName("menuSecurity");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuNetMap->menuAction());
        menubar->addAction(menuDevices->menuAction());
        menubar->addAction(menuSecurity->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionNouvellePage->setText(QCoreApplication::translate("MainWindow", "NouvellePage", nullptr));
        labelStep->setText(QCoreApplication::translate("MainWindow", "\303\211tape 1/6", nullptr));
        lineEdit->setText(QCoreApplication::translate("MainWindow", "Mettre IP, ex : 192.168.1.0/24", nullptr));
        pushButtonImage->setText(QCoreApplication::translate("MainWindow", "Scanner le r\303\251seau", nullptr));
        checkBoxClosed->setText(QCoreApplication::translate("MainWindow", "Closed Port", nullptr));
        checkBoxFiltered->setText(QCoreApplication::translate("MainWindow", "Filtered Port", nullptr));
        checkBoxOpen->setText(QCoreApplication::translate("MainWindow", "Open Port", nullptr));
        menuNetMap->setTitle(QCoreApplication::translate("MainWindow", "NetMap", nullptr));
        menuDevices->setTitle(QCoreApplication::translate("MainWindow", "Devices", nullptr));
        menuSecurity->setTitle(QCoreApplication::translate("MainWindow", "Security", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
