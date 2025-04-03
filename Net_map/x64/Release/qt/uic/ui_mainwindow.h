/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
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

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNouvellePage;
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page1;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_3;
    QLabel *imageLabel;
    QWidget *widgetContainer;
    QVBoxLayout *verticalLayout_2;
    QProgressBar *progressBar;
    QPushButton *pushButtonImage;
    QWidget *page2;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents;
    QWidget *widget;
    QTableWidget *tableWidget;
    QMenuBar *menubar;
    QMenu *menuNetMap;
    QMenu *menuEquipement;
    QMenu *menuDevices;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1007, 554);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionNouvellePage = new QAction(MainWindow);
        actionNouvellePage->setObjectName("actionNouvellePage");
        actionNouvellePage->setMenuRole(QAction::MenuRole::NoRole);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setMinimumSize(QSize(1007, 511));
        centralwidget->setMaximumSize(QSize(1007, 511));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 0, 1001, 511));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy1);
        page1 = new QWidget();
        page1->setObjectName("page1");
        scrollArea = new QScrollArea(page1);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(0, 10, 1001, 451));
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(3);
        sizePolicy2.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy2);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOn);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOn);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName("scrollAreaWidgetContents_3");
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 985, 435));
        sizePolicy.setHeightForWidth(scrollAreaWidgetContents_3->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents_3->setSizePolicy(sizePolicy);
        scrollAreaWidgetContents_3->setMinimumSize(QSize(0, 0));
        scrollAreaWidgetContents_3->setAutoFillBackground(true);
        imageLabel = new QLabel(scrollAreaWidgetContents_3);
        imageLabel->setObjectName("imageLabel");
        imageLabel->setGeometry(QRect(1220, 80, 903, 425));
        sizePolicy1.setHeightForWidth(imageLabel->sizePolicy().hasHeightForWidth());
        imageLabel->setSizePolicy(sizePolicy1);
        imageLabel->setMinimumSize(QSize(0, 0));
        imageLabel->setScaledContents(false);
        imageLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        widgetContainer = new QWidget(scrollAreaWidgetContents_3);
        widgetContainer->setObjectName("widgetContainer");
        widgetContainer->setGeometry(QRect(20, 0, 931, 164));
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(widgetContainer->sizePolicy().hasHeightForWidth());
        widgetContainer->setSizePolicy(sizePolicy3);
        widgetContainer->setMinimumSize(QSize(0, 164));
        widgetContainer->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        verticalLayout_2 = new QVBoxLayout(widgetContainer);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        progressBar = new QProgressBar(widgetContainer);
        progressBar->setObjectName("progressBar");
        progressBar->setEnabled(true);
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy4);
        progressBar->setValue(24);

        verticalLayout_2->addWidget(progressBar);

        pushButtonImage = new QPushButton(widgetContainer);
        pushButtonImage->setObjectName("pushButtonImage");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(pushButtonImage->sizePolicy().hasHeightForWidth());
        pushButtonImage->setSizePolicy(sizePolicy5);
        pushButtonImage->setMinimumSize(QSize(100, 30));

        verticalLayout_2->addWidget(pushButtonImage);

        scrollArea->setWidget(scrollAreaWidgetContents_3);
        stackedWidget->addWidget(page1);
        page2 = new QWidget();
        page2->setObjectName("page2");
        scrollArea_2 = new QScrollArea(page2);
        scrollArea_2->setObjectName("scrollArea_2");
        scrollArea_2->setGeometry(QRect(0, 0, 1001, 511));
        scrollArea_2->setMaximumSize(QSize(16777215, 16777215));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 999, 509));
        widget = new QWidget(scrollAreaWidgetContents);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 0, 981, 751));
        tableWidget = new QTableWidget(widget);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 981, 441));
        scrollArea_2->setWidget(scrollAreaWidgetContents);
        stackedWidget->addWidget(page2);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1007, 21));
        menuNetMap = new QMenu(menubar);
        menuNetMap->setObjectName("menuNetMap");
        menuEquipement = new QMenu(menubar);
        menuEquipement->setObjectName("menuEquipement");
        menuDevices = new QMenu(menubar);
        menuDevices->setObjectName("menuDevices");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuNetMap->menuAction());
        menubar->addAction(menuEquipement->menuAction());
        menubar->addAction(menuDevices->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionNouvellePage->setText(QCoreApplication::translate("MainWindow", "NouvellePage", nullptr));
        imageLabel->setText(QString());
        pushButtonImage->setText(QCoreApplication::translate("MainWindow", "Scanner le r\303\251seau", nullptr));
        menuNetMap->setTitle(QCoreApplication::translate("MainWindow", "NetMap", nullptr));
        menuEquipement->setTitle(QCoreApplication::translate("MainWindow", "Equipement", nullptr));
        menuDevices->setTitle(QCoreApplication::translate("MainWindow", "Devices", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
