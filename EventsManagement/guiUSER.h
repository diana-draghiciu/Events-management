#pragma once
#include <QListWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QSpinBox>
#include <qlineedit.h>
#include "UserController.h"
#include "AdmController.h"
#include "Event.h"
#include "TableModel.h"
#include <QtWidgets/qtableview.h>

class guiUSER: public QWidget
{
	Q_OBJECT
private:
	UserController* user;
	AdmController* admin;

	int currentPosition;
	EventRepository* chosenMonth;

	TableModel* model;
	QTableView* usersList;

	QLineEdit* titleEdit;
	QLineEdit* linkEdit;
	QTextEdit* descriptionEdit;
	QLineEdit* nrEdit;
	QLineEdit* dateEdit;

	QPushButton* addEventButton;
	QPushButton* deleteEventButton;
	QPushButton* NextButton;
	QPushButton* ChangeMonthButton;
	QPushButton* DisplayButton;
	QSpinBox* spinner;

public:
	guiUSER(UserController* ac, AdmController* adm, QWidget* parent);
	void guiInit();
	void connectSignalsAndSlots();
	// When an item in the list is clicked, the text boxes get filled with the item's information
	void completeInfo();

	void listItemChanged();

	//Add button handler
	void add_userUI();

	//removes an event
	void remove_userUI();

	void next();
	void changeMonth();
	void display();

signals:
	void eventsUpdatedSignal();
};


