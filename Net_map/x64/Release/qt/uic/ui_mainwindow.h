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
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
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
    QWidget *widgetContainer;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButtonImage;
    QLabel *imageLabel;
    QWidget *page2;
    QMenuBar *menubar;
    QMenu *menuNetMap;
    QMenu *menuEquipement;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1007, 561);
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
        stackedWidget->setGeometry(QRect(0, 0, 991, 451));
        page1 = new QWidget();
        page1->setObjectName("page1");
        scrollArea = new QScrollArea(page1);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(0, 0, 991, 451));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(3);
        sizePolicy1.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy1);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOn);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName("scrollAreaWidgetContents_3");
        scrollAreaWidgetContents_3->setGeometry(QRect(0, -20, 975, 571));
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(scrollAreaWidgetContents_3->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents_3->setSizePolicy(sizePolicy2);
        scrollAreaWidgetContents_3->setMinimumSize(QSize(975, 571));
        scrollAreaWidgetContents_3->setAutoFillBackground(true);
        widgetContainer = new QWidget(scrollAreaWidgetContents_3);
        widgetContainer->setObjectName("widgetContainer");
        widgetContainer->setGeometry(QRect(0, 20, 981, 521));
        sizePolicy.setHeightForWidth(widgetContainer->sizePolicy().hasHeightForWidth());
        widgetContainer->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(widgetContainer);
        verticalLayout_2->setSpacing(12);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        verticalLayout_2->setContentsMargins(-1, 9, -1, -1);
        pushButtonImage = new QPushButton(widgetContainer);
        pushButtonImage->setObjectName("pushButtonImage");
        sizePolicy2.setHeightForWidth(pushButtonImage->sizePolicy().hasHeightForWidth());
        pushButtonImage->setSizePolicy(sizePolicy2);
        pushButtonImage->setMinimumSize(QSize(100, 30));

        verticalLayout_2->addWidget(pushButtonImage);

        imageLabel = new QLabel(widgetContainer);
        imageLabel->setObjectName("imageLabel");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(imageLabel->sizePolicy().hasHeightForWidth());
        imageLabel->setSizePolicy(sizePolicy3);
        imageLabel->setScaledContents(false);
        imageLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(imageLabel);

        scrollArea->setWidget(scrollAreaWidgetContents_3);
        stackedWidget->addWidget(page1);
        page2 = new QWidget();
        page2->setObjectName("page2");
        stackedWidget->addWidget(page2);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1007, 21));
        menuNetMap = new QMenu(menubar);
        menuNetMap->setObjectName("menuNetMap");
        menuEquipement = new QMenu(menubar);
        menuEquipement->setObjectName("menuEquipement");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuNetMap->menuAction());
        menubar->addAction(menuEquipement->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionNouvellePage->setText(QCoreApplication::translate("MainWindow", "NouvellePage", nullptr));
        pushButtonImage->setText(QCoreApplication::translate("MainWindow", "Scanner le r\303\251seau", nullptr));
        imageLabel->setText(QString());
        menuNetMap->setTitle(QCoreApplication::translate("MainWindow", "NetMap", nullptr));
        menuEquipement->setTitle(QCoreApplication::translate("MainWindow", "Equipement", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
