#include "HtmlFileRepo.h"
#include <fstream>
#include <sstream>

void htmlFileRepo::add_repo(const Event& e)
{
	EventRepository::add_repo(e);
	save();
}

void htmlFileRepo::remove_repo(const std::string& title)
{
	EventRepository::remove_repo(title);
	save();
}

void htmlFileRepo::update_repo(const Event& e1, const Event& e2)
{
	EventRepository::update_repo(e1, e2);
	save();
}

void htmlFileRepo::save()
{
	std::ofstream fout;
	fout.open("Events.html");
	if (!fout.is_open())
		return;

	fout << "<!DOCTYPE html>";
	fout << "\n <html>";
	fout << "\n <head>";
	fout << "\n <title>Events</title>";
	fout << "\n </head>";
	fout << "\n <body>";
	fout << "\n <table border='1' bgcolor=" << '"' << "#E6F6C8" << '"' << ">";
	fout << "\n <tr>";
	fout << "\n <td>Title </td>";
	fout << "\n <td>Description </td>";
	fout << "\n <td>Link </td>";
	fout << "\n <td>No.participants </td>";
	fout << "\n <td>Date </td>";
	fout << "\n <td>Time </td>";
	fout << "\n </tr>";
	for (const auto& e : this->getEventListRepo()) {
		fout << "\n <tr>";

		fout << "\n <td>" << e.getTitle() << " </td>";
		fout << "\n <td>" << e.getDescription() << " </td>";
		fout << "\n <td><a href=" << '"' << e.getLink() << '"' << ">" << e.getLink() << "</a></td>";
		fout << "\n <td>" << e.getNr() << " </td>";
		fout << "\n <td>" << e.getDate().day << "/" << e.getDate().month << "/" << e.getDate().year << " </td>";
		if (e.getDate().minutes < 10)
			fout << "\n <td>" << e.getDate().hours << ":0" << e.getDate().minutes << " </td>";
		else
			fout << "\n <td>" << e.getDate().hours << ":" << e.getDate().minutes << " </td>";

		fout << "\n </tr>";
	}
	fout << "\n </table>";
	fout << "\n </body>";
	fout << "\n </html>";
	fout.close();
}
