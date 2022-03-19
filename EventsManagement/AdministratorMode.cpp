#include "AdministratorMode.h"
#include <iostream>
#include <string>
#include <sstream>
#include "ValidationException.h"
#include "EventRepository.h"

AdministratorUI::AdministratorUI(AdmController* ac) {
	this->Adm_serv = ac;
}

void AdministratorUI::show_list() {
	std::string str;
	for(const auto& e: this->Adm_serv->getEventListSrv())
		std::cout << e << "\n";
}

void AdministratorUI::add_AdmUI() {
	std::string title;
	std::cin.get();
	std::cout << "\nEvent title: ";
	std::getline(std::cin,title);

	std::string description;
	std::cout << "\nEvent description: ";
	std::getline(std::cin, description);

	int day, month, year, hours, minutes;
	int nr;
	
	std::cout << "\nEvent day: ";
	std::cin >> day;
	if (std::cin.fail()) {
		std::cout << "Invalid input! Input must be an integer!";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return;
	}
	std::cout << "\nEvent month: ";
	std::cin >> month;
	if (std::cin.fail()) {
		std::cout << "Invalid input! Input must be an integer!";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return;
	}
	std::cout << "\nEvent year: ";
	std::cin >> year;
	if (std::cin.fail()) {
		std::cout << "Invalid input! Input must be an integer!";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return;
	}
	std::cout << "\nEvent hours: ";
	std::cin >> hours;
	if (std::cin.fail()) {
		std::cout << "Invalid input! Input must be an integer!";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return;
	}
	std::cout << "\nEvent minutes: ";
	std::cin >> minutes;
	if (std::cin.fail()) {
		std::cout << "Invalid input! Input must be an integer!";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return;
	}
	
		
	std::cout << "\nNo. participants: ";
	std::cin >> nr;
	if (std::cin.fail()) {
		std::cout << "Invalid input! Input must be an integer!";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return;
	}
	

	std::cin.get();

	std::string link;
	std::cout << "\nEvent link: ";
	std::getline(std::cin,link);

	
	this->Adm_serv->add_srv(title, description, nr, link,day,month,year,hours,minutes);
	
}

void AdministratorUI::remove_AdmUI() {
	std::string title;
	std::cin.get();
	std::cout << "\nEvent title: ";
	std::getline(std::cin, title);

	this->Adm_serv->remove_srv(title);

}

void AdministratorUI::update_AdmUI() {
	std::string title;
	std::cin.get();
	std::cout << "\nEvent title: ";
	std::getline(std::cin, title);

	std::string new_title;
	std::cout << "\nEvent new title: ";
	std::getline(std::cin, new_title);

	std::string description;
	std::cout << "\nEvent description: ";
	std::getline(std::cin, description);

	int day, month, year, hours, minutes;
	std::cout << "\nEvent day: ";
	std::cin >> day;
	if (std::cin.fail()) {
		std::cout << "Invalid input! Input must be an integer!";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return;
	}
	std::cout << "\nEvent month: ";
	std::cin >> month;
	if (std::cin.fail()) {
		std::cout << "Invalid input! Input must be an integer!";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return;
	}
	std::cout << "\nEvent year: ";
	std::cin >> year;
	if (std::cin.fail()) {
		std::cout << "Invalid input! Input must be an integer!";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return;
	}
	std::cout << "\nEvent hours: ";
	std::cin >> hours;
	if (std::cin.fail()) {
		std::cout << "Invalid input! Input must be an integer!";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return;
	}
	std::cout << "\nEvent minutes: ";
	std::cin >> minutes;
	if (std::cin.fail()) {
		std::cout << "Invalid input! Input must be an integer!";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return;
	}

	int nr;
	std::cout << "\nNo. participants: ";
	std::cin >> nr;
	if (std::cin.fail()) {
		std::cout << "Invalid input! Input must be an integer!";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return;
	}

	std::cin.get();

	std::string link;
	std::cout << "\nEvent link: ";
	std::getline(std::cin, link);

	this->Adm_serv->update_srv(title,new_title, description, nr, link, day, month, year, hours, minutes);

}

void print_menu() {
	std::cout << "\n1. Add a new event";
	std::cout << "\n2. Remove an event";
	std::cout << "\n3. Update an event";
	std::cout << "\n4. Display events";
}

void AdministratorUI::menu_AdmUI() {
	int command;
	bool not_done = true;
	while (not_done) {
		print_menu();
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
				add_AdmUI();
				break;
			case 2:
				remove_AdmUI();
				break;
			case 3:
				update_AdmUI();
				break;
			case 4:
				show_list();
				break;
			default:
				not_done = false;
			}
		}
		catch (const ValidateException& ex) {
			std::cout << ex;
		}
		catch (const RepoException& re) {
			std::cout << re;
		}
	}
}