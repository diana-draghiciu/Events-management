#pragma once
#include "Event.h"
#include "EventRepository.h"
#include <string>
#include <vector>
#include "TextFileRepo.h"
#include "UndoRedo.h"

class UserController
{
private:
	int current;
	EventRepository* adm;
	EventRepository* repo;
	bool Valid(EventRepository* month_list);
public:
	UserController(EventRepository* user, EventRepository* a);
	
	//Updates the current element of the iterator
	void GetCurrent(EventRepository* month_list,Event& e);

	std::string getFileServ() { return this->repo->getFile(); };

	//Return the user's attending list
	std::vector<Event> getElems() const { return this->repo->getEventListRepo(); };
	//Goes to the next element of the iterator
	void Next(EventRepository* month_list);
	//Adds the current event to the user's attending list
	void Add_User(EventRepository& month_list,Event& e);
	//Removes the current event from the user's attending list
	void Remove_User(EventRepository& month_list,Event& e);
	//Removes the event with the given title from the user's attending list
	void Remove_Using_Title(EventRepository& month_list,const std::string& title);
	//Sorts the administrator's list chronologically
	void sortChronologically();

};
