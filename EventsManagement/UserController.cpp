#include "UserController.h"
#include <sstream>

UserController::UserController(EventRepository* user, EventRepository* a): adm(a) { 
	this->repo = user;
	this->current = 0;
}

void UserController::GetCurrent(EventRepository* month_list, Event& e) {
	e=month_list->getEventListRepo()[this->current];
}

void UserController::Next(EventRepository* month_list) {
	this->current++;
	if (!Valid(month_list))
		this->current = 0;
}

bool UserController::Valid(EventRepository* month_list) {
	if (this->current < month_list->getEventListRepo().size())
		return true;
	return false;
}

void UserController::Add_User(EventRepository& month_list,Event& e) {
	e.setNr(e.getNr() + 1);
	this->repo->add_repo(e);

	int i = this->adm->getEventPos(e);
	this->adm->getEventListRepo()[i].setNr(this->adm->getEventListRepo()[i].getNr() + 1);
	this->adm->update_repo(this->adm->getEventListRepo()[i], this->adm->getEventListRepo()[i]);
	//this->adm->save();

	i = month_list.getEventPos(e);
	month_list.getEventListRepo()[i].setNr(month_list.getEventListRepo()[i].getNr() + 1);
}

void UserController::Remove_User(EventRepository& month_list,Event& e) {
	this->repo->remove_repo(e.getTitle());
	e.setNr(e.getNr() - 1);

	

	int i = this->adm->getEventPos(e);
	this->adm->getEventListRepo()[i].setNr(this->adm->getEventListRepo()[i].getNr() - 1);
	this->adm->update_repo(this->adm->getEventListRepo()[i], this->adm->getEventListRepo()[i]);
	//this->adm->save();

	i = month_list.getEventPos(e);
	month_list.getEventListRepo()[i].setNr(month_list.getEventListRepo()[i].getNr() - 1);

}

void UserController::Remove_Using_Title(EventRepository& month_list,const std::string& title) {
	this->repo->remove_repo(title);

	Event e = Event(title, "", 0, "", 0, 0, 0, 0, 0);

	int i = this->adm->getEventPos(e);
	this->adm->getEventListRepo()[i].setNr(this->adm->getEventListRepo()[i].getNr() - 1);
	this->adm->update_repo(this->adm->getEventListRepo()[i], this->adm->getEventListRepo()[i]);
	//this->adm->save();

	i = month_list.getEventPos(e);
	if(i!=-1)
		month_list.getEventListRepo()[i].setNr(month_list.getEventListRepo()[i].getNr() - 1);
}

void UserController::sortChronologically() {
	this->adm->sortChronologically();
}

