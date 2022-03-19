#include "Event.h"
#include <vector>


Event::Event()
{	
	this->title="";
	this->description= "";
	this->link="";
	this->nr = 0;
	this->dt.day = 0;
	this->dt.month = 0;
	this->dt.year = 0;

	this->dt.hours = 0;
	this->dt.minutes = 0;
	this->dt.seconds = 0;
}

Event::Event(std::string title, std::string description, int nr, std::string link, int day, int month, int year, int hours, int minutes) {
	this->title= title;
	this->description= description;
	this->nr = nr;
	this->link= link;
	this->dt.day = day;
	this->dt.month = month;
	this->dt.year = year;
	this->dt.hours = hours;
	this->dt.minutes = minutes;
	
}

Event::Event(const Event& e){
	this->title= e.title;
	this->description= e.description;
	this->nr = e.nr;
	this->link= e.link;
	this->dt.day = e.dt.day;
	this->dt.month = e.dt.month;
	this->dt.year = e.dt.year;
	this->dt.hours = e.dt.hours;
	this->dt.minutes = e.dt.minutes;
}

const std::string Event::toStr() const{
	if (this->dt.minutes < 10) {
		std::stringstream txt;
		txt <<"\n"<< this->title << ": \n" << this->link <<"\n"<<this->description << "\n date: " << this->dt.day<<"/"<<this->dt.month<<"/"<<this->dt.year<<", time: "<<this->dt.hours<<":0"<<this->dt.minutes<<", no. participants: "<< this->nr;
		return txt.str();
	}
	else {
		std::stringstream txt;
		txt << "\n" << this->title << ": \n" << this->link << "\n" << this->description << "\n date: " << this->dt.day << "/" << this->dt.month << "/" << this->dt.year << ", time: " << this->dt.hours << ":" << this->dt.minutes << ", no. participants: " << this->nr;
		return txt.str();
	}
}

std::ostream& operator<<(std::ostream& out, const Event& e) {
	if (e.getDate().minutes < 10)
		out <<"\n"<< e.getTitle() << ";" << e.getDescription() << ";" << e.getLink() << "\n" << e.getNr() << " " << e.getDate().day << "/" << e.getDate().month << "/" << e.getDate().year << " " << e.getDate().hours << ":0" << e.getDate().minutes;
	else
		out << "\n" << e.getTitle() << ";" << e.getDescription() << ";" << e.getLink() << "\n" << e.getNr() << " " << e.getDate().day << "/" << e.getDate().month << "/" << e.getDate().year << " " << e.getDate().hours << ":" << e.getDate().minutes;
	return out;
}

std::istream& operator>>(std::istream& in, Event& e) {

	in.clear(); in.sync();

	//First line
	std::string title,description,link,date,time,line,line2;
	
	std::getline(in, line);
	std::stringstream attrib(line);

	std::getline(attrib, title, ';');
	e.title = title;
	std::getline(attrib,description, ';');
	e.description = description;
	std::getline(attrib,link, '\n');
	e.link = link;
	
	//Second line
	std::getline(in, line);
	std::stringstream attrib1(line);
	std::getline(attrib1, line2, ' ');

	int nr = 0;
	std::stringstream ax(line2);
	ax >> nr;
	e.nr = nr;

	//Date
	std::getline(attrib1, line2, ' ');
	std::stringstream attrib2(line2);
	std::getline(attrib2, date, '/');

	int day = 0;
	std::stringstream ax1(date);
	ax1 >> day;
	e.dt.day = day;

	std::getline(attrib2, date, '/');
	int month = 0;
	std::stringstream ax2(date);
	ax2 >> month;
	e.dt.month = month;

	std::getline(attrib2, date, '/');
	int year = 0;
	std::stringstream ax3(date);
	ax3 >> year;
	e.dt.year = year;

	//Time
	std::getline(attrib1,line2, ' ');
	std::stringstream attrib3(line2);
	std::getline(attrib3, time, ':');

	int hour = 0;
	std::stringstream ax4(time);
	ax4 >> hour;
	e.dt.hours = hour;

	std::getline(attrib3, time, '\n');
	int minute = 0;
	std::stringstream ax5(time);
	ax5 >> minute;
	e.dt.minutes = minute;
	
	return in;
}

const std::string& Event::getTitle() const{
	return this->title;
}

const std::string& Event::getDescription() const{
	return this->description;
}

const std::string& Event::getLink() const{
	return this->link;
}

int Event::getNr() const{
	return this->nr;
}

void Event::setNr(int value) {
	this->nr = value;
}

date Event::getDate() const {
	return this->dt;
}


Event& Event::operator=(const Event& e) {
	this->title = e.title;
	this->description= e.description;
	this->link= e.link;
	this->nr = e.nr;
	this->dt.day = e.dt.day;
	this->dt.month = e.dt.month;
	this->dt.year = e.dt.year;
	this->dt.hours = e.dt.hours;
	this->dt.minutes = e.dt.minutes;

	return *this;
}

bool Event::operator==(const Event& e1)
{
	if (this->title == e1.getTitle())
		return true;
	return false;
}





















