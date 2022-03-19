#include "TextFileRepo.h"
#include <fstream>
#include <sstream>

TextFileRepo::TextFileRepo(std::string file) : EventRepository{} {
	this->file_name = file;
	load();
}

void TextFileRepo::add_repo(const Event& e)
{
	EventRepository::add_repo(e);
	save();
}

void TextFileRepo::remove_repo(const std::string& title)
{
	EventRepository::remove_repo(title);
	save();
}

void TextFileRepo::update_repo(const Event& e1,const Event& e2)
{
	EventRepository::update_repo(e1, e2);
	save();
}

void TextFileRepo::load()
{
	std::ifstream fin;
	fin.open(this->file_name);
	if (!fin.is_open())
		return;
	Event e;
	fin.get();
	while (!fin.eof()) {
		fin >> e;
		this->add_repo(e);
	}
	fin.close();
}

void TextFileRepo::save()
{
	std::ofstream fout;
	fout.open(this->file_name);
	if (!fout.is_open())
		return;
	for (const auto& e : this->getEventListRepo())
		fout << e;
	fout.close();
}
