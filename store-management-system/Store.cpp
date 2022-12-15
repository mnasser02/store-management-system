#include "Store.h"
#include <iostream>

bool Store::store_contains(const Product& product) const {
	return products_available.find(product.name()) != products_available.end();
}

Store::Store(const std::string& name, const std::vector<Product>& products) :name_(name), products_(products) {
	for (int i = 0; i < products_.size(); i++) {
		Product& p = products_[i];
		p.set_index(i);
		product_idx[p.name()] = i;
		products_available.insert(p.name());
	}
	products_count = products.size();
}

std::string Store::name() const {
	return name_;
}
std::vector<Product> Store::products() const {
	return products_;
}
int Store::number_of_products() const {
	return products_count;
}

void Store::set_name(const std::string& name) {
	name_ = name;
}

bool Store::add_product(const Product& product) {
	if (store_contains(product)) {
		std::cout << "product already exists" << std::endl;
		return false;
	}
	else {
		products_.push_back(product);
		products_available.insert(product.name());
		products_count++;
		return true;
	}
}
void Store::remove_product(const Product& product) {
	if (store_contains(product)) {
		auto it = products_available.find(product.name());
		products_available.erase(it);
		products_count--;
	}
	else {
		std::cout << "product does not exist" << std::endl;
	}
}
void Store::edit_product(const std::string& name) {
	
	if (!store_contains(Product(name))) {
		std::cout << "product does not exist" << std::endl;
	}
	else {
		Product product = get_product(name);
		std::cout << "1. Increase quantity" << std::endl
			<< "2. Decrease quantity" << std::endl
			<< "3. Change price" << std::endl;
		int edit_choice = 0;
		std::cin >> edit_choice;
		if (edit_choice == 1) {
			int inc;
			std::cout << "increase by: ";
			std::cin >> inc;
			product.increase_quantity(inc);
		}
		else if (edit_choice == 2) {
			int dec;
			std::cout << "decrease by: ";
			std::cin >> dec;
			product.decrease_quantity(dec);
		}
		else if (edit_choice == 3) {
			int price;
			std::cout << "new price: ";
			std::cin >> price;
			product.set_price(price);
		}
		int idx = product_idx[name];
		products_[idx] = product;
	}
}
void Store::display() const {
	for (const Product& p : products_) {
		if (store_contains(p)) {
			p.display();
			std::cout << "--------------------------------------------------------------------------------------------------------------------" << std::endl;
		}
	}
}
void Store::customer_display() const {
	for (const Product& p : products_) {
		if (store_contains(p)) {
			p.customer_display();
			std::cout << "--------------------------------------------------------------------------------------------------------------------" << std::endl;
		}
	}
}
Product Store::get_product(const std::string& name) const {
	for (const Product& p : products_) {
		if (store_contains(p)) {
			if (p.name() == name)
				return p;
		}
	}
}
