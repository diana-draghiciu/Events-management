/********************************************************************************
** Form generated from reading UI file 'EventsManagement.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EVENTSMANAGEMENT_H
#define UI_EVENTSMANAGEMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EventsManagementClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *EventsManagementClass)
    {
        if (EventsManagementClass->objectName().isEmpty())
            EventsManagementClass->setObjectName(QString::fromUtf8("EventsManagementClass"));
        EventsManagementClass->resize(600, 400);
        menuBar = new QMenuBar(EventsManagementClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        EventsManagementClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(EventsManagementClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        EventsManagementClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(EventsManagementClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        EventsManagementClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(EventsManagementClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        EventsManagementClass->setStatusBar(statusBar);

        retranslateUi(EventsManagementClass);

        QMetaObject::connectSlotsByName(EventsManagementClass);
    } // setupUi

    void retranslateUi(QMainWindow *EventsManagementClass)
    {
        EventsManagementClass->setWindowTitle(QCoreApplication::translate("EventsManagementClass", "EventsManagement", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EventsManagementClass: public Ui_EventsManagementClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EVENTSMANAGEMENT_H
