#include "guiADM.h"
#include <QApplication>
#include <QListWidget>
#include <QLabel>
#include <QFormLayout>
#include <QMessageBox>
#include "ValidationException.h"
#include <QBarSet>
#include <QtCharts>
#include <QShortcut>

using namespace QtCharts;
guiADM::~guiADM()
{
	delete this->Adm_serv;
}

void guiADM::guiInit()
{
	//General layout of the window
	QHBoxLayout* layout = new QHBoxLayout{ this };
	this->resize(2000, 500);
	// left side - just the list
	this->eventsList = new QListWidget{};
	// set the selection model
	this->eventsList->setSelectionMode(QAbstractItemView::SingleSelection);
	layout->addWidget(this->eventsList);

	// right side - event information + buttons
	QWidget* rightSide = new QWidget{};
	rightSide->setStyleSheet("background-color:rgb(51,153,255)");
	QVBoxLayout* vLayout = new QVBoxLayout{ rightSide };

	// EVENT INFO
	QWidget* DataWidget = new QWidget{};
	DataWidget->setStyleSheet("background-color:rgb(224,224,224)");
	QFormLayout* formLayout = new QFormLayout{ DataWidget };

	//create boxes
	this->titleEdit = new QLineEdit{};
	this->titleEdit->setFixedWidth(500);
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
	buttonsWidget->setStyleSheet("background-color: rgb(224,224,224)");
	QHBoxLayout* hLayout = new QHBoxLayout{ buttonsWidget };
	this->addEventButton = new QPushButton("Add event");
	this->addEventButton->setFont(f);
	this->addEventButton->setStyleSheet("background-color: rgb(153,255,204)");
	this->deleteEventButton = new QPushButton("Delete event");
	this->deleteEventButton->setFont(f);
	this->deleteEventButton->setStyleSheet("background-color: rgb(153,255,255)");
	this->updateEventButton = new QPushButton("Update event");
	this->updateEventButton->setFont(f);
	this->updateEventButton->setStyleSheet("background-color: rgb(153,204,255)");
	this->undoButton = new QPushButton("Undo");
	this->undoButton->setFont(f);
	this->undoButton->setStyleSheet("background-color: rgb(204,229,255)");
	this->redoButton = new QPushButton("Redo");
	this->redoButton->setFont(f);
	this->redoButton->setStyleSheet("background-color: rgb(204,255,229)");
	
	hLayout->addWidget(this->addEventButton);
	hLayout->addWidget(this->deleteEventButton);
	hLayout->addWidget(this->updateEventButton);
	hLayout->addWidget(this->undoButton);
	hLayout->addWidget(this->redoButton);

	vLayout->addWidget(buttonsWidget);

	// add everything to the big layout
	layout->addWidget(this->eventsList);
	layout->addWidget(rightSide);
	
	
	//------------------------------------------------------------------------
	QWidget* chartWidget = new QWidget{};	//One bar representing the nr of participants to the events
	QBarSet* set = new QBarSet("Nr of participants");
	for (const auto& e : this->Adm_serv->getEventListSrv())
		set->append(e.getNr()); //append height (nr of participants) for each event (category)

	QBarSeries* series = new QBarSeries();
	series->append(set);

	QChart* chart = new QChart();
	chart->addSeries(series);
	chart->setTitle("Events");
	chart->setAnimationOptions(QChart::SeriesAnimations);

	QBarCategoryAxis* axisX = new QBarCategoryAxis();
	for(const auto& e: this->Adm_serv->getEventListSrv())
		axisX->append(QString::fromStdString(e.getTitle())); //set the names of the categories
	chart->addAxis(axisX, Qt::AlignBottom);
	series->attachAxis(axisX);

	QValueAxis* axisY = new QValueAxis();
	axisY->setRange(0, 15); //set range, we suppose max 15 nr of participants
	chart->addAxis(axisY, Qt::AlignLeft); //set the nr to the left of the chart, Y-axis
	series->attachAxis(axisY);

	chart->legend()->setVisible(true); //make legend visible and set it at the bottom of the chart
	chart->legend()->setAlignment(Qt::AlignBottom);

	QChartView* chartView = new QChartView(chart, chartWidget);
	chartView->setRenderHint(QPainter::Antialiasing);
	layout->addWidget(chartView);
}

void guiADM::connectSignalsAndSlots()
{
	// when the vector of events is updated - re-populate the list
	QObject::connect(this, &guiADM::eventsUpdatedSignal, this, &guiADM::show_list);

	// add a connection: function listItemChanged() will be called when an item in the list is selected
	QObject::connect(this->eventsList, &QListWidget::itemSelectionChanged, this, [this]() {this->listItemChanged(); });

	// add button connections
	QObject::connect(this->addEventButton, &QPushButton::clicked, this, &guiADM::add_AdmUI);
	QObject::connect(this->deleteEventButton, &QPushButton::clicked, this, &guiADM::remove_AdmUI);
	QObject::connect(this->updateEventButton, &QPushButton::clicked, this, &guiADM::update_AdmUI);
	QObject::connect(this->undoButton, &QPushButton::clicked, this, &guiADM::undoHandler);
	QObject::connect(this->redoButton, &QPushButton::clicked, this, &guiADM::redoHandler);

	//shortcuts undo/redo
	QShortcut* undoShortcut = new QShortcut(QKeySequence("Ctrl+Z"), this);
	QObject::connect(undoShortcut, &QShortcut::activated, [this]() { this->undoHandler(); });
	QShortcut* redoShortcut = new QShortcut(QKeySequence("Ctrl+Y"), this);
	QObject::connect(redoShortcut, &QShortcut::activated, [this]() {this->redoHandler(); });
}

void guiADM::listItemChanged() {

	int idx;
	if (this->eventsList->count() == 0)
		idx = -1;

	// get selected index
	QModelIndexList index = this->eventsList->selectionModel()->selectedIndexes();
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

	if (idx >= this->Adm_serv->getEventListSrv().size())
		return;
	Event e = this->Adm_serv->getEventListSrv()[idx];

	this->titleEdit->setText(QString::fromStdString(e.getTitle()));
	this->linkEdit->setText(QString::fromStdString(e.getLink()));
	this->descriptionEdit->setText(QString::fromStdString(e.getDescription()));
	this->nrEdit->setText(QString::fromStdString(std::to_string(e.getNr())));
	std::string date;
	if(e.getDate().minutes<10)
		date = std::to_string(e.getDate().day) + "/" + std::to_string(e.getDate().month) + "/" + std::to_string(e.getDate().year) + " " + std::to_string(e.getDate().hours) + ":0"+ std::to_string(e.getDate().minutes);
	else
		date = std::to_string(e.getDate().day) + "/" + std::to_string(e.getDate().month) + "/" + std::to_string(e.getDate().year) + " " + std::to_string(e.getDate().hours) + ":" + std::to_string(e.getDate().minutes);
	this->dateEdit->setText(QString::fromStdString(date));
}

void guiADM::show_list()
{
	
	// clear the list, if there are elements in it
	if (this->eventsList->count() > 0)
		this->eventsList->clear();

	for (const auto& e : this->Adm_serv->getEventListSrv()) {
		QString itemInList= QString::fromStdString(e.toStr());
		QFont f{ "Verdana", 15 };
		QListWidgetItem* item = new QListWidgetItem{ itemInList };
		item->setFont(f);
		this->eventsList->addItem(item);
	}
}

void guiADM::add_AdmUI()
{
	try {
	QString title = this->titleEdit->text();
	QString link = this->linkEdit->text();
	QString description = this->descriptionEdit->toPlainText();
	QString nr = this->nrEdit->text();
	QString auxdate = this->dateEdit->text();
	std::string line = auxdate.toStdString();

	//Date
	std::string dateANDtime, date, time;
	std::stringstream attrib1(line);
	std::getline(attrib1, dateANDtime, ' ');
	std::stringstream attrib2(dateANDtime);
	std::getline(attrib2, date, '/');

	int day = 0;
	std::stringstream ax1(date);
	ax1 >> day;

	std::getline(attrib2, date, '/');
	int month = 0;
	std::stringstream ax2(date);
	ax2 >> month;

	std::getline(attrib2, date, '/');
	int year = 0;
	std::stringstream ax3(date);
	ax3 >> year;

	//Time
	std::getline(attrib1, dateANDtime, ' ');
	std::stringstream attrib3(dateANDtime);
	std::getline(attrib3, time, ':');

	int hour = 0;
	std::stringstream ax4(time);
	ax4 >> hour;

	std::getline(attrib3, time, '\n');
	int minute = 0;
	std::stringstream ax5(time);
	ax5 >> minute;

	this->Adm_serv->add_srv(title.toStdString(), description.toStdString(), nr.toInt(), link.toStdString(), day, month, year, hour, minute);
	emit eventsUpdatedSignal();
	}
	catch (const ValidateException& ex) {
		QMessageBox* msgBox;
		std::ostringstream strm;
		strm << ex;
		msgBox->warning(this->eventsList, "Error", strm.str().c_str());
	}
	catch (const RepoException& ex) {
		QMessageBox* msgBox;
		std::ostringstream strm;
		strm << ex;
		msgBox->warning(this->eventsList, "Error", strm.str().c_str());
	}
}

void guiADM::remove_AdmUI()
{
	QString title = this->titleEdit->text();
	try {
		this->Adm_serv->remove_srv(title.toStdString());
		emit eventsUpdatedSignal();
	}
	catch (const ValidateException& ex) {
		QMessageBox* msgBox;
		std::ostringstream strm;
		strm << ex;
		msgBox->warning(this->eventsList, "Error", strm.str().c_str());
	}
	catch (const RepoException& ex) {
		QMessageBox* msgBox;
		std::ostringstream strm;
		strm << ex;
		msgBox->warning(this->eventsList, "Error", strm.str().c_str());
	}
}

void guiADM::update_AdmUI()
{
	if (this->eventsList->count() == 0)
		return;

	// get selected index
	QModelIndexList index = this->eventsList->selectionModel()->selectedIndexes();
	if (index.size() == 0)
	{
		this->titleEdit->clear();
		this->linkEdit->clear();
		this->descriptionEdit->clear();
		this->dateEdit->clear();
		this->nrEdit->clear();
		return;
	}

	int idx = index.at(0).row();
	
	QString title = this->titleEdit->text();
	QString link = this->linkEdit->text();
	QString description = this->descriptionEdit->toPlainText();
	QString nr = this->nrEdit->text();
	QString auxdate = this->dateEdit->text();
	std::string line = auxdate.toStdString();

	//Date
	std::string dateANDtime, date, time;
	std::stringstream attrib1(line);
	std::getline(attrib1, dateANDtime, ' ');
	std::stringstream attrib2(dateANDtime);
	std::getline(attrib2, date, '/');

	int day = 0;
	std::stringstream ax1(date);
	ax1 >> day;

	std::getline(attrib2, date, '/');
	int month = 0;
	std::stringstream ax2(date);
	ax2 >> month;

	std::getline(attrib2, date, '/');
	int year = 0;
	std::stringstream ax3(date);
	ax3 >> year;

	//Time
	std::getline(attrib1, dateANDtime, ' ');
	std::stringstream attrib3(dateANDtime);
	std::getline(attrib3, time, ':');

	int hour = 0;
	std::stringstream ax4(time);
	ax4 >> hour;

	std::getline(attrib3, time, '\n');
	int minute = 0;
	std::stringstream ax5(time);
	ax5 >> minute;


	try {
		this->Adm_serv->update_srv(this->Adm_serv->getEventListSrv()[idx].getTitle(), title.toStdString(), description.toStdString(), nr.toInt(), link.toStdString(), day, month, year, hour, minute);
		emit eventsUpdatedSignal();
	}
	catch (const ValidateException& ex) {
		QMessageBox* msgBox;
		std::ostringstream strm;
		strm << ex;
		msgBox->warning(this->eventsList, "Error", strm.str().c_str());
	}
	catch (const RepoException& ex) {
		QMessageBox* msgBox;
		std::ostringstream strm;
		strm << ex;
		msgBox->warning(this->eventsList, "Error", strm.str().c_str());
	}
}

void guiADM::undoHandler()
{
	try {
		this->Adm_serv->undo();
		emit eventsUpdatedSignal();
	}
	catch (const std::exception& ex) {
		QMessageBox* msgBox;
		msgBox->warning(this->eventsList, "Error", "No more undos left!");
	}
}

void guiADM::redoHandler()
{
	try {
		this->Adm_serv->redo();
		emit eventsUpdatedSignal();
	}
	catch (const std::exception& ex) {
		QMessageBox* msgBox;
		msgBox->warning(this->eventsList, "Error", "No more redos left!");
	}
}
