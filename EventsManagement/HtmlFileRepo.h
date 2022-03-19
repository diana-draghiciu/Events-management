#pragma once
#include "EventRepository.h"

class htmlFileRepo : public EventRepository {
private:
	std::string file_name;
public:
	htmlFileRepo(std::string file) : EventRepository(), file_name(file) {}
	std::string getFile() { return this->file_name; };
	void add_repo(const Event& e);
	void remove_repo(const std::string& title);
	void update_repo(const Event& e1, const Event& e2);
	void save();
};