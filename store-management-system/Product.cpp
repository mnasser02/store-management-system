#include "Product.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

Product::Product(const std::string& name, const int& price, const int& quantity, const int& idx) : name_(name), price_(price), quantity_(quantity), idx_(idx) {
	std::transform(name_.begin(), name_.end(), name_.begin(), ::toupper);
}

int Product::index() const {
	return idx_;
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

void Product::set_index(int& idx) {
	idx_ = idx;
}
void Product::set_name(const std::string& name) {
	name_ = name;
}
void Product::set_price(const int& price) {
	price_ = abs(price);
}
void Product::set_quantity(const int& quantity) {
	quantity_ = abs(quantity);
}

void Product::increase_quantity(const int& inc) {
	quantity_ += abs(inc);
}
void Product::decrease_quantity(const int& dec) {
	if (abs(dec) > quantity_)
		quantity_ = 0;
	else
		quantity_ -= abs(dec);
}
void Product::display() const {
	std::string name = name_;
	if (name.length() > 60)
		name = name.substr(0, 60) + "...";
	std::cout << std::left;
	std::cout << std::setw(63) << name << "\t" << "price: " << std::setw(10) << price_ << "\t" << "availabe: " << std::setw(10) << quantity_ << std::endl;
	std::cout.unsetf(std::ios::left);
}
void Product::customer_display() const {
	std::string name = name_;
	if (name.length() > 60)
		name = name.substr(0, 60) + "...";
	std::cout << std::left;
	std::cout << std::setw(63) << name << "\t" << "price: " << std::setw(10) << price_ << std::endl;
	std::cout.unsetf(std::ios::left);
}