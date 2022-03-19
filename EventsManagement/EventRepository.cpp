#include "EventRepository.h"
#include <algorithm>
#include <stdexcept>

std::ostream& operator<<(std::ostream& out, const RepoException& ex) {
	for (const auto& msg : ex.msgs) {
		out << msg << " ";
	}
	return out;
}

int EventRepository::getEventPos(const Event& e) {
	auto it = find(this->arr.begin(), this->arr.end(),e);
	if(it!=this->arr.end())
		return it - this->arr.begin();
	return -1;
}

std::string EventRepository::getFile()
{
	std::vector<std::string> msj;
	msj.push_back("\nNo file given in repository!");
	throw RepoException(msj);
}

void EventRepository::add_repo(const Event& e) {
	if (getEventPos(e) == -1)
		this->arr.push_back(e);
	else {
		std::vector<std::string> msj;
		msj.push_back("\nEvent already in database!");
		throw RepoException(msj);
	}
}

void EventRepository::remove_repo(const std::string& title){
	Event e = Event(title, "ss", 0, "sasa", 0, 0, 0, 0, 0);
	int i= getEventPos(e);
	if (i != -1)
		this->arr.erase(this->arr.begin() + i);
	else {
		std::vector<std::string> msj;
		msj.push_back("\nEvent not in database! Could not remove!");
		throw RepoException(msj);
	}
}

void EventRepository::update_repo(const Event& e1,const Event& e2) {
	std::vector<std::string> msgs;
	if (getEventPos(e1) == -1)
		msgs.push_back("\nGiven event not found in database!");
	if(getEventPos(e2)!=-1 && e1.getTitle()!=e2.getTitle())
		msgs.push_back("\nCannot update. New event title already in database!");

	if (msgs.size() > 0) {
		throw RepoException(msgs);
	}
	std::replace(this->arr.begin(), this->arr.end(), e1, e2);
}

bool compare(const Event& e1,const Event& e2) {
	if (e1.getDate().year > e2.getDate().year) {
		return false;
	}
	else if (e1.getDate().year == e2.getDate().year) {
		if (e1.getDate().month > e2.getDate().month)
		{
			return false;
		}
		else if (e1.getDate().month == e2.getDate().month)
		{
			if (e1.getDate().day >= e2.getDate().day) {
				return false;
			}
		}
	}
	return true;
}

void EventRepository::sortChronologically() {
	std::sort(this->arr.begin(), this->arr.end(), &compare);
}