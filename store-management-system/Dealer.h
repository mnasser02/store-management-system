#pragma once
#include "User.h"
#include "Store.h"

class Dealer : public User
{
private:
	std::string estableshment_date_;
	int rent_;
public:
	Dealer(const User&, const std::string&, const int&);

	//getters
	int rent() const;
	std::string estableshment_date() const;
	//setters
	void set_rent(const int&);
	void set_establishment_date(const std::string&);
};

