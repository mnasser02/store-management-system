#include "Product.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

Product::Product(const std::string& name, int price, int quantity) : name_(name), price_(price), quantity_(quantity) {
	std::transform(name_.begin(), name_.end(), name_.begin(), ::toupper);
}

std::string Product::name() const {
	return name_;
}
int Product::price() const {
	return price_;
}
int Product::quantity() const {
	return quantity_;
}

void Product::set_name(const std::string& name) {
	name_ = name;
}
void Product::set_price(int price) {
	price_ = abs(price);
}
void Product::set_quantity(int quantity) {
	quantity_ = abs(quantity);
}

void Product::increase_quantity(int inc) {
	quantity_ += abs(inc);
}
void Product::decrease_quantity(int dec) {
	if (abs(dec) > quantity_)
		quantity_ = 0;
	else
		quantity_ -= abs(dec);
}
void Product::display() const {
	std::string name = name_;
	if (name.length() > 40)
		name = name.substr(0, 40) + "...";
	std::cout << std::left;
	std::cout << std::setw(43) << name << "\t \t" << "price: $" << std::setw(10) << price_ << "\t" << "availabe: " << std::setw(10) << quantity_ << std::endl;
	std::cout.unsetf(std::ios::left);
}
void Product::cart_display() const {
	std::string name = name_;
	if (name.length() > 40)
		name = name.substr(0, 40) + "...";
	std::cout << std::left;
	std::cout << std::setw(43) << name << "\t" << "price: $" << std::setw(7) << price_ << "\t" << "quantity: " << std::setw(7) << quantity_ << "\t" << "total: $" << std::setw(7) << quantity_ * price_ << std::endl;
	std::cout.unsetf(std::ios::left);
}