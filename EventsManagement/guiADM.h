#pragma once
#include <QTextEdit>
#include <QPushButton>
#include <qlineedit.h>
#include <QListWidget>
#include "AdmController.h"


class guiADM: public QWidget
{
	Q_OBJECT
private:
	AdmController* Adm_serv;

	QListWidget* eventsList;
	QLineEdit* titleEdit;
	QLineEdit* linkEdit;
	QTextEdit* descriptionEdit;
	QLineEdit* nrEdit;
	QLineEdit* dateEdit;
	
	QPushButton* addEventButton;
	QPushButton* deleteEventButton;
	QPushButton* updateEventButton;
	QPushButton* undoButton;
	QPushButton* redoButton;

public:
	guiADM(AdmController* ac, QWidget* parent) : QWidget{ parent }, Adm_serv(ac) { guiInit(); this->eventsList->setStyleSheet("background-color:rgb(224,224,224)"); connectSignalsAndSlots(); show_list(); }
	~guiADM();

	void guiInit();
	void connectSignalsAndSlots();
	// When an item in the list is clicked, the text boxes get filled with the item's information
	void listItemChanged();

	//Displays the entire list of events
	void show_list();

	//Administrator: adds a new event
	//Add button handler
	void add_AdmUI();

	//Administrator: removes an event
	void remove_AdmUI();

	//Administrator: updates an event
	void update_AdmUI();

	void undoHandler();
	void redoHandler();


signals:
	void eventsUpdatedSignal();

};

/*
class TestTableModel :public QAbstractTableModel {
	friend class guiADM;
public:
	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return ;
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return COLS;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			qDebug() << "row:" << index.row() << " col:" << index.column();
			return QString("Row%1, Column%2").arg(index.row()).arg(index.column());
		}

		return QVariant{};
	}
};
*/