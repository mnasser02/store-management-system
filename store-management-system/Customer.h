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

	//getters
	int bill() const;
	std::vector<Product> cart() const;

	void add_product(const Product&);
};

