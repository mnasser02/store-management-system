#include "Dealer.h"

Dealer::Dealer(const User& user, const std::string& date, const int& rent) : User(user), estableshment_date_(date), rent_(rent) {}

int Dealer::rent() const {
	return rent_;
}
std::string Dealer::estableshment_date() const {
	return estableshment_date_;
}

void Dealer::set_rent(const int& rent) {
	rent_ = rent;
}
void Dealer::set_establishment_date(const std::string& date) {
	estableshment_date_ = date;
}