#include "Customer.h"

Customer::Customer(const User& user) : User(user) {}


int Customer::bill() const {
	return bill_;
}
std::vector<Product> Customer::cart() const {
	return cart_;
}

void Customer::add_product(const Product& product) {
	cart_.push_back(product);
	bill_ += product.price();
}