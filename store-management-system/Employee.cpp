#include "Employee.h"

Employee::Employee(const User& user, const int& salary, const std::string& date, const std::string& number) : User(user), salary_(abs(salary)), start_date_(date), phone_number_(number) {}

int Employee::salary() const {
	return salary_;
}
std::string Employee::start_date() const {
	return start_date_;
}
std::string Employee::phone_number() const {
	return phone_number_;
}

void Employee::set_salary(const int& salary) {
	salary_ = abs(salary);
}
void Employee::set_phone_number(const std::string& number) {
	phone_number_ = number;
}
void Employee::set_start_date(const std::string& date) {
	start_date_ = date;
}