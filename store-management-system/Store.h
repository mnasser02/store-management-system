#pragma once
#include <vector>
#include "Product.h"
#include <unordered_set>
#include <unordered_map>
class Store
{
private:
	std::string name_;
	std::vector<Product> products_;
	std::unordered_set<std::string> products_available;
	std::unordered_map<std::string, int> product_idx;
	int products_count;
public:
	bool store_contains(const Product&) const;
	Store(const std::string&, const std::vector<Product>& products = {});

	//getters
	std::string name() const;
	std::vector<Product> products() const;
	int number_of_products() const;
	//setters
	void set_name(const std::string&);

	bool add_product(const Product&);
	void remove_product(const Product&);
	void edit_product(const std::string&);
	void display() const;
	void customer_display() const;
	Product get_product(const std::string&) const;
};

