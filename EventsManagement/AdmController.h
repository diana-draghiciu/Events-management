#pragma once
#include <string>
#include <vector>
#include "Event.h"
#include "EventRepository.h"
#include "UserController.h"
#include "UndoRedo.h"

class UserController;

class AdmController
{
	friend class UserController;
private:
	EventRepository* repo;
	CommandManager commandManager;
public:
	//Administrator Service constructor
	AdmController(EventRepository* repo, CommandManager cmd) :repo(repo), commandManager(cmd) {}

	//getters
	std::vector<Event> getEventListSrv() const { return this->repo->getEventListRepo(); };

	const Event& find_event(std::string title);
	void add_srv(std::string title, std::string description, int nr, std::string link, int day, int month, int year, int hours, int minutes);
	void remove_srv(std::string title);
	void update_srv(std::string title,std::string new_title, std::string description, int nr, std::string link, int day, int month, int year, int hours, int minutes);
	void undo();
	void redo();

	//Generates a list of 10 Events
	void generateList();
};

