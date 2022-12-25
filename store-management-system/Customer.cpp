#include "Customer.h"
#include <fstream>
#include <sstream>
#include <iostream>

Customer::Customer(const User& user) : User(user) {}


int Customer::bill() const {
	return bill_;
}

void Customer::add_to_cart(const std::string& pathname, int i) {
	std::ifstream fin(pathname);
	std::string line;
	while (fin.peek() != EOF) {
		getline(fin, line);
		if (line == std::to_string(i)) {
			std::string name, tmp;
			int price, quantity, q;
			getline(fin, name);
			getline(fin, tmp);
			price = stoi(tmp);
			getline(fin, tmp);
			quantity = stoi(tmp);
			std::cout << "specify quantity: ";
			std::cin >> q;
			q = abs(q);
			if(q > quantity) {
				std::cout << "amount specified is not available" << std::endl;
				return;
			}
			//check if product is already in cart and increase quantity
			for (Product& p : cart_) {
				if (p.name() == name) {
					p.set_quantity(q + p.quantity());
					bill_ += p.price() * q;
					fin.close();
					return;
				}
			}
			Product product(name, price, q);
			edit_product(pathname, i, 2, q); //decrement amount added to cart from stock
			cart_.push_back(product);
			bill_ += product.price() * q;
			fin.close();
			return;
		}
		else {
			std::string grb;
			for (int k = 0; k < 3; ++k) {
				getline(fin, grb);
			}
		}
	}
	fin.close();
	std::cout << "product not available" << std::endl;
}
void Customer::remove_from_cart(const std::string& pathname, int i, int q) {
	--i;
	if (i >= cart_.size()) {
		std::cout << "cart does not containt " << i + 1 << " product(s)" << std::endl;
		return;
	}
	if (q > cart_[i].quantity()) {
		std::cout << "cart does not containt " << q << " of product " << i + 1 << std::endl;
		return;
	}
	bill_ -= cart_[i].price() * q;
	std::ifstream fin(pathname);
	std::string line;
	int k = 0;
	while (fin.peek() != EOF) {
		++k;
		getline(fin, line);
		getline(fin, line);
		if (line == cart_[i].name()) {
			std::string tmp;
			int price, quantity;
			getline(fin, tmp);
			price = stoi(tmp);
			getline(fin, tmp);
			quantity = stoi(tmp);
			edit_product(pathname, k, 1, q);
			if (q == cart_[i].quantity())
				cart_.erase(cart_.begin() + i);
			else
				cart_[i].set_quantity(cart_[i].quantity() - q);
			fin.close();
			return;
		}
		else {
			std::string grb;
			for (int k = 0; k < 2; ++k) {
				getline(fin, grb);
			}
		}
	}
	fin.close();
}
void Customer::view_cart() const {
	int i = 0;
	for (Product p : cart_) {
		std::cout << ++i <<". ";
		p.cart_display();
		std::cout << "--------------------------------------------------------------------------------------------------------------------" << std::endl;
	}
	std::cout << "=============" << std::endl
		<< "Total: $" << bill_ << std::endl
		<< "=============" << std::endl;
}
void Customer::view_products(const std::string& pathname) const {
	std::ifstream fin(pathname);
	while (fin.peek() != EOF) {
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