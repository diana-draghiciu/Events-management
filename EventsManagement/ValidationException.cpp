#include "ValidationException.h"
#include <assert.h>
#include <sstream>

void EventValidator::validate(const Event& e) {
	vector<string> msgs;
	if (e.getNr() < 0)
		msgs.push_back("\nCannot have negative nr of participants");
	if (e.getDate().day < 1 || e.getDate().day>31)
		msgs.push_back("\nDay must be between 1-31");
	if (e.getDate().month < 1 || e.getDate().month>12)
		msgs.push_back("\nMonth must be between 1-12");
	
	//We suppose the event application is for the following 10 years.
	if (e.getDate().year < 2020 || e.getDate().year>2030)
		msgs.push_back("\nYear must be between 2020-2030");
	if (e.getDate().hours < 1 || e.getDate().hours>24)
		msgs.push_back("\nHour must be between 1-24!");
	if (e.getDate().minutes < 0 || e.getDate().minutes>59)
		msgs.push_back("\nMinutes must be between 0-59");
	
	if (msgs.size() > 0) {
		throw ValidateException(msgs);
	}
}

ostream& operator<<(ostream& out, const ValidateException& ex) {
	for (const auto& msg : ex.msgs) {
		out << msg << " ";
	}
	return out;
}
