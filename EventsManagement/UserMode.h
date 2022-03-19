#pragma once
#include "UserController.h"
#include "AdmController.h"

class UserMode {
private:
	UserController* user_serv;
	const AdmController& adm;
public:
	UserMode(UserController* uc, const AdmController& a);
	//
	void choose_month(EventRepository& month_list,Event& e);
	//Adds current event
	void add_user_ui(EventRepository& month_list,Event &e);
	//Removes current event
	void remove_user_ui(EventRepository& month_list,Event& e);
	//Removes an event with a given title
	void remove_title_ui(EventRepository& month_list);

	//Display's the current event
	void display_current(EventRepository* month_list,Event& e);
	//Displays the user's attending list
	void display_list();
	//Displays the user's attending list according to the option given: CSV file or HTML file
	void display_option(const std::string& option);

	//Displays the next event
	void next(EventRepository* month_list,Event& e);
	//the user's menu
	void menuUser(const std::string& option);
};
