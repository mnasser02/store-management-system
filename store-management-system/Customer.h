#pragma once
#include <string>
#include <vector>
#include "User.h"
#include "Product.h"

class Customer : public User
{
private:
	std::vector<Product> cart_ = {};
	int bill_ = 0;
public:
	Customer(const User&);

	int bill() const;

	void add_to_cart(const std::string&, int);
	void remove_from_cart(const std::string&, int, int);
	void view_products(const std::string&) const;
	void view_cart() const;
};

