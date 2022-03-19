#pragma once
#include "AdmController.h"

class AdministratorUI
{
private:
	AdmController* Adm_serv;
public:
	//Constructor
	AdministratorUI(AdmController* ac);

	//Displays the entire list of events
	void show_list();

	//Administrator: adds a new event
	void add_AdmUI();

	//Administrator: removes an event
	void remove_AdmUI();

	//Administrator: updates an event
	void update_AdmUI();

	//Administrator menu
	void menu_AdmUI();

};

