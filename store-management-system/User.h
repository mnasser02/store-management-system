#pragma once
#include <string>
#include <unordered_set>

class User
{
private:
	int id_;
	std::string email_, password_, username_;
	static std::unordered_set<std::string> emails;
	static int n;
public:
	static  bool is_email_valid(const std::string&);
	static  bool is_password_valid(const std::string&);
	User(const std::string&, const std::string&, const std::string& username = "");

	//getters
	std::string email() const;
	std::string password() const;
	std::string username() const;
	int id() const;
	//setters
	void set_email(const std::string&);
	void set_password(const std::string&);
	void set_username(const std::string&);
	
	~User();
};

