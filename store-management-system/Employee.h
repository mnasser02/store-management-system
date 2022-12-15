#pragma once
#include "User.h"

class Employee : public User
{
private:
	int salary_;
	std::string start_date_, phone_number_;
public:
	Employee(const User&, const int&, const std::string&, const std::string&);

	//getters
	int salary() const;
	std::string start_date() const;
	std::string phone_number() const;
	//setters
	void set_salary(const int&);
	void set_phone_number(const std::string&);
	void set_start_date(const std::string&);
};

