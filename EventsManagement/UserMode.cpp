#include "UserMode.h"
#include <iostream>
#include <string>
#include "EventRepository.h"
#include <sstream>

UserMode::UserMode(UserController* uc, const AdmController& a) : adm(a) {
	this->user_serv = uc;
}

void UserMode::choose_month(EventRepository& month_list,Event& e)
{
	int month;
	do {
		std::cout << "\nGive month nr: ";
		std::cin >> month;
		if (std::cin.fail()) {
			std::cout << "Input not integer!";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return;
		}
	} while (month < 0 ||month > 12);

	month_list.getEventListRepo().clear();

	bool found = false;
	if (month == 0)
		for (const auto& e : this->adm.getEventListSrv()) {
			month_list.add_repo(e);
			found = true;
		}
	else
		for (const auto& e : this->adm.getEventListSrv())
			if (e.getDate().month == month) {
				month_list.add_repo(e);
				found = true;
			}
				
	if (!found) {
		std::cout<<"No events in given month!";
		choose_month(month_list, e);
		return;
	}
	else {
		month_list.sortChronologically();
		display_current(&month_list, e);
	}
}

void UserMode::add_user_ui(EventRepository& month_list,Event& e) {
	this->user_serv->Add_User(month_list,e);
}
void UserMode::remove_user_ui(EventRepository& month_list,Event& e) {
	this->user_serv->Remove_User(month_list,e);
}

void UserMode::remove_title_ui(EventRepository& month_list) {
	std::string title;
	std::cin.get();
	std::cout << "\nEvent title: ";
	std::getline(std::cin, title);

	this->user_serv->Remove_Using_Title(month_list,title);
}

void UserMode::display_current(EventRepository* month_list,Event& e) {
	std::string str;
	this->user_serv->GetCurrent(month_list,e);
	std::cout << e;
}

void UserMode::next(EventRepository* month_list,Event& e) {
	this->user_serv->Next(month_list);
	 display_current(month_list,e);
}

void UserMode::display_list() {
	std::string str;
	if (this->user_serv->getElems().size() == 0)
	{
		std::cout << "No event added to favorites!";
	}
	else {
		for (const auto& e : this->user_serv->getElems())
			std::cout << e << "\n";
	}
}

void UserMode::display_option(const std::string& option)
{
	if (option == "CSV") {
		std::string topicName = "Events.csv";
		topicName = "notepad \"" + topicName + "\"";
		system(topicName.c_str());
	}
	else{
		//f.HTMLsave(this->user_serv->getElems());
		system(std::string("start ").append("Events.html").c_str());
	}
}

void go_to_website(Event e)
{
	system(std::string("start ").append(e.getLink()).c_str());
}


void print_menu2() {
	std::cout << "\n1. Next";
	std::cout << "\n2. Add current event";
	std::cout << "\n3. Remove current event";
	std::cout << "\n4. Remove event with given title";
	std::cout << "\n5. Display my events";
	std::cout << "\n6. Display website";
	std::cout << "\n7. Change month";
	std::cout << "\n8. Display in format";
}

void UserMode::menuUser(const std::string& option) {
	int command;
	bool not_done = true;
	
	EventRepository* month_list = new EventRepository();
	Event e;
	choose_month(*month_list, e);
	
	while (not_done) {
		print_menu2();
		std::cout << "\n> ";
		std::cin >> command;
		while (std::cin.fail()) {
			std::cout << "\nInput not integer!";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "\n> ";
			std::cin >> command;
		}

		try {
			switch (command)
			{
			case 1:
				next(month_list,e);
				break;
			case 2:
				add_user_ui(*month_list,e);
				break;
			case 3:
				remove_user_ui(*month_list,e);
				break;
			case 4:
				remove_title_ui(*month_list);
				break;
			case 5:
				display_list();
				break;
			case 6:
				go_to_website(e);
				break;
			case 7:
				choose_month(*month_list,e);
				break;
			case 8:
				display_option(option);
				break;
			default:
				delete month_list;
				not_done = false;
			}
		}
		catch (const RepoException& ex) {
			std::cout << ex;
		}
	}
}

