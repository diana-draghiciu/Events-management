#pragma once
#include "Event.h"
#include "EventRepository.h"
#include <string>
#include <iostream>

class TextFileRepo: public EventRepository
{
private:
	std::string file_name;
public:
	TextFileRepo(std::string file);

	void add_repo(const Event& e);
	void remove_repo(const std::string& title);
	void update_repo(const Event& e1,const Event& e2);
	void load();
	void save();
};

