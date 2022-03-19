#pragma once
#include "Event.h"
#include <vector>
#include<string>
#include <ostream>
#define NULL_EVENT Event();

class EventRepository
{
private:
	std::vector<Event> arr;
public:
	EventRepository(){}
	//Returns the list of events
	std::vector<Event>& getEventListRepo(){ return this->arr; };

	//Returns the position to an event
	int getEventPos(const Event& e);

	virtual std::string getFile();
	virtual void add_repo(const Event& e);
	virtual void remove_repo(const std::string& title);
	virtual void update_repo(const Event& e1,const Event& e2);

	//Sorts the list order chronologically
	void sortChronologically();
};

class RepoException {
	std::vector<std::string> msgs;
public:
	RepoException(const std::vector<std::string>& errors) :msgs{ errors } {}
	//functie friend (vreau sa folosesc membru privat msg)
	friend std::ostream& operator<<(std::ostream& out, const RepoException& ex);
};

std::ostream& operator<<(std::ostream& out, const RepoException& ex);