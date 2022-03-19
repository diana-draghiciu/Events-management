#pragma once
#include <ctime>
#include <string>
#include <iostream>
#include <sstream>

typedef struct{
	int day;
	int month;
	int year;
	int hours;
	int minutes;
	int seconds;
} date;

//Each Event has a title, a description, a date and time, a number of people who are going and a link towards the online resource containing the event
class Event
{
private:
	std::string title;
	std::string description;
	int nr;
	std::string link;
	
	date dt;

public:

	//constructor
	Event();

	Event(std::string title, std::string description, int nr, std::string link, int day, int month, int year, int hours, int minutes);

	//copy constructor
	Event(const Event& e);

	//Updates the given string with a specific format
	const std::string toStr() const;

	//getters
	const std::string& getTitle() const;
	const std::string& getDescription() const;
	date getDate() const;
	int getNr() const;
	void setNr(int value);
	const std::string& getLink() const;

	Event& operator=(const Event& e);
	bool operator==(const Event& e1);

	friend std::ostream& operator<<(std::ostream& out, const Event& e);
	friend std::istream& operator>>(std::istream& in, Event& e);
};

