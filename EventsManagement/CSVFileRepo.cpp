#include "CSVFileRepo.h"
#include <fstream>
#include <sstream>

void CSVFileRepo::add_repo(const Event& e)
{
	EventRepository::add_repo(e);
	save();
}

void CSVFileRepo::remove_repo(const std::string& title)
{
	EventRepository::remove_repo(title);
	save();
}

void CSVFileRepo::update_repo(const Event& e1, const Event& e2)
{
	EventRepository::update_repo(e1, e2);
	save();
}

void CSVFileRepo::save()
{
	std::ofstream fout;
	fout.open(this->file_name);
	if (!fout.is_open())
		return;

	for (const auto& e : this->getEventListRepo()) {
		fout << e.getTitle() << "," << e.getDescription() << "," << e.getLink() << "," << e.getNr() << "," << e.getDate().day << "," << e.getDate().month << "," << e.getDate().year << "," << e.getDate().hours << "," << e.getDate().minutes << "\n";
	}
	fout.close();
}
