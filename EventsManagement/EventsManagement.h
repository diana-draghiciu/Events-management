#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_EventsManagement.h"

class EventsManagement : public QMainWindow
{
    Q_OBJECT

public:
    EventsManagement(QWidget *parent = Q_NULLPTR);

private:
    Ui::EventsManagementClass ui;
};
