#include "guiUSER.h"
#include <qlayout.h>
#include <QFormLayout>
#include <QLabel>
#include <QMessageBox>
#include <qshortcut.h>

guiUSER::guiUSER(UserController* ac, AdmController* adm, QWidget* parent) : QWidget{ parent }, admin(adm), user(ac) {
	this->chosenMonth=new EventRepository();
	for (const auto& e : this->admin->getEventListSrv()) {
		this->chosenMonth->add_repo(e);
	}
	this->currentPosition = 0;
	std::string aux = std::string("start ").append(this->chosenMonth->getEventListRepo()[currentPosition].getLink());
	system(aux.c_str());
	guiInit(); this->usersList->setStyleSheet("background-color:darkgray;"); ; 
	connectSignalsAndSlots(); listItemChanged();
}


void guiUSER::guiInit()
{
	//General layout of the window
	QHBoxLayout* layout = new QHBoxLayout{ this };

	// left side - just the list
	this->usersList = new QTableView{};
	this->usersList->resizeColumnsToContents();
	this->model = new TableModel{ this->user };
	this->usersList->setModel(this->model);
	this->usersList->setSelectionMode(QAbstractItemView::SingleSelection);
	layout->addWidget(this->usersList);

	// right side - event information + buttons
	QWidget* rightSide = new QWidget{};
	rightSide->setStyleSheet("background-color:darkgray;");
	QVBoxLayout* vLayout = new QVBoxLayout{ rightSide };

	// EVENT INFO
	QWidget* DataWidget = new QWidget{};
	DataWidget->setStyleSheet("background-color: rgb(224,224,224)");
	QFormLayout* formLayout = new QFormLayout{ DataWidget };

	//create boxes
	this->titleEdit = new QLineEdit{};
	//this->titleEdit->setFixedWidth(400);
	this->linkEdit = new QLineEdit{};
	this->descriptionEdit = new QTextEdit{};
	this->nrEdit = new QLineEdit{};
	this->dateEdit = new QLineEdit{};

	QFont f{ "Verdana", 15 };
	QFont f1{ "Verdana", 8 };

	//label the boxes
	QLabel* titleLabel = new QLabel{ "&Event title:" };
	titleLabel->setBuddy(this->titleEdit);
	QLabel* linkLabel = new QLabel{ "&Event link: " };
	linkLabel->setBuddy(this->linkEdit);
	QLabel* descriptionLabel = new QLabel{ "&Description:" };
	descriptionLabel->setBuddy(this->descriptionEdit);
	QLabel* nrLabel = new QLabel{ "&no. participants:" };
	nrLabel->setBuddy(this->nrEdit);
	QLabel* dateLabel = new QLabel{ "&Date: " };
	dateLabel->setBuddy(this->dateEdit);


	titleLabel->setFont(f);
	linkLabel->setFont(f);
	descriptionLabel->setFont(f);
	nrLabel->setFont(f);
	dateLabel->setFont(f);
	this->titleEdit->setFont(f);
	this->linkEdit->setFont(f1);
	this->descriptionEdit->setFont(f);
	this->nrEdit->setFont(f);
	this->dateEdit->setFont(f);
	formLayout->addRow(titleLabel, this->titleEdit);
	formLayout->addRow(linkLabel, this->linkEdit);
	formLayout->addRow(descriptionLabel, this->descriptionEdit);
	formLayout->addRow(nrLabel, this->nrEdit);
	formLayout->addRow(dateLabel, this->dateEdit);

	vLayout->addWidget(DataWidget);

	// buttons
	QWidget* buttonsWidget = new QWidget{};
	buttonsWidget->setStyleSheet("background-color:darkgray;");
	QHBoxLayout* hLayout = new QHBoxLayout{ buttonsWidget };
	this->addEventButton = new QPushButton("Add event");
	this->addEventButton->setFont(f);
	this->addEventButton->setStyleSheet("background-color: rgb(255,204,153)");

	this->deleteEventButton = new QPushButton("Remove event");
	this->deleteEventButton->setFont(f);
	this->deleteEventButton->setStyleSheet("background-color: rgb(255,255,153)");

	this->NextButton = new QPushButton("Next");
	this->NextButton->setFont(f);
	this->NextButton->setStyleSheet("background-color: rgb(255, 153, 153)");

	this->ChangeMonthButton = new QPushButton("Change month");
	this->ChangeMonthButton->setFont(f);
	this->ChangeMonthButton->setStyleSheet("background-color: rgb(153,255,153)");

	this->spinner = new QSpinBox{};
	this->spinner->setRange(0, 12);
	this->spinner->setFont(f);
	this->spinner->setStyleSheet("background-color:rgb(153,204,255)");

	this->DisplayButton = new QPushButton("Display");
	this->DisplayButton->setFont(f);
	this->DisplayButton->setStyleSheet("background-color: rgb(204,153,255)");

	hLayout->addWidget(this->NextButton);
	hLayout->addWidget(this->addEventButton);
	hLayout->addWidget(this->deleteEventButton);
	hLayout->addWidget(this->ChangeMonthButton);
	hLayout->addWidget(this->spinner);
	hLayout->addWidget(this->DisplayButton);
	vLayout->addWidget(buttonsWidget);

	// add everything to the big layout
	layout->addWidget(rightSide);
}

void guiUSER::connectSignalsAndSlots()
{
	QObject::connect(this, &guiUSER::eventsUpdatedSignal, this, &guiUSER::listItemChanged);

	// add button connections
	QObject::connect(this->addEventButton, &QPushButton::clicked, this, &guiUSER::add_userUI);
	QObject::connect(this->deleteEventButton, &QPushButton::clicked, this, &guiUSER::remove_userUI);
	QObject::connect(this->NextButton, &QPushButton::clicked, this, &guiUSER::next);
	QObject::connect(this->ChangeMonthButton, &QPushButton::clicked, this, &guiUSER::changeMonth);
	QObject::connect(this->DisplayButton, &QPushButton::clicked, this, &guiUSER::display);

}

void guiUSER::completeInfo()
{
		int idx;
		if (this->user->getElems().size() == 0 )//|| this->usersList->size()==0)
			idx = -1;

		// get selected index
		QModelIndexList index = this->usersList->selectionModel()->selectedIndexes();
		if (index.size() == 0)
		{
			this->titleEdit->clear();
			this->linkEdit->clear();
			this->descriptionEdit->clear();
			this->dateEdit->clear();
			this->nrEdit->clear();
			return;
		}

		idx = index.at(0).row();

		if (idx >= this->user->getElems().size())
			return;
		Event e = this->user->getElems()[idx];

		this->titleEdit->setText(QString::fromStdString(e.getTitle()));
		this->linkEdit->setText(QString::fromStdString(e.getLink()));
		this->descriptionEdit->setText(QString::fromStdString(e.getDescription()));
		this->nrEdit->setText(QString::fromStdString(std::to_string(e.getNr())));
		std::string date;
		if (e.getDate().minutes < 10)
			date = std::to_string(e.getDate().day) + "/" + std::to_string(e.getDate().month) + "/" + std::to_string(e.getDate().year) + " " + std::to_string(e.getDate().hours) + ":0" + std::to_string(e.getDate().minutes);
		else
			date = std::to_string(e.getDate().day) + "/" + std::to_string(e.getDate().month) + "/" + std::to_string(e.getDate().year) + " " + std::to_string(e.getDate().hours) + ":" + std::to_string(e.getDate().minutes);
		this->dateEdit->setText(QString::fromStdString(date));
}

void guiUSER::listItemChanged()
{
	Event currentEvent = this->chosenMonth->getEventListRepo()[currentPosition];
	this->titleEdit->setText(QString::fromStdString(currentEvent.getTitle()));
	this->descriptionEdit->setText(QString::fromStdString(currentEvent.getDescription()));
	this->linkEdit->setText(QString::fromStdString(currentEvent.getLink()));
	this->nrEdit->setText(QString::fromStdString(std::to_string(currentEvent.getNr())));
	std::string date;
	if (currentEvent.getDate().minutes < 10)
		date = std::to_string(currentEvent.getDate().day) + "/" + std::to_string(currentEvent.getDate().month) + "/" + std::to_string(currentEvent.getDate().year) + " " + std::to_string(currentEvent.getDate().hours) + ":0" + std::to_string(currentEvent.getDate().minutes);
	else
		date = std::to_string(currentEvent.getDate().day) + "/" + std::to_string(currentEvent.getDate().month) + "/" + std::to_string(currentEvent.getDate().year) + " " + std::to_string(currentEvent.getDate().hours) + ":" + std::to_string(currentEvent.getDate().minutes);
	this->dateEdit->setText(QString::fromStdString(date));
}

void guiUSER::add_userUI()
{
	Event currentEvent = this->chosenMonth->getEventListRepo()[currentPosition];
	try {
		this->user->Add_User(*(this->chosenMonth), currentEvent);
		this->model->update();
	}
	catch (const RepoException& ex) {
		QMessageBox* msgBox;
		msgBox->warning(this->usersList, "Error", "Event already added!");
	}
}

void guiUSER::remove_userUI()
{
	int index=this->usersList->selectionModel()->currentIndex().row();
	if (index == -1)
		return;
	Event e = this->user->getElems()[index];
	try {
		this->user->Remove_Using_Title(*(this->chosenMonth), e.getTitle());
		this->model->update();
	}
	catch (const RepoException& ex) {
		QMessageBox* msgBox;
		msgBox->warning(this->usersList, "Error", "Event already removed!");
	}
}


void guiUSER::next()
{
	if (currentPosition < this->chosenMonth->getEventListRepo().size()-1) {
		currentPosition++;
	}
	else {
		currentPosition = 0;
	}
	std::string aux = std::string("start ").append(this->chosenMonth->getEventListRepo()[currentPosition].getLink());
	system(aux.c_str());
	this->usersList->clearSelection();
	emit eventsUpdatedSignal();
}

void guiUSER::changeMonth()
{
	int month= this->spinner->value();
	this->chosenMonth->getEventListRepo().clear();

	bool found = false;
	if (month == 0)
		for (const auto& e : this->admin->getEventListSrv()) {
			this->chosenMonth->add_repo(e);
			found = true;
		}
	else
		for (int i=0;i< this->admin->getEventListSrv().size();i++)
			if (this->admin->getEventListSrv()[i].getDate().month == month) {
				this->chosenMonth->add_repo(this->admin->getEventListSrv()[i]);
				found = true;
			}

	if (!found) {
		QMessageBox* msgBox;
		msgBox->warning(this->usersList, "Error", "No events in given month!");
		this->NextButton->setDisabled(true);
		this->addEventButton->setDisabled(true);
		this->deleteEventButton->setDisabled(true);
		return;
	}
	else {
		this->chosenMonth->sortChronologically();
		currentPosition = 0;
		this->NextButton->setEnabled(true);
		this->addEventButton->setEnabled(true);
		this->deleteEventButton->setEnabled(true);

		std::string aux = std::string("start ").append(this->chosenMonth->getEventListRepo()[currentPosition].getLink());
		system(aux.c_str());
		this->usersList->clearSelection();
		emit eventsUpdatedSignal();
	}
}

void guiUSER::display()
{
	std::string aux = std::string("start ").append(this->user->getFileServ());
	system(aux.c_str());
}
