#include "User.h"
#include <regex>
#include <iostream>

int User::n = 0;
std::unordered_set<std::string> User::emails;

bool User::is_password_valid(const std::string& password) {
	if (password.length() < 8) {
		std::cout << "password must consist of atleast 8 characters" << std::endl;
	}
	return password.length() >= 8;
}
bool User::is_email_valid(const std::string& email) {

	//reject more than one account with the same email
	if (emails.find(email) != emails.end()) {
		std::cout << "an account with the provided email already exists" << std::endl;
		return false;
	}

	const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	bool valid = std::regex_match(email, pattern);
	if (!valid) {
		std::cout << "invalid email format" << std::endl;
	}
	return valid;
}

//email validated before constructing object
User::User(const std::string& email, const std::string& password, const std::string& username) : email_(email), password_(password), username_(username) {
	emails.insert(email);
	n++;
	id_ = n;
}

std::string User::email() const {
	return email_;
}
std::string User::password() const {
	return password_;
}
std::string User::username() const {
	return username_;
}
int User::id() const {
	return id_;
}


void User::set_email(const std::string& email) {
	if (is_email_valid(email)) {
		email_ = email;
	}
}
void User::set_password(const std::string& password) {
	if (is_password_valid(password))
		password_ = password;
}
void User::set_username(const std::string& username) {
	username_ = username;
}

User::~User() {
	emails.erase(emails.find(email_));
}