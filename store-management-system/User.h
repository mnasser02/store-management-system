#pragma once
#include <string>
#include "Product.h"

class User
{
private:
	int id_;
	std::string email_, password_, username_, role_;
	static int n, number_of_products;
public:
	static  bool is_email_valid(const std::string&);
	static  bool is_password_valid(const std::string&);
	static void set_products_number(const std::string&);
	static int products_number();
	User(const std::string&, const std::string&, const std::string&, const std::string& username = "");

	std::string email() const;
	std::string password() const;
	std::string username() const;
	int id() const;

	void set_email(const std::string&);
	void set_password(const std::string&);
	void set_username(const std::string&);

	void add_product(const std::string&, const Product&) const;
	void remove_product(const std::string&, int) const;
	void edit_product(const std::string&, int, int, int) const;
	void view_products(const std::string&) const;
};

