#include "AdmController.h"
#include "ValidationException.h"


const Event& AdmController::find_event(std::string title)
{
	for (const auto& e : this->repo->getEventListRepo()) {
		if (e.getTitle() == title)
			return e;
	}
}

void AdmController::add_srv(std::string title, std::string description, int nr, std::string link, int day, int month, int year, int hours, int minutes) {
	Event e = Event(title,description,nr,link,day,month,year,hours,minutes);
	EventValidator v;
	v.validate(e);

	std::shared_ptr<ICommand> c(new AddCommand(*this->repo,e)); 
	this->commandManager.executeCmd(c);
}

void AdmController::remove_srv(std::string title) {
	Event e=find_event(title);
	std::shared_ptr<ICommand> c(new DeleteCommand(*this->repo, e));
	this->commandManager.executeCmd(c);
}

void AdmController::update_srv(std::string title,std::string new_title, std::string description, int nr, std::string link, int day, int month, int year, int hours, int minutes) {
	Event e1 = find_event(title);
	Event e2 = Event(new_title, description, nr, link, day, month, year, hours, minutes);
	EventValidator v;
	//v.validate(e1);
	v.validate(e2);
	std::shared_ptr<ICommand> c(new UpdateCommand(*this->repo, e1,e2));
	this->commandManager.executeCmd(c);
}

void AdmController::undo()
{
	this->commandManager.undo();
}

void AdmController::redo()
{
	this->commandManager.redo();
}

void AdmController::generateList() {
	std::string title, description, link;

	add_srv("Atelier de cusut / brodat","O zi pentru pasiuni, fashion, design!",0, "https://sibiucityapp.ro/en/events/atelier-de-cusut-brodat-1",21,3,2021,10,00);
	add_srv("Movie night", "Make a list, compare with friends, make plans to see a great film!", 0, "https://www.themovienightapp.com/", 21, 3, 2021, 10, 00);
	add_srv("Mici crime conjugale", "teatru de Eric - Emmanuel Schmitt", 0, "https://sibiucityapp.ro/en/events/mici-crime-conjugale", 19, 3, 2021, 19, 00);
	add_srv("Jewelery international showcase", "The Largest Independent Jewelry Trade Show in the Americas", 0, "https://10times.com/jewelers-international-showcase", 21, 3, 2021, 10, 00);
	add_srv("Creativation", "With nearly 100 classes to choose from, you can build an educational experience that fits your current business and creative needs.", 0, "https://10times.com/cha-mega", 15, 3, 2021, 9, 00);
	add_srv("The Future of Food at Europe's Favourite Natural Food Business Event", "Natural & Organic Products Europe is Europe's biggest trade show for natural & organic products making it the must attend event for buyers of natural health and living products, natural and organic food & drink as well as natural beauty & personal care products.", 0, "https://10times.com/natural-organic-europe", 19, 4, 2021, 9, 40);
	/*
	strcpy(title, "Professional Beauty London");
	strcpy(description, "Professional Beauty London is among Europe, leading beauty and spa trade event. The event involves a wide variety of cosmetics and spa industries demonstrating their latest discoveries and inventions in the field of cosmetics.");
	strcpy(link, "https://10times.com/professional-beauty-autumn");
	add_srv(title, description, 0, link, 17, 5, 2021, 10, 00);

	strcpy(title, "European Coffee, Tea & Soft Drinks Expo");
	strcpy(description, "European Coffee, Tea & Soft Drinks Expo is an event for the professional service of coffee, tea, soft drinks and other non-alcoholic products. It has received an overwhelming thumbs up from the industry.");
	strcpy(link, "https://10times.com/european-coffee-expo");
	add_srv(title, description, 0, link, 24, 3, 2021, 9, 30);

	strcpy(title, "Advanced Microsoft Teams Webinar for Assistants and Admins - Bringing Collaboration to the Next Level");
	strcpy(description, "If you are a Professional Assistant, Management Support or Admin you should not miss this! ");
	strcpy(link, "https://10times.com/e1z1-d0f5-4sdd");
	add_srv(title, description, 0, link, 23, 3, 2021, 7, 00);

	strcpy(title, "Primary Care and Public Health");
	strcpy(description, "Primary Care and Public Health is an event that illustrates products like the UK's leading event for GPs, federations, CCGs, nurses, midwives, AHPs and managers working in primary, community, public, prison and global health etc. It is an exhibition featuring the latest ideas, innovations and products, itâ€™s no wonder that delegates will experience something new.");
	strcpy(link, "https://10times.com/pcph");
	add_srv(title, description, 0, link, 12, 5, 2021, 10, 00);
	*/
}