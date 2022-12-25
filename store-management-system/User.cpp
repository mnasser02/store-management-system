#include "User.h"
#include "Product.h"
#include <regex>
#include <fstream>
#include <iostream>
#include <sstream>

int User::n = 0;
int User::number_of_products = 0;

void User::set_products_number(const std::string& pathname) {
	std::ifstream fin(pathname);
	std::string line;
	while (getline(fin, line))
		++number_of_products;
	number_of_products /= 4;
	fin.close();
}
int User::products_number() {
	return number_of_products;
}
bool User::is_password_valid(const std::string& password) {
	if (password.length() < 8) {
		std::cout << "password must consist of atleast 8 characters" << std::endl;
	}
	return password.length() >= 8;
}
bool User::is_email_valid(const std::string& email) {
	const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	bool valid = std::regex_match(email, pattern);
	if (!valid) {
		std::cout << "invalid email format" << std::endl;
	}
	return valid;
}

// email/password validated before constructing object
User::User(const std::string& email, const std::string& password, const std::string &role, const std::string& username) : email_(email), password_(password), role_(role), username_(username) {
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

void User::add_product(const std::string& pathname, const Product &p) const {
	std::ofstream fout(pathname, std::ios_base::app);
	++number_of_products;
	fout << number_of_products << std::endl << p.name() << std::endl << p.price() << std::endl << p.quantity() << std::endl;
	fout.close();
}

void User::remove_product(const std::string& pathname, int i) const {
	if (i < 0 || i > number_of_products) {
		std::cout << "product does not exist" << std::endl;
		return;
	}
	--number_of_products;
	std::ifstream fin(pathname);
	std::ofstream tmp1("tmp.txt");
	std::string line;
	while (fin.peek() != EOF) {
		getline(fin, line);
		std::string nb = line;
		for (int k = 0; k < 3; ++k) {
			getline(fin, line);
			if (nb != std::to_string(i))
				tmp1 << line << std::endl;
		}
	}
	tmp1.close();
	fin.close();

	std::ifstream tmp2("tmp.txt");
	std::ofstream fout(pathname);
	int j = 1;
	while (tmp2.peek() != EOF) {
		fout << j++ << std::endl;
		for (int k = 0; k < 3; ++k) {
			getline(tmp2, line);
			fout << line << std::endl;
		}
	}
	tmp2.close();
	fout.close();
}

void User::edit_product(const std::string& pathname, int i, int edit_choice, int change) const {
	std::ifstream fin(pathname);
	std::ofstream tmp1("tmp.txt");
	std::string line, old_product;
	while (fin.peek() != EOF) {
		getline(fin, line);
		if (line != std::to_string(i)) {
			for (int k = 0; k < 3; ++k) {
				getline(fin, line);
				tmp1 << line << std::endl;
			}
		}
		else {
			std::string name, tmp;
			int price, quantity;
			getline(fin, name);
			getline(fin, tmp);
			price = stoi(tmp);
			getline(fin, tmp);
			quantity = stoi(tmp);
			Product new_product(name, price, quantity);
			if (edit_choice == 1) {
				new_product.increase_quantity(change);
			}
			else if (edit_choice == 2) {
				new_product.decrease_quantity(change);
			}
			else if (edit_choice == 3) {
				new_product.set_price(change);
			}
			tmp1 << new_product.name() << std::endl << new_product.price() << std::endl << new_product.quantity() << std::endl;
		}
	}
	tmp1.close();
	fin.close();
	std::ifstream tmp2("tmp.txt");
	std::ofstream fout(pathname);
	int j = 1;
	while (tmp2.peek() != EOF) {
		fout << j++ << std::endl;
		for (int k = 0; k < 3; ++k) {
			getline(tmp2, line);
			fout << line << std::endl;
		}
	}
	tmp2.close();
	fout.close();
}

void User::view_products(const std::string& pathname) const {
	std::ifstream fin(pathname);
	while(fin.peek() != EOF) {
		std::string name, tmp;
		int price, quantity, i;
		getline(fin, tmp);
		i = stoi(tmp);
		getline(fin, name);
		getline(fin, tmp);
		price = stoi(tmp);
		getline(fin, tmp);
		quantity = stoi(tmp);
		Product p(name, price, quantity);
		std::cout << i << ". ";
		p.display();
		std::cout << "--------------------------------------------------------------------------------------------------------------------" << std::endl;
	}
	fin.close();
}